# More Effective C++

## item1：指针与引用的区别
使用指针的场景：
+ 存在不指向任何对象的可能
+ 可以指向不同的对象

使用引用的场景：
+ 指向一个对象后不改变指向
+ 重载运算符

## item2：尽量使用C++风格的类型转换

## item3：不要对数组使用多态
```cpp
#include <iostream>
using namespace std;

class BST {
public:
    int depth;
    BST(int d = 0) : depth(d){}
};

class balanceBST : public BST {
public:
    int left, right;
};

void printDepth(BST bst[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        cout << bst[i].depth << endl;
    }
}

int main(){
    balanceBST bst[10];
    for(int i = 0; i < 10; ++i)
    {
        bst[i].depth = i;
    }

    printDepth(bst, 10);
}
```
输出
```
0
32767
1
1
-2042110912
32767
2
21891
1
3
```

## item4：避免无用的缺省构造函数


## item5：对定制的“类型转换函数”保持警觉
```cpp
#include <string>
#include <iostream>
using namespace std ;

class BOOK  //定义了一个书类
{
    private:
        string _bookISBN ;  //书的ISBN号
        float _price ;    //书的价格

    public:
        //定义了一个成员函数，这个函数即是那个“期待一个实参为类类型的函数”
        //这个函数用于比较两本书的ISBN号是否相同
        bool isSameISBN(const BOOK & other ){
            return other._bookISBN==_bookISBN;
        }

        //类的构造函数，即那个“能够用一个参数进行调用的构造函数”（虽然它有两个形参，但其中一个有默认实参，只用一个参数也能进行调用）
        BOOK(string ISBN,float price=0.0f):_bookISBN(ISBN),_price(price){}
};

int main()
{
    BOOK A("A-A-A");
    BOOK B("B-B-B");

    cout<<A.isSameISBN(B)<<endl;   //正经地进行比较，无需发生转换

    cout<<A.isSameISBN(string("A-A-A"))<<endl; //此处即发生一个隐式转换：string类型-->BOOK类型，借助BOOK的构造函数进行转换，以满足isSameISBN函数的参数期待。
    cout<<A.isSameISBN(BOOK("A-A-A"))<<endl;    //显式创建临时对象，也即是编译器干的事情。
}

/*
 * 输出：
 * 0
 * 1
 * 1
 */
```
可以用 **单个形参** 来调用的构造函数定义了从 **形参类型** 到 **该类类型** 的一个隐式转换

如上述例子的 string -> Book 的隐式类型转换

解决方法：**explicit** ，在构造函数前加上该关键字就可以避免隐式转换，显示转换还是允许的


## item6：区别加减操作符的前置和后置形式

## item7：千万不要重载&&，||和，操作符

## item8：了解各种不同意义的new和delete

## item9：利用析构函数避免泄露资源

## item10：在构造函数内阻止资源泄露
构造函数可能会发生异常，而C++只会析构已经构造完成的对象，即对象只有在其构造函数执行完毕才算是完全构造

因此C++不自动清理

## item11：禁止异常流出析构函数之外


## item17：考虑使用lazy evaluatino
1. 引用计数
2. 区分读和写
3. 缓式取出
4. 表达式缓评估

## item19：了解临时对象的来源
两种情况：
1. 隐式类型转换
```cpp
#include <iostream>
using namespace std;

// 报错
void uppercasify(string& str){}

int main(){
    char subtleBookPlug[] = "Effective C++";
    string s;
    uppercasify(subtleBookPlug);
}
```
不可以将对象传递给一个  reference to non-const 的参数，假设编译器为此产生一个临时对象，
然后此临时对象被传递给 uppercasify，这个函数的实参 subtleBookPlug 并未收到影响，只有临时对象产生影响

而 reference-to-const 参数则不需要承担此问题(C++ Primer 第五版 P192)

2. 函数返回对象


## iterm20：协助完成返回值优化RVO
如果以 by-value 方式返回对象，背后隐藏的构造好析构函数都将无法消除

返回 构造函数参数 以取代对象，例如
```cpp
const Rational operator* (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
```
C++允许编译器将临时对象优化，使他们不存在，于是可以这样调用 `operator*`：
```cpp
Rational a = 10；
Rational b(1, 2);

Rational c = a * b;
```

编译器可以将表达式所定义的对象构造与 c 的内存内

最优的做法是用 inline


## item21：利用重载避免隐式类型转换
C++的重载操作符中的参数必须至少有一个用户定制类型的自变量


## item22：考虑以操作符复合形式(如+=)取代其独身形式(如+)

## item23：考虑使用其他程序库
stdio一般比iostreams性能好

## item24：了解虚函数、多重继承、虚基类、运行时类型判断的成本
+ 虚函数的成本：
    1. 为每个拥有虚函数的class耗费一个vtbl空间，其大小视虚函数的个数而定，每个类只有一个
        + vtbl该放在哪里，有两种方法(通常选用)：
            1. 在每个需要vtbl的目标文件内部产生一个vtbl副本，最后由链接器去除重复的副本
            2. vtbl被产生于内含其第一个 non-inline、non-pure 虚函数定义式的目标文件中，
            如果所有虚函数都被声明为 inline，通常忽略虚函数的 inline 指示
    2. 每个对象都多了一个 vptr
        + 调用虚函数的效率与调用非虚函数的效率相当
    3. 无法 inlining

+ RTTI
    + 一个类只需要一份RTTI信息，为type_info对象
    + 放在 vtbl 的第一个位置


## item25：将构造函数和非成员函数虚化
+ 虚构造函数就是根据其输入产生出不同类型的对象
+ 虚拷贝构造函数会返回一个指向其调用者的新副本的指针


## item26：限制某个类所能产生的对象数量





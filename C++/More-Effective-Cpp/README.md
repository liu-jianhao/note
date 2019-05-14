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

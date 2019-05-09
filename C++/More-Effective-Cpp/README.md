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

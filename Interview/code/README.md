# 目录
+ [双向链表](##手写一个双向链表)
+ [智能指针](##实现智能指针)


## 手写一个双向链表
```cpp
#ifndef LinkList_hpp
#define LinkList_hpp

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *pre;
};

template <typename T>
class LinkList
{
  private:
    Node<T>* head;
    Node<T>* tail;
    int length;

  public:
    LinkList();
    ~LinkList();

    Node<T>* makeNode();
    bool push(T data);
    void pop();
    T indexAt(int index);
    bool insert(T data, int index);
    void display();
};

template <typename T>
LinkList<T>::LinkList()
{
    head = makeNode();
    tail = head;
    length = 0;
}

template <typename T>
Node<T>* LinkList<T>::makeNode()
{
    Node<T>* node = new Node<T>;
    return node;
}

template <typename T>
LinkList<T>::~LinkList()
{
    while(head != tail)
    {
        Node<T>* next = head->next;
        free(head);
        head = next;
    }
    free(head);
}

template <typename T>
bool LinkList<T>::push(T data)
{
    Node<T>* newNode = makeNode();
    if(!newNode)
    {
        return false;
    }

    newNode->data = data;
    tail->next = newNode;
    newNode->pre = tail;
    newNode->next = head;
    head->pre = newNode;
    tail = newNode;
    length++;
    return true;
}

template <typename T>
void LinkList<T>::pop()
{
    if(!tail)
    {
        return;
    }

    tail = tail->pre;
    tail->next = head;
    head->pre = tail;
    length--;
}

template <typename T>
bool LinkList<T>::insert(T data, int index)
{
    if(index < 1 || index > length)
    {
        return false;
    }

    Node<T>* newNode = makeNode();
    newNode->data = data;

    Node<T>* p = head;
    for(int i = 0; i < index; ++i)
    {
        p = p->next;
    }
    newNode->pre = p->pre;
    newNode->next = p;
    newNode->pre->next = newNode;
    p->pre = newNode;
    length++;
    return true;
}

template <typename T>
void LinkList<T>::display()
{
    Node<T>* p = head->next;
    cout << "data:";
    while(p != tail)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << p->data << endl;
}

#endif
```


## 实现智能指针
### 第一代
```cpp
template<typename T>
class Auto_ptr1
{
public:
    Auto_ptr1(T* ptr = nullptr):m_ptr{ptr}
    {}

    virtual ~Auto_ptr1()
    {
        delete m_ptr;
    }

    T& operator*() { return *m_ptr; }
    T& operator->() { return m_ptr; }

private:
    T* m_ptr;
};

class Resource
{
public:
    Resource() { cout << "Resource acquired!" << endl; }
    virtual ~Resource() { cout << "Resource destoryed!" << endl; }
};

int main()
{
    {
        Auto_ptr1<Resource> res(new Resource);
    }

    return 0;
}
```
输出：
```
Resource acquired!
Resource destoryed!
```
但是上面的实现却有致命的隐患，考虑下面的代码：
```cpp
int main()
{
    {
        Auto_ptr1<Resource> res1(new Resource);
        Auto_ptr1<Resource> res2(res1);
    }

    cin.ignore(10);
    return 0;
}
```
看起来没有问题，但是执行起来，程序会崩溃。因为用res1初始化res2，调用的是默认复制构造函数，执行的是浅复制。所以，res2与res1内部保存是同一块内存，当销毁变量时，同一块内存将会被多次释放，程序当然会奔溃。同样地，下面的代码依然存在同样的问题：
```cpp
void passByValue(Auto_ptr1<Resource> res)
{}
int main()
{
    {
        Auto_ptr1<Resource> res1(new Resource);
        passByValue(res1);
    }

    cin.ignore(10);
    return 0;
}
```
因为res1被浅复制到函数参数res中，函数执行后其内存会被释放，那么在销毁res1时，又会销毁已经释放的内存，程序崩溃。所以我们需要修改这个类，最好自己实现复制构造函数，同样地要自己实现赋值运算符重载。假如我们在这两个函数中，将指针所有权从一个对象转移到另外一个对象，那么上面的问题将迎刃而解。修改的智能指针类如下：
### 第二代
```cpp
template<typename T>
class Auto_ptr2
{
public:
    Auto_ptr2(T* ptr = nullptr) : m_ptr{ptr}
    {}

    virtual ~Auto_ptr2()
    {
        delete m_ptr;
    }

    Auto_ptr2(Auto_ptr2& rhs)
    {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
    }

    Auto_ptr2& operator=(Auto_ptr2& rhs)
    {
        if(&rhs == this)
        {
            return *this;
        }

        delete m_ptr;
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
        return *this;
    }

    T& operator*(){ return *m_ptr; }
    T& operator->(){ return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
private:
    T* m_ptr;
};
```

```cpp
int main()
{
    Auto_ptr2<Resource> res1(new Resource);
    Auto_ptr2<Resource> res2; // 初始化为nullptr

    cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    res2 = res1; // 转移指针所有权

    cout << "Ownership transferred\n";

    cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    cin.ignore(10);
    return 0;
}
```
输出：
```cpp
Resource acquired
res1 is not null
res2 is null
Ownership transferred
res1 is null
res2 is not null
Resource destroyed
```

第二代智能指针实际上就是实现了移动语义，类似于`std::auto_ptr`。

`std::auto_ptr`内部调用的是非数组`delete`，那么对于动态分配的数组，`std::auto_ptr`无法正常工作，可能会出现内存泄露。最后，`std::auto_ptr`对STL不兼容，因为STL的对象在进行复制时，就是进行复制，而不是移动语义。


### 第三代
```cpp
template<typename T>
class Auto_ptr3
{
public:
    Auto_ptr3(T* ptr = nullptr):
        m_ptr{ptr}
    {}

    Auto_ptr3(const Auto_ptr3& rhs) = delete;

    Auto_ptr3(Auto_ptr3&& rhs) :
        m_ptr{ rhs.m_ptr }
    {
        rhs.m_ptr = nullptr;
    }

    Auto_ptr3& operator=(const Auto_ptr3& rhs) = delete;

    Auto_ptr3& operator=(Auto_ptr3&& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        std::swap(m_ptr, rhs.m_ptr);
        return *this;

    }

    virtual ~Auto_ptr3()
    {
        delete m_ptr;
    }

    T& operator*() { return *m_ptr; }
    T* operator->() { return m_ptr; }

    bool isNull() const { return m_ptr == nullptr; }
private:
    T* m_ptr;
};
```
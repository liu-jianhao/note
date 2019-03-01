#include <iostream>
using namespace std;

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

class Resource
{
public:
    Resource() { cout << "Resource acquired!" << endl; }
    virtual ~Resource() { cout << "Resource destoryed!" << endl; }
};

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

    return 0;
}
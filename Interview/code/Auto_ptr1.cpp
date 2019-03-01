#include <iostream>
using namespace std;

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
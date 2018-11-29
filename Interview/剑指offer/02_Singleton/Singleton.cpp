#include <mutex>
#include <thread>
#include <cassert>
#include <iostream>
#include <unistd.h>

class Singleton{
private:
    Singleton();
    ~Singleton();

public:
    static Singleton* get_instance();
    static Singleton* m_instance;

    static std::mutex m_mutex;
};

Singleton* Singleton::m_instance = nullptr;

Singleton::Singleton()
{}

Singleton::~Singleton()
{
    delete m_instance;
}

// 线程非安全版本
// Singleton* Singleton::get_instance()
// {
//     if(m_instance == nullptr)
//     {
//         m_instance = new Singleton();
//     }

//     return m_instance;
// }


// 线程安全版本，加锁版本
// Singleton* Singleton::get_instance()
// {
//     std::lock_guard<std::mutex> lock(m_mutex);

//     if(m_instance == nullptr)
//     {
//         m_instance = new Singleton();
//     }

//     return m_instance;
// }

// 线程安全版本，call_once版本
Singleton* Singleton::get_instance()
{
    static std::once_flag oc;
    std::call_once(oc, [] {
        m_instance = new Singleton();
    });
    return m_instance;
}

void Test1()
{
    std::cout << "Begin Test1...\n";
    Singleton *s1 = Singleton::get_instance();
    Singleton *s2 = Singleton::get_instance();

    assert(s1 == s2);
    std::cout << "Test1 passed\n";
}

// 并发测试
void Test2()
{
    std::cout << "Begin Test2...\n";
    std::thread t1([] {
        for(int i = 0; i < 5; ++i)
        {
            Singleton *s1 = Singleton::get_instance();
            Singleton *s2 = Singleton::get_instance();
            assert(s1 == s2);
            sleep(1);
        }
    });

    std::thread t2([] {
        for (int i = 0; i < 5; ++i)
        {
            Singleton *s1 = Singleton::get_instance();
            Singleton *s2 = Singleton::get_instance();

            assert(s1 == s2);
            sleep(1);
        }
    });

    t1.join();
    t2.join();

    std::cout << "Test2 passed\n";
}

int main()
{
    Test1();
    Test2();
}
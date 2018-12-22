#include <memory>
#include <string>
#include <iostream>
#include <mutex>
#include <cassert>

using namespace std;

mutex g_mutex;
shared_ptr<string> g_pv(new string("liu"));

void post(const string& f)
{
    lock_guard<mutex> lg(g_mutex);
    // 当traverse中调用post时才需要复制
    if(!g_pv.unique())
    {
        g_pv.reset(new string(*g_pv));
        printf("copy the whole list\n");
    }
    assert(g_pv.unique());
    *g_pv += f;
}

void traverse()
{
    shared_ptr<string> foos;
    {
        lock_guard<mutex> lg(g_mutex);
        foos = g_pv;
        assert(!g_pv.unique());
    }

    // 做一些修改
    post(string(" traverse"));
}

int main()
{
    cout << "*g_pv = " << *g_pv << endl;

    traverse();
    cout << "*g_pv = " << *g_pv << endl;

    post(" post");
    cout << "*g_pv = " << *g_pv << endl;

    traverse();
    cout << "*g_pv = " << *g_pv << endl;
}
# Atomic

## 为什么要使用原子操作
1. 读和写不是atomic
2. 编译器生成的代码有可能改变操作次序
使用`mutex`两个问题都可以解决，但代价比较昂贵，所以用`atomic`取代。


## 用例
```cpp
#include <atomic>    // for atomics
#include <future>    // for async() and futures
#include <thread>    // for this_thread
#include <chrono>    // for durations
#include <iostream>

long data;
std::atomic<bool> readyFlag(false);

void provider ()
{
    // after reading a character
    std::cout << "<return>" << std::endl;
    std::cin.get();

    // provide some data
    data = 42;

    // and signal readiness
    readyFlag.store(true);
}

void consumer ()
{
    // wait for readiness and do something else
    while (!readyFlag.load()) {
        std::cout.put('.').flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // and process provided data
    std::cout << "\nvalue : " << data << std::endl;
}

int main()
{
    // start provider and consumer
    auto p = std::async(std::launch::async,provider);
    auto c = std::async(std::launch::async,consumer);

    std::atomic<int> x{0};
    int x0 = x;
    std::cout << "x = " << x << std::endl;
    while ( !x.compare_exchange_strong(x0, x0+1) ) {}
    std::cout << "x = " << x << std::endl;

}
```
编译后运行：
```shell
$ ./atomics 
<return>
x = 0
x = 1
....

value : 42
```

## 常用接口
假设有一个原子变量`a`
+ `a.store(val)`：赋值val返回void
+ `a.load()`：返回a的拷贝
+ `a.exchange(val)`：赋值val并返回旧值a的拷贝
+ `a.compare_exchange_strong(exp, des)`
+ `a.compare_exchange_weak(exp, des)`
上面两个操作是`CAS(compare-and-swap)`操作，比较“某内存区内容“和”某给定值“，并且唯有在它们相同时才将内存区内容更新为另一个给定的新值。
例如：
```cpp
bool success = x.compare_exchange_strong(y, z);
// If x==y, make x=z and return true
// Otherwise, set y=x and return false
```
这两个操作常用做无锁算法
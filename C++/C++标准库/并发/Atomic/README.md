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


## 内存屏障
### 定义
阻止编译器或者CPU对程序进行部分优化，防止在多线程环境下执行的结果和预期不同。

### 编译器的内存屏障
`volatile`：
+ 对声明为`volatile`的变量进行的任何操作都不会被优化器去除，即使它看起来没有意义
+ 不会被编译器优化到寄存器中，每次读写操作都保证在内存中完成
+ 在不同表达式内的多个`volatile`变量之间的操作顺序不会被优化器调换

但是`volatile`不能解决以下问题：
+ 保证变量的读写的原子性
+ 确保变量的操作发生在主内存中，而不是在Cache中
+ 确保CPU不会乱序执行指令
也就是说`volatile`只会让编译器循规蹈矩地按顺序生成指令，但CPU如何执行指令是编译器无法控制的。此时我们需要另一种内存屏障——CPU的内存屏障

### CPU内存屏障
用来消除CPU乱序对内存访问的影响，可以保证多个变量交叉访问的逻辑顺序，一般分为：
+ 全屏障，即双向屏障。所有在屏障前的指令不得调换到屏障后执行，同时所有屏障后的指令不得调换到屏障前执行。
+ Acquire屏障，即后向屏障。禁止CPU将屏障后的指令调换到屏障前执行。Acquire的通常作用是构建临界区，在临界区上锁前执行，临界区里的代码无法调换到临界区外执行，但反过来可以。
+ Release屏障，即前向屏障。与Acquire相反，通常用于结束临界区。


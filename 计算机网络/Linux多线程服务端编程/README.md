目录：
+ [线程同步精要](#第2章：线程同步精要)
+ [多线程服务器的适用场合与常用编程模型](#第3章：多线程服务器的适用场合与常用编程模型)
+ [高效的多线程日志](#第3章：高效的多线程日志)


# 第2章：线程同步精要

## 并发编程的两种基本模型
+ message passing
    + 分布式系统架构就只有这一种
+ shared memory

## 线程同步的四项原则
1. 尽量最低限度地共享对象
2. 使用高级并发编程构件，如TaskQueue、Producer-Consumer Queue、CountDownLatch等等
3. 同步原语，非递归的互斥器和条件变量，慎用读写锁，不要用信号量
4. 除了使用atomic整数之外，不要自己编写lock-free代码


## 同步原语的使用
### mutex
一般原则：
+ 用RAII手法封装mutex的创建、销毁、加锁、解锁
+ 只使用非递归的mutex
+ 不手动调用lock和unlock函数，一切交给栈

### 条件变量
需要等待某个条件成立，应该使用条件变量。

只有一种正确的使用方式：
+ wait端：
    1. 必须与mutex一起使用
    2. 在mutex已上锁的时候才调用wait
    3. 吧判断布尔条件和wait放到while循环中
    ```cpp
    using namespace std;
    mutex mutex;
    condition_variable cond(mutex);
    queue queue;
    int dequeue()
    {
        lock_guard<mutex> lock(mutex);
        while(queue.empty()) // 必须用循环，必须在判断之后再wait
        {
            cond.wait();
        }
        assert(!queue.empty());
        int top = queue.front();
        queue.pop_front();
        return top;
    }
    ```

+ 对于signal/broadcast端：
    1. 不一定要在mutex已经上锁的情况下调用signal
    2. 在signal之前一定要修改布尔表达式
    3. 修改布尔表达式通常需要mutex保护
    ```cpp
    void enqueue(int x)
    {
        lock_guard<mutex> lock(mutex);
        queue.push_back(x);
        cond.notify_one(); // 可以移除临界区外
    }
    ```

#### CountDownLatch
两个主要用途：
1. 主线程发起多个子线程，等这些子线程各自完成一定的任务之后，主线程才继续执行。通常用于主线程等待多个子线程完成初始化。
2. 主线程发起多个子线程，子线程都等待主线程，主线程完成其他一些任务之后通知所有子线程开始执行。通常用于多个子线程等待主线程发起起跑命令。

代码参考muduo库的实现

### 线程安全的singleton实现
+ pthread_once


### sleep不是同步原语

### 借shared_prt实现copy-on-write
```cpp
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
```

输出：
```
*g_pv = liu
copy the whole list
*g_pv = liu traverse
*g_pv = liu traverse post
copy the whole list
*g_pv = liu traverse post traverse
```
可以看出，在调用traverse时，post才会需要复制一份，
因为这时其他线程在读`g_pv`，而post需要修改`g_pv`，所以不能原地修改，
而是复制一份，在副本上修改。



# 第3章：多线程服务器的适用场合与常用编程模型
多线程 -> 更好地发挥多核处理器的效能

## 单线程服务器的常用编程模型
最广泛：non-blocking IO + IO multiplexing，即Reactor模式

程序基本结构是一个事件循环，以事件驱动和事件回调的方式实现业务逻辑
+ 优点：不难，效率不错，适用于IO密集型应用
+ 缺点：要求事件回调函数必须是非阻塞的

## 多线程服务器的常用编程模型
1. 每个请求传建一个线程，使用阻塞IO操作。伸缩性不佳
2. 使用线程池，使用阻塞IO操作。与第一种相比，性能较好
3. 使用non-blocking IO + IO multiplexing
4. Leader/Follower等高级模式

默认使用第三种

### one loop per thread
每个IO线程有一个event loop(Reactor)，用于处理读写和定时事件

### 线程池
对于没有IO只有计算任务的线程，使用event loop会浪费，一种补充方案是用blocking queue

### 推荐模式
+ event loop用作IO multiplexing，配合non-blocking IO和定时器
+ thread pool用来做计算，具体可以是任务队列或生产者或消费者队列

## 进程间通信只用TCP

## 多线程服务器的适用场合
### 必须使用单线程的场合
1. 程序可能会fork
    + 只有单线程能fork
2. 限制程序的CPU占有率
    + 只有单线程能限制程序的CPU占有率


### 单线程程序的优缺点
程序的结构一般为一个基于IO multiplexing 的event loop

Event loop有一个明显的缺点就是它是非抢占的。这个缺点可以用多线程来克服。

### 适合多线程程序的场景
提高响应速度，让IO和计算相互重叠，降低延迟。

例如日志，再一次请求响应中，可能要写多条日志消息，如果使用同步的方式写文件多半会降低性能。这是用单独一个logging线程，通过一个或多个blocking queue对提供接口。将消息往queue一塞，基本不需要等待。这样服务线程的计算和logging线程的磁盘IO相互重叠，降低服务线程的响应时间。

#### 线程的分类
+ IO线程，主循环是IO multiplexing，阻塞地等待在select/poll/epoll_wait系统调用上。这类线程处理定时事件。当然也有一些简单的计算，消息的编码或解码。
+ 计算线程，这类线程的主循环是blocking queue，阻塞地等在条件变量上。这类线程一般位于thread pool中。
+ 第三类库所用的线程，如logging，database connection


# 第3章：高效的多线程日志
一个日志库大体可以分为前端和后端两部分：
+ 前端是供应用程序使用的接口，并生成日志消息
+ 后端则负责把日志消息写到目的地

在多线程程序中，前端和后端都与单线程程序没有什么区别，无非是每个线程有自己的前端，整个程序共用一个后端。

难点在于将日志数据从多个前端高效地传输到后端。这是一个典型的多生产者-单消费者的问题，
对生产者(前端)而言，要尽量做到低延迟，低CPU开销、无阻塞；对消费者(后端)而言，要做到足够大的吞吐量，并占用较小的资源

## 功能需求

往文件写日志的一个常见问题是万一程序崩溃了，要么最后若干条日志往往丢失了，因为日志库不能每条消息都flush硬盘，
更不能每条消息都open、close文件，开销太大。

解决办法：
1. 定期flush
2. 每条内存中的日志消息都带有cookie(或叫哨兵值)，其值为某个函数的地址，这样通过在core dump文件中查找cookie就能找到尚未来得及写入磁盘的消息

## 多线程异步日志
线程安全：
+ 简单的办法就是维护一个全局的mutex 保护IO，或者每个线程单独写一个日志文件。
但性能堪忧，前者会造成全部线程抢一个锁，后者可能让业务线程阻塞在写磁盘上

最好一个进程只写一个日志文件

用一个背景线程负责手记日志消息，并写入日志文件，其他业务线程只管往这个日志线程发送日志消息，称为异步日志。

muduo日志库采用双缓冲技术，基本思路是准备两块buffer：A和B，前端负责往bufferA填数据，后端负责将bufferB的数据写入文件。

当bufferA写满之后，交换A和B，让后端将bufferA的数据写入文件，而前端往bufferB填入新的日志消息，如此往复。

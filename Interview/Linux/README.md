

## fork()流程
对父进程程序段、数据段、堆段以及栈段创建拷贝。

如果简单地将父进程虚拟内存页拷贝到新的子进程，这样很容易造成浪费(如fork之后exec)。
采用两种技术避免这种浪费：
1. 内核将每一进程的代码段标记为只读，从而使进程无法修改自身代码。这样父子进程就可以共享同意代码段
2. 对于父进程数据段、堆段和栈段中的各页，内核采用写时复制技术来处理。
fork()之后，内核会捕获所有父进程或子进程针对这些页面的修改企图，并为将要修改的页面创建拷贝。
系统将新的页面拷贝分配给遭到内核捕获的进程，还或对子进程的相应页表项做适当调整

## vfork、clone与fork的区别
三个函数最终由同一个函数实现(kernel/fork.c中的do_fork())

vfork是为子进程立刻执行exec而专门设计的

区别：
+ 无需为子进程复制虚拟内存页或页表，子进程共享父进程的内存，直至成功执行了exec()或是调用_exit()退出
+ 在子进程调用exec()或_exit()之前，将暂停执行父进程
在不影响父进程的前提下，子进程能在vfork和exec之间做的操作屈指可数，包括对打开文件描述符进行操作

clone也能创建一个新进程，对创建进程期间的步骤控制更为精确

## 僵尸进程
在父进程执行wait()之前，其子进程就已经终止。内核通过将子进程转化为僵尸进程来处理这种情况。
这意味着将释放进程所把持的大部分资源，以便提供其他进程重新使用。
该进程所唯一保留的是内核进程表中的一条记录，其中包含了子进程ID终止状态、资源使用数据等信息

如果存在大量僵尸进程，将会填满内核进程表，从而阻碍新进程的创建。既然无法用信号杀死僵尸进程，
那么从系统中移除的唯一办法是杀掉它们的父进程，此时init进程将会接管和等待这些僵尸进程，从而从系统将它们清理掉。

## SIGCHLD信号
无论一个子进程于何时终止，系统都会向其父进程发送SIGCHILD信号，对该信号的默认处理是忽略。

子进程的终止属于异步事件，父进程应使用wait来防止僵尸进程的累积，或者采用以下两种办法：
+ 父进程调用不带WNOHANG标志的wait()，或waitpid()方法，此时如果尚无已经终止的子进程，那么调用将会阻塞
+ 父进程周期性地调用调用WHOHANG标志的waitpid()，执行针对已经终止子进程的非阻塞检查
这两种办法都使用便，可以采用针对SIGCHLD信号的处理程序，用来捕获终止子进程。

进程可以将对SIGCHLD信号的处理设置置为忽略(SIG_IGN)，这将立即丢弃终止子进程的状态。


## epoll & poll & select
select的缺点：
1. 每次调用select，都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多时会很大
2. 同时每次调用select都需要在内核遍历传递进来的所有fd，这个开销很多时也很大
3. select支持的文件描述符数量太小，默认是1024

epoll避免了上述三个缺点：
1. 每次注册新的事件到epoll句柄中时(epoll_ctl中指定EPOLL_CTL_ADD)，会把所有的fd拷贝进内核，而不是在epoll_wait的时候重复拷贝。epoll保证了每个fd在整个过程只会拷贝一次
2. 不像select或poll一样每次都把current(当前进程)轮流加入fd对应的设备等带队列中，而只在epoll_ctl时把current挂一遍并为每个fd指定一个回调函数，当设备就绪，唤醒等待队列上的等待者时，就会调用这个回调函数，而这个回调函数会把就绪的fd加入一个就绪链表。epoll_wait的工作实际上就是在这个就绪链表中查看有没有就绪的fd
3. epoll所支持的fd上限就是可以最大打开文件的数目

epoll的应用场景就是需要同时处理许多客户端的服务器，需要监视大量的文件描述符，但大部分处于空闲状态，只有少数文件描述符处于就绪态

## epoll的ET和LT
水平触发：如果文件描述符上可以非阻塞地执行IO系统调用，此时认为它已经就绪了
边缘触发：如果文件描述符自上次状态检查以来有了新的IO活动，此时需要触发通知

采用水平触发时，可以在任意时刻检查文件描述符的就绪状态，
而采用边缘触发时，只有当IO事件发生时我们才会收到通知，
所以在接收到一个IO事件通知后，要尽可能多地执行IO

## ET使用非阻塞socket
如果程序采用循环来对文件描述符执行尽可能多的IO，而文件描述符又被置为可阻塞的，
那么最终当没有更多的IO可执行时，IO系统调用就会阻塞，所以每个被检查的文件描述符应该是非阻塞的

## 进程与线程的区别？
+ 进程是资源分配的最小单位，线程是程序执行的最小单位。

+ 进程有自己的独立地址空间，每启动一个进程，系统就会为它分配地址空间，建立数据表来维护代码段、堆栈段和数据段，这种操作非常昂贵。而线程是共享进程中的数据的，使用相同的地址空间，因此CPU切换一个线程的花费远比进程要小很多，同时创建一个线程的开销也比进程要小很多。

+ 线程之间的通信更方便，同一进程下的线程共享全局变量、静态变量等数据，而进程之间的通信需要以通信的方式（IPC)进行。不过如何处理好同步与互斥是编写多线程程序的难点。

+ 但是多进程程序更健壮，多线程程序只要有一个线程死掉，整个进程也死掉了，而一个进程死掉并不会对另外一个进程造成影响，因为进程有自己独立的地址空间。


## 惊群效应
### accept惊群（Linux2.6已解决）
一个连接过来，只有一个进程可以accept成功
### epoll惊群
如果多个进程/线程阻塞在监听同一个监听socket fd的epoll_wait上，当有一个新的连接到来时，所有的进程都会被唤醒。


## 静态库和动态库
静态库:
+ 静态库对函数库的链接是放在编译时期完成的。
+ 程序在运行时与函数库再无瓜葛，移植方便。
+ 浪费空间和资源，因为所有相关的目标文件与牵涉到的函数库被链接合成一个可执行文件

动态库:
不同的应用程序如果调用相同的库，那么在内存里只需要有一份该共享库的实例，规避了空间浪费问题。动态库在程序运行是才被载入，也解决了静态库对程序的更新、部署和发布页会带来麻烦

+ 动态库把对一些库函数的链接载入推迟到程序运行的时期。
+ 可以实现进程之间的资源共享。（因此动态库也称为共享库）
+ 将一些程序升级变得简单。
+ 甚至可以真正做到链接载入完全由程序员在程序代码中控制（显示调用）。
Window与Linux执行文件格式不同，在创建动态库的时候有一些差异。
+ 在Windows系统下的执行文件格式是PE格式，动态库需要一个DllMain函数做出初始化的入口，通常在导出函数的声明时需要有_declspec(dllexport)关键字。
+ Linux下gcc编译的执行文件默认是ELF格式，不需要初始化入口，亦不需要函数做特别的声明，编写比较方便。


## 加载并运行a.out
1. 删除已存在的用户区域。删除当前进程虚拟地址的用户部分中的已存在的区域结构
2. 映射私有区域。为新程序的代码、数据、bss和栈区域创建新的区域结构。所有这些区域都是私有的、写时复制的。
代码和数据区域被映射为a.out文件中的.text和.data区。bss区域是请求二进制零的，映射到匿名文件，其大小包含在a.out中。
栈和堆区域也是为二进制清零的，初始长度为零。
3. 映射共享区域。如果a.out程序与共享对象链接，比如标准C库libc.so，
那么这些对象都是动态链接到这个程序的，然后再映射到用户虚拟地址空间中的共享区域内。
4. 设置程序计数器(PC)。设置当前进程上下文中的程序计数器指向代码区域的入口点。


## 创建一个daemon
1. 执行一个fork()，之后父进程退出，子进程继续执行。(结果是daemon成为了init进程的子进程)。之所以要做这一步是因为：
    1. 假设daemon是从命令行启动的，父进程的终止会被shell发现，shell在发现之后会显示出另一个shell提示符并让子进程继续在后台执行
    2. 子进程被确保不会成为一个进程组首进程
2. 子进程调用setsid()开启一个新会话并释放它与控制终端之间的所有联系
3. 如果daemon从来没有打开过终端设备，那么就无需担心daemon会重新请求一个控制终端了。
如果daemon后面可能湖打开一个终端设备，那么必须要采取措施来确保这个不会成为控制终端
4. 清除进程umask以确保daemon创建文件和目录时拥有所需的权限
5. 修改进程的当前工作目录，通常改为根目录
6. 关闭daemon从其父进程继承而来的所有打开的文件描述符(可选)
7. 关闭文件描述符0、1、2之后，daemon通常会打开/dev/null并使用dup2()使所有这些描述符指向这个设备。
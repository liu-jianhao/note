# 列出函数的名字

## 例子
```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *thread_func(void *p_arg)
{
    while (1)
    {
        sleep(10);
    }
}
int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_func, "Thread 1");
    pthread_create(&t2, NULL, thread_func, "Thread 2");

    sleep(1000);
    return 0;
}
```

## 技巧
使用gdb调试时，使用“info functions”命令可以列出可执行文件的所有函数名称。以上面代码为例：
```
gdb ./func -q
Reading symbols from ./func...done.
(gdb) info functions 
All defined functions:

File func.c:
int main(void);
void *thread_func(void *);

Non-debugging symbols:
0x0000000000000560  _init
0x0000000000000590  pthread_create@plt
0x00000000000005a0  sleep@plt
0x00000000000005c0  _start
0x00000000000005f0  deregister_tm_clones
0x0000000000000630  register_tm_clones
0x0000000000000680  __do_global_dtors_aux
0x00000000000006c0  frame_dummy
0x0000000000000740  __libc_csu_init
0x00000000000007b0  __libc_csu_fini
0x00000000000007b4  _fini
```
可以看到会列出函数原型以及不带调试信息的函数。

另外这个命令也支持正则表达式：“info functions regex”，这样只会列出符合正则表达式的函数名称，例如：
```
(gdb) info functions thr*
All functions matching regular expression "thr*":

File func.c:
void *thread_func(void *);

Non-debugging symbols:
0x0000000000000590  pthread_create@plt
```
可以看到gdb只会列出名字里包含“thr”的函数。
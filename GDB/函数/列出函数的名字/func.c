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
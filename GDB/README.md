# GDB

## core dump
```shell
ulimit -c unlimited
```

```c
#include <stdio.h>
int main()
{
    int *a = NULL;
    *a = 0x1;
    return 0;
}
```

```
gcc -g test.c
./a.out
gdb ./a.out core
(gdb) bt
#0  0x0000564d93e4f60a in main () at test.c:5
(gdb) list 
1	#include <stdio.h>
2	int main()
3	{
4	    int *a = NULL;
5	    *a = 0x1;
6	    return 0;
7	}
```
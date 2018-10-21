# Sanitizers

## address sanitizer
```cpp
#include <string>

int main()
{
    const char *names[] = { "bob", "fred" };
    std::string last_arg = names[3];
    return last_arg.size();
}
```

### gcc
首先用gcc编译器：
```shell
$ g++ address.cpp
$ ./a.out
```
```shell
$ g++ address.cpp -Wall -Werror
$ ./a.out
```
依旧没输出，加上`-fsanitize=address`之后：
```shell
$ g++ address.cpp -Wall -Werror -fsanitize=address
$ ./a.out
=================================================================
==29068==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7fffcb0e9628 at pc 0x561169164fea bp 0x7fffcb0e95a0 sp 0x7fffcb0e9598
READ of size 8 at 0x7fffcb0e9628 thread T0
    #0 0x561169164fe9 in main /home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/address.cpp:6
    #1 0x7f1fec3c2a86 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21a86)
    #2 0x561169164dc9 in _start (/home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/a.out+0xdc9)

Address 0x7fffcb0e9628 is located in stack of thread T0 at offset 120 in frame
    #0 0x561169164eb9 in main /home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/address.cpp:4

  This frame has 3 object(s):
    [32, 33) '<unknown>'
    [96, 112) 'names' <== Memory access at offset 120 overflows this variable
    [160, 192) 'last_arg'
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/address.cpp:6 in main
Shadow bytes around the buggy address:
  0x100079615270: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100079615280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100079615290: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000796152a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000796152b0: 00 00 00 00 00 00 f1 f1 f1 f1 01 f2 f2 f2 f2 f2
=>0x1000796152c0: f2 f2 00 00 f2[f2]f2 f2 f2 f2 00 00 00 00 f3 f3
  0x1000796152d0: f3 f3 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000796152e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000796152f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100079615300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100079615310: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==29068==ABORTING
```

### clang
```shell
$ clang++ address.cpp -Wall -Werror
address.cpp:6:28: error: array index 3 is past the end of the
      array (which contains 2 elements) [-Werror,-Warray-bounds]
    std::string last_arg = names[3];
                           ^     ~
address.cpp:5:5: note: array 'names' declared here
    const char *names[] = { "bob", "fred" };
    ^
1 error generated.
```
加上加上`-fsanitize=address`之后输出也是一样：
```shell
$ clang++ address.cpp -Wall -Werror -fsanitize=address -g
address.cpp:6:28: error: array index 3 is past the end of the
      array (which contains 2 elements) [-Werror,-Warray-bounds]
    std::string last_arg = names[3];
                           ^     ~
address.cpp:5:5: note: array 'names' declared here
    const char *names[] = { "bob", "fred" };
    ^
1 error generated.
```


## memory sanitizer
```cpp
#include <iostream>

void set_val(bool &b, const int val)
{
    if(val > 1) {
        b = false;
    }
}

int main(const int argc, const char *[])
{
    bool b;
    set_val(b, argc);
    if(b) {
        std::cout << "value set\n";
    }
}
```

### gcc
```shell
$ g++ memory.cpp
$ ./a.out
$ g++ memory.cpp -Wall -Wextra
$ ./a.out
```
g++没有`-fsanitize=memory`这个选项，只有`address`和`thread`：
```shell
$ g++ memory.cpp -Wall -Wextra -fsanitize=memory
g++: error: unrecognized argument to -fsanitize= option: ‘memory’
```

## clang
```shell
$ clang++ memory.cpp -Wall -Wextra
$ ./a.out
```

加上了`fsanitize=memory`之后：
```shell
$ clang++ memory.cpp -Wall -Wextra -fsanitize=memory
$ ./a.out
==2216==WARNING: MemorySanitizer: use-of-uninitialized-value
    #0 0x493c4b  (/home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/a.out+0x493c4b)    #1 0x7f101a44ea86  (/lib/x86_64-linux-gnu/libc.so.6+0x21a86)
    #2 0x41d329  (/home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/a.out+0x41d329)

SUMMARY: MemorySanitizer: use-of-uninitialized-value (/home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/a.out+0x493c4b)
Exiting
```

如果要知道在哪行出了问题：
```shell
$ MSAN_SYMBOLIZER_PATH=/usr/lib/llvm-4.0/bin/llvm-symbolizer ./a.out
==7959==WARNING: MemorySanitizer: use-of-uninitialized-value
    #0 0x493c4b in main /home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/memory.cpp:14:8
    #1 0x7f9345ae6a86 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21a86)
    #2 0x41d329 in _start (/home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/a.out+0x41d329)

SUMMARY: MemorySanitizer: use-of-uninitialized-value /home/liu/Desktop/note/C++/Cpp-Weekly/Sanitizers/memory.cpp:14:8 in main
Exiting
```
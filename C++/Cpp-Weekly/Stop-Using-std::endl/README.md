# 小心使用std::endl

## std::endl实际做了什么
```cpp
<< std::endl;
```
相当于
```cpp
<< '\n' << std::flush;
```


## helloworld1.cpp
```cpp
#include <iostream>
#include <fstream>

void writeln(std::ostream &os, const std::string &str) {
    os << str << std::endl;
}

int main()
{
    std::ofstream outfile("output.txt", std::ios_base::trunc);

    for(int i = 0; i < 1000000; ++i) {
        writeln(outfile, "Hello World");
    }
}
```

编译：
```shell
$ g++ helloworld1.cpp
```
计算运行时间：
```shell
$ time ./a.out
./a.out  0.26s user 1.61s system 99% cpu 1.870 total
```

## helloworld2.cpp
```cpp
#include <iostream>
#include <fstream>

void writeln(std::ostream &os, const std::string &str) {
    os << str << "\n";
}

int main()
{
    std::ofstream outfile("output.txt", std::ios_base::trunc);

    for(int i = 0; i < 1000000; ++i) {
        writeln(outfile, "Hello World");
    }
}
```
仅仅是将`std::endl`改成`"\n"`


编译：
```shell
$ g++ helloworld2.cpp
```
计算运行时间：
```shell
$ time ./a.out
./a.out  0.08s user 0.01s system 99% cpu 0.091 total
```
可以看出来时间少了很多


将`"\n"`改为`'\n`后编译，计算运行时间
```shell
$ time ./a.out
./a.out  0.07s user 0.01s system 99% cpu 0.084 total
```
将字符串改为一个字符，时间也会少一些

## 总结
`std::endl`等同于`'\n' << std::flush`，因此，除非你确定你这么干，否则不要那么做
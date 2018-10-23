# CMake

## main.cpp
```cpp
#include <iostream>
#include <functional>

int main()
{
    [out = std::ref(std::cout << "Hello ")](){ out.get() << "World\n"; }();
}
```


## CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.5)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(intro main.cpp)
target_compile_features(intro PRIVATE cxx_lambda_init_captures)
```

## 编译运行
```shell
$ mkdir build
$ cd build
$ cmake ..

$ make

$ ./intro
Hello World
```
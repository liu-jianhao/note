# C++11新特性

## nullptr
+ `nullptr`用来表示一个指针指向所谓的`no value`
+ C++保证`NULL`其实就是`0`(其类型可以使`int`也可以是`long`)
+ C语言中的`NULL`通常定义为`(void*)0`，这在C++中并不明确，NULL必须是个整数类型，否则你无法将`NULL`赋值给一个指针。这是因为C++中并没有定义从`void*`到任何其他类型的自动类型转换操作。
+ 从C++11开始应该使用`nullptr`取代`NULL`

## auto类型自动推导

## 一致性初始化与初值列
+ 一致性初始化意思是面对任何初始化动作，你可使用相同的语法，也就是使用大括号
```cpp
int values[] { 1, 2, 3 };
std::vector<int> v{ 2, 3, 4, 5 };
```
+ 初始列会强迫即使某个本地变量属于某种基础类型也会被初始化为0(或nullptr，如果是指针的话)
```cpp
int j{}; // j被初始化为0
int* q{} // q被初始化为nullptr
```
+ 窄化(精度降低)对于大括号而言是不可成立的
```cpp
int x1(5.3);    // OK，x1为5
int x2 = 5.3；  // OK, x2为5
int x3{5.3}；   // ERROR
```

## Range-Based for 循环
```cpp
for (decl : col) {
    statement
}
```


## Move语义
可以避免拷贝和临时对象
```cpp
class X {
    public:
        X(const X& lvalue); // 复制构造函数
        X(X&& rvalue);      // 移动构造函数
        ...
}
```
举个例子，`string`的move构造函数只是将既有的内部字符数组赋予新对象，而非建立一个新数组然后复制所有元素

如果move构造函数不存在，copy构造函数将会被用上

## 新式的字符串字面常量
Raw string 允许我们定义字符序列，例如两个反斜线和一个`n`
```cpp
"\\\\n"
R"(\\n)"
```
语法：`R"delim(...)delim"`，`delim`是个字符序列

定义正则表达式时很有用


## noexcept
指明某个函数无法或不打算抛出异常

`void foo() noexcept;`

声明了`foo()`不打算抛出异常。若有异常未在`foo()`内被处理——即如果`foo()`抛出异常程序会被终止

## constexpr
`constexpr`让表达式核定与编译期。例如
```cpp
constexpr int square(int x)
{
    return x*x;
}
float a[square(9)]; // OK，since C++11
```

## 新的Template特性
+ 可以接受不定个数的template实参
+ 带有别名的模板
+ 默认的template实参


## Lambda

### Lambda的语法
```cpp
// 带参数的lambda
auto l = [] (const std::string& s) {
            std::cout << s << std::endl;
        };
l("hello");

// [=]，可读，值传递
// [&]，可写，引用传递
auto qqq = [x, &y] {
            std::cout << x << std::endl;
            std::cout << y << std::endl;
            ++y; // OK
        };
// 也可以写[=, &y]，表示除了y之外其他参数都是值传递
```

### Lambda的类型
Lambda的类型是个不具名的functor。每个lambda表达式的类型都是独一无二的，如果想根据该类型声明对象，可借助于`template`和`auto`。如果实在需要需要写下该类型，可以使用`decltype`

返回类型为lambda的唯一方法：
```cpp
std::function<int(int, int)> returnLambda()
{
    return [] (int x, int y) {
                return x * y;
            };
}
```


## decltype
让编译器找出表达式类型
```cpp
std::map<std::string, float> coll;
decltype(coll)::value_type elem;
```


## 新的函数声明语法
可以将一个函数的返回类型转而声明与参数列之后
```cpp
template<typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x+y);
```

## 新的基础类型
+ `char16_t`和`char32_t`
+ `long long`和`unsigned long long`
+ `std::nullptr_t`
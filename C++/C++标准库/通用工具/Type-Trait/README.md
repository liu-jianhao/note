# Type Trait

## 目的
type trait 提供一种用来处理type属性的方法，它是个template，可在编译期根据一个或多个template实参产出一个type或value

```cpp
template<typename T>
void foo(const T& val)
{
    if(std::is_pointer<T>::value)
    {
        ...
    }
    else
    {
        ...
    }
}
```
`is_pointer<T>`用来检查T是否个pointer type。产出的是type true_type 或是 type false_type，而 ::value 产出的是true 或是 false。

```cpp
template<typename T>
void foo_impl(const T& val, std::true_type)
{
    ...
}

template<typename T>
void foo_impl(const T& val, std::false_type)
{
    ...
}

template<typename T>
void foo(const T& val)
{
    foo_impl(val, std::is_pointer<T>());
}
```

`type trait`是泛型代码的基石


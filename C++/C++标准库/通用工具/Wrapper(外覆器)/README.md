# Wrapper

## Reference Wrapper
声明于<functional>中
```cpp
template<typename T>
void foo(T val);

int x;
foo(std::ref(x)); // T变成int&

foo(std::cref(x)); // T变成coonst int&
```

`class reference_wrapper`使你能够使用reference作为最高级对象，例如作为stl容器的元素类型：
```
std::vector<MyClass&> coll; // ERROR
std::vector<std::reference_wrapper<MyClass>> coll; // OK
```

## Function Type Wrapper
```cpp
void func(int x, int y);

// 初始化任务集合
std::vector<std::function<void(int, int)>> tasks;
tasks.push_back(func);
tasks.push_back([] (int x, int y){
    ...
});

// 调用
for(std:function<void(int, int)>f : tasks){
    f(2, 3);
}
```
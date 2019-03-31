# C++内存管理

## C++内存原语
![](https://img-blog.csdnimg.cn/20190102084333121.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

### new 表达式
1. operator new
    + malloc
2. static_cast
3. 构造函数(只有编译器可以直接调用)

![](https://img-blog.csdnimg.cn/20190102084948788.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

malloc调用失败，会调用`new handler`，这个函数是你设定的。


### delete
1. 析构函数(可以直接调用)
2. operator delete
    + free
![](https://img-blog.csdnimg.cn/20190102085253612.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

### array new & array delete
![](https://img-blog.csdnimg.cn/20190102090203323.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

如果用`new []`，之后没有用`delete []`，而用`delete`，
不一定会发生内存泄露，要看对象的析构函数是否是是trivial的，
如果是`trivial`的，即不重要的，就不会泄露

### placement new
placement new 不分配内存，相当于调用构造函数
![](https://img-blog.csdnimg.cn/20190103175723610.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


## C++内存管理流程
+ 全局的operator new
+ placement new

![](https://img-blog.csdnimg.cn/20190103182013354.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

![](https://img-blog.csdnimg.cn/20190103182020853.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


## malloc
![](https://img-blog.csdnimg.cn/20190104133908859.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

+ 浅蓝色的是想要的空间的大小
+ cookie是整个的大小
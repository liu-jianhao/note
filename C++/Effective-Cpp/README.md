# 学习笔记

## item02：尽量以const、enum、inline替换#define
+ 对于单纯变量，最好以`const`对象或`enums`替换`#define`
+ 对于形似函数的宏，最好改用`inline`替换`#define`


## item03：尽量用const

## item04：确定对象在被使用前已被初始化
+ 构造函数最好使用成员初值列，而不要在构造函数体内使用赋值操作。
+ 初值列列出的成员变量，其排列次序应该和它们在class中的声明次序相同。

## item07：为多态基类声明virtual析构函数
+ 带有多态性质的基类应该声明一个虚析构函数。如果类带有任何虚函数，它就应该拥有一个虚析构函数。

## item08：别让异常逃离析构函数
+ 析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，
析构函数应该捕捉任何异常，然后吞下它们或结束程序。

## item09：绝不在构造和析构过程中调用虚函数
+ 在构造和析构期间不要调用虚函数，因为这类调用不下降至继承类。

## item10：令operator=返回一个reference to *this

## item11：在operator=中处理自我赋值


## item13：以对象管理资源
+ 为防止资源泄露，使用RAII对象，它们在构造函数中获得资源并在析构函数中释放资源。

## item14：在资源管理类中小心复制行为
+ 当一个RAII对象被复制时，会发生什么？
    1. 禁止复制
    2. 对底层资源使用引用计数法

## item15：在资源管理类中提供对原始资源的访问

## item16：成对使用new和delete时要采用相同形式


## item18：让接口容易被正确使用，不易被误用

## item19：设计class犹如设计type

## item20：宁以pass-by-reference-to-const替换pass-by-value
+ 这个规则并不适用内置类型，以及STL的迭代器和函数对象，对它们而言pass-by-value往往更合适


## item21：必须返回对象时，别妄想返回其reference
+ 绝不要返回pointer或reference指向一个本地栈对象，或返回reference指向一个堆对象，
或返回pointer或reference指向一个本地static对象而可能同时需要多个这样的对象


## item22：将成员变量声明为private

## item23：宁以非成员函数、非友元函数替代成员函数

## item24：若所有参数需要类型转换，请使用非成员函数

## item25：写一个不抛异常的swap函数


## item25：尽量延后变量定义式出现的时间

## item26：尽量少做转型操作
+ const_cast：只有它能将const转为non const
+ dynamic_cast：用来决定某对象是否归属继承体系中的某个类型
    + 性能差
    + 之所以需要dynamic_cast，通常是因为你想在一个你认定为继承类对象身上执行继承类操作函数，
    但你的手上却只有一个指向基类的指针或引用
+ reinterpret_cast：意图执行低级转型，实际动作可能取决于编译器
+ static_cast：强迫隐式转换

## item28：避免返回handles指向对象内部成分
+ 避免返回handles（包括references、指针、迭代器）指向对象内部

## item29：为异常安全而努力是值得的

## item30：透彻了解inlining的里里外外

## item31：将文件间的编译依存关系降至最低

## item32：确定public继承是is-a关系

## item33：避免遮盖继承而来的名称
+ 继承类内的名称会遮掩基类内的名称
+ 为了让被遮掩的名称重见天日，可使用using声明式或转交函数


## item34：区别接口继承和实现继承
+ 声明一个纯虚函数的目的是为了让继承类只继承函数接口
    + 继承类必须实现
+ 声明非纯虚函数的目的是让继承类继承该函数的接口和缺省实现
    + 继承类可能覆写
+ 声明非虚函数的目的是为了令继承类继承函数的接口及一份强制型实现

## item35：考虑虚函数之外的选择
+ 使用non-virtual interface(NVI)手法，是Template Method设计模式的一种特殊形式。
它以public non-virtal成员函数包裹较低访问性的virtual函数
+ 将virtual函数替换为函数指针成员变量，这是Strategy设计模式的一种分解形式
+ 将继承体系内的virtual函数替换为另一个继承体系内的virtual函数。这是strategy模式的传统实现手法


## item36：绝不重新定义继承而来的non-virtual函数

## item37：绝不重新定义继承而来的缺省参数值

## item38：明智而审慎地使用private继承

## item38：明智而审慎地使用多重继承
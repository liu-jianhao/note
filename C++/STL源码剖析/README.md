目录：
+ [分配器](##分配器)
+ [List](##list)
+ [Traits](###traits)
+ [迭代器](###迭代器)
+ [Vector](##vector)
+ [array](##array)
+ [Deque](##deque)
    + [queue&stack](###queue&stack)
+ [红黑树](##红黑树)
    + [Set](###set)
    + [Map](###map)
+ [hashtable](##hashtable)
+ [算法](##算法)
+ [仿函数](##仿函数)
+ [tuple](##tuple)


# Part1
## STL六大部件

![](https://img-blog.csdnimg.cn/20181213212615508.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

## 容器内部结构
+ set/multiset & map/multimap 内部用红黑树
+ unordered_set/map/multiset/multimap 内部用哈希表
    + 桶个数比元素个数多，一旦元素个数和桶个数相同时会进行×2扩容，并重哈希

![](https://img-blog.csdnimg.cn/20181213212816750.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

## gunc独有的分配器
![](https://img-blog.csdnimg.cn/20181213213220826.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


# Part2
## OOP和GP(泛型编程)
+ OOP试图将data和methods关联在一起
+ GP是将data和methods分开来
    + containers和algorithms可以通过iterator沟通
    + algorithms通过iterators确定范围，并通过iterators取用container元素

## 分配器
### operator new 和 malloc
operator new最终都会调用到malloc。

malloc会分配如下的空间：
![](https://img-blog.csdnimg.cn/201812140757429.png)
浅蓝色即我们真正想要的空间，其他的都是额外开销。

请求的区块小则开销大。

想法：怎么减少malloc的次数，即减小额外开销。

### gnuc2.9
每一块以8为倍数增长
![](https://img-blog.csdnimg.cn/20181214080834687.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


### gunc4.9
改为没有特殊设计的allocator，之前2.9的特殊设计的allocator改为`__pool_alloc`。


## list
### list 源码 gunc2.9
![](https://img-blog.csdnimg.cn/20181214232636699.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

gunc4.9复杂难理解

### list 迭代器
![](https://img-blog.csdnimg.cn/2018121423331916.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


## 迭代器
![](https://img-blog.csdnimg.cn/20181215085359788.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)
上面的rotate算法需要知道迭代器的迭代器的三种类型。
+ value_type:元素类型
+ difference_type:距离类型
+ iterator_category:迭代器类型

![](https://img-blog.csdnimg.cn/20181215090102728.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

问题：如果迭代器不是一个类，而是一个原生指针，要怎么知道这些type呢？
答：这就需要萃取机了。

### traits
它必须能区别迭代器是一个类还是一个指针。

![](https://img-blog.csdnimg.cn/20181215090426179.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


利用模板特化，可以萃取出传入的类型是迭代器还是指针：
![](https://img-blog.csdnimg.cn/20181215090935435.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


迭代器萃取机只是萃取机的一个部分，还有很多其它类型的萃取机：
+ type traits
+ char traits
+ allocator traits
+ pointer traits
...


## vector
+ 二倍增长
    + 需要拷贝，即需要析构和构造
    + ![](https://img-blog.csdnimg.cn/20181215121321368.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)
+ 三个指针
    + start
    + finish
    + end_of_storage
    + ![](https://img-blog.csdnimg.cn/20181215121402376.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)



## array
+ 为了享受算法，所以构造出这个类
+ 没有构造和析构函数
+ 数组存储

## deque
![](https://img-blog.csdnimg.cn/20181215171210549.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

deque看上去是连续的，实际上是因为其迭代器的功劳：
+ cur指向当前元素
+ first指向当前指向的元素所在的那块buffer的头
+ last指向当前指向的元素所在的那块buffer的尾
+ node指向所在buffer在控制块(实际上是vector)的位置

![](https://img-blog.csdnimg.cn/20181215172144255.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


### queue&stack
+ 容器适配器
+ 以deque为默认的底层容器
+ 也可以以list为底层容器
+ stack可以以vector为底层容器，queue不可以（pop会有问题）
+ stack和queue都不可以set或map作为底层容器
+ 不支持迭代器，也不支持遍历


## 红黑树
![](https://img-blog.csdnimg.cn/20181216085236528.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

### 标准库中的红黑树
![](https://img-blog.csdnimg.cn/20181216085739306.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

模板参数：
+ Key：红黑树节点中的某个值，用以排序
+ Value：红黑树节点的类型
+ KeyOfValue：怎么取出Value中的Key
+ Compare：怎么比较Key的大小
+ Alloc：默认alloc分配器

### set
[](https://img-blog.csdnimg.cn/20181216122954870.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

可以遍历，但不可以修改

set源代码：
![](https://img-blog.csdnimg.cn/20181216123513781.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)
注意到上面的迭代器是const的，所以不可以修改其中的元素

### map
![](https://img-blog.csdnimg.cn/20181216123513781.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

可以遍历，但不可以修改key，但可以修改value

map源码：
![](https://img-blog.csdnimg.cn/20181216123938870.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)
+ select1st：作用是从value中选择第一个元素为key。
+ 注意pair中的第一个元素为const，所以key不可以修改


multimap不支持[]运算符，只有map支持
![](https://img-blog.csdnimg.cn/20181216124755163.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)
注意上面的lower_bound。


## hashtable
![](https://img-blog.csdnimg.cn/20181216130925831.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)



## 算法
算法看不见容器，他所需要的一切信息都必须从迭代器取得。

### 五种迭代器的分类：
![](https://img-blog.csdnimg.cn/20181217133935518.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

+ random_access_iterator_tag:array,vector,deque
+ bidrection_iterator_tag:list,set,map,multiset,multimap
+ forward_iterator_tag:forward_list,unordered_*


为什么迭代器类型要用类？
+ 方便函数重载，对于不同的迭代器类型有不同的操作
+ 各种迭代器是继承关系，不同操作就可以不用针对每一个类型都写

以copy为例：
![](https://img-blog.csdnimg.cn/20181218133730549.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

### 算法例子
本身容器有的算法，就不要用全局的算法。
![](https://img-blog.csdnimg.cn/20181218150049174.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

![](https://img-blog.csdnimg.cn/20181218150055804.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

![](https://img-blog.csdnimg.cn/20181218150111727.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

## 仿函数
![](https://img-blog.csdnimg.cn/20181218151850714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

## tuple
递归继承，类似于erlang的递归
![](https://img-blog.csdnimg.cn/20181231233140202.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)


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


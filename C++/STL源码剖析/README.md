
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
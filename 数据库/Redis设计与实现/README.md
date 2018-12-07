# Redis数据结构

## 跳跃表简介
+ 跳跃表是一种有序的数据结构，他通过在每个节点中维持多个指向其他节点的指针，从而达到快速访问节点的目的。
+ 跳跃表支持平均O(logN)、最坏O(N)复杂度的节点查找，还可以通过顺序性操作来批量处理节点
+ Redis使用跳跃表作为有序集合键的底层实现之一，如果有序集合包含的元素数量比较多，又或者有序集合中元素的成员是比较长的字符串，Redis就会使用跳跃表作为有序集合键的地底层实现

### 跳跃表的实现
+ `redis.h/zskiplist`结构则用于保存跳跃表节点的相关信息：

+ `redis.h/zskiplistNode`结构用于表示跳跃表节点


### `redis.h/zskiplistNode`
```c
typedef struct zskiplistNode {
	// 层
	struct zskiplistLevel {
		// 前进指针
		struct zskiplistNode *forward;
		// 跨度
		unsigned int span;
	} level[];

	// 后退指针
	struct zskiplistNode *backward;
	// 分值
	double score;
	// 成员对象
	robj *obj;
} zskiplistNode;
```
1. 层（level）：每个层带有两个属性：前进指针和跨度。
前进指针用于访问位于表尾方向的其他节点，而跨度则记录了前进指针所指向节点和当前节点的距离。
2. 后退指针：指向当前节点的前一个节点。在从表尾想表头遍历时使用
3. 分值：节点按各自所保存的分值从小到大排列
4. 成员对象：


### `redis.h/zskiplist`
```c
typedef struct zskiplist {
	// 表头节点和表尾节点
	struct skiplistNode *header, *tail;

	// 表中节点的数量
	unsigned long length;

	// 表中层数最大的节点的层数
	int level;
} zskiplist;
```

1. header：指向跳跃表的表头结点
2. tail：指向跳跃表的表尾节点
3. level：记录目前跳跃表内，层数最大的那个节点的层数
4. length：记录跳跃表的长度，也即是跳跃表目前包含节点的数量


## 整数集合简介
整数集合是集合键的底层实现之一，当一个集合只包含整数值元素，并且这个集合的元素数量不多时，Redis就会使用整数集合作为集合键的底层实现

### 实现
整数集合是Redis用于保存整数值的集合抽象数据结构，它可以保存类型为`int16_t`、`int32_t`、`int64_t`的整数值，并且保证集合中不会出现重复元素。
`intset.h/intset`
```c
typedef struct intset {
	// 编码方式
	uint32_t encoding;
	// 集合包含的元素数量
	uint32_t length;
	// 保存元素的数组
	int8_t contents[];
} intset;
```
+ `contents`数组是整数集合的底层实现：整数集合的每个元素都是`contents`数组的一个数组项，每个项在数组中按值的大小从小到大有序地排列，并且数组中不包含任何重复项
+ `length`属性记录了整数集合包含的元素数量，也即是`contents`数组的长度

### 升级
每当我们要将一个新元素添加到整数集合里面，并且新元素的类型比整数集合现有所有元素的类型都要长时，整数集合就需要先进行升级，然后才能将新元素添加到整数集合里面

#### 升级的好处
1. 提升灵活性
2. 节约内存

### 降级
整数集合不支持降级，升级之后就一直保持


## 压缩列表简介
压缩列表是列表键和哈希键的底层实现之一。
是为了节约内存而开发的顺序型数据结构。

### 压缩列表的构成
压缩列表是Redis为了节约内存而开发，是由一系列特殊编码的连续内存块组成的顺序型数据结构。一个压缩列表可以包含任意多个节点，每个节点可以保存一个字节数组或者一个整数值。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20181207202947652.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)



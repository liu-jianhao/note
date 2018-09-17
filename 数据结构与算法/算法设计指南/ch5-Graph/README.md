# 图

## 图的风格
+ 无向与有向
+ 加权与无权
+ 简单和非简单
    + 自圈指仅涉及一个顶点的边，也就是(x, x)
    + 边(x, y)在图中出现不止一次，称该边为多重边
    + 有上述结构的为非简单图
+ 稀疏与稠密
+ 有环与无环
+ 嵌入与拓扑
+ 隐式与显式
    + 有些图是随用随建的。回溯算法就是这样
+ 有标与无标
    + 有标图中的每个顶点都会有唯一的名字或标识


## 图的数据结构
1. 邻接矩阵

2. 邻接图

```c
#define MAXV    1000

typedef struct {
    int y;      // 邻接信息
    int weight; // 边的权值
    struct edgenode *next;  // 列表中下一条边
} edgenode;

typedef struct {
    edgenode *edges[MAXV+1];    // 邻接信息
    int degree[MAXV+1];         // 每个顶点的出度
    int nvertices;              // 图中的顶点数
    int nedges;                 // 图中的边数
    bool directed;              // 此图是否有向
} graph;


void initialize_graph(graph *g, bool directed);
void read_graph(graph *g, bool directed);
void insert_edge(graph *g, int x, int y, bool directed);
void print_graph(graph *g);

void print_graph(graph *g);
void bfs(graph *g, int start);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int x, int y);
void find_path(int start, int end, int parents[]);

void initialize_graph(graph *g, bool directed) {
    int i;
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;
    for(i = 1; i <= MAXV; i++) {
        g->degree[i] = 0;
    }
    for(i = 1; i <= MAXV; i++) {
        g->edges[i] = NULL;
    }
}


void read_graph(graph *g, bool directed) {
    int i;
    int m;
    int x, y;

    initialize_graph(g, directed);
    scanf("%d %d", &(g->nvertices), &m);
    for(i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        insert_edge(g, x, y, directed);
    }
}

void insert_edge(graph *g, int x, int y, bool directed) {
    edgenode *p;

    p = malloc(sizeof(edgenode));

    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;

    g->degree[x]++;

    if(directed == false) {
        insert_edge(g, y, x, true);
    } else {
        g->nedges++;
    }
}

void print_graph(graph *g) {
    int i;
    edgenode *p;

    for(i = 1; i <= g->nvertices; i++) {
        printf("%d: ", i);
        p = g->edges[i];
        while(p != NULL) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}
```

## 遍历图
每个顶点都处于一下三种状态之一：
+ 未发现
+ 已找到
+ 处理完

### 广度优先搜索
图中每个节点的状态都会遍历过程中的某一时刻，从`未发现`到`已找到`

在无向图的广度优先搜索中，我们会给每条边指定一个方向，如果顶点`u`找到了顶点`v`，那么边的方向就是从`u`到`v`，因此将`u`记为`v`的父亲

因此一个无向图可以定义为一棵树，该树确定了树中从根到其他所有节点的最短路径


```c
bool processed[MAXV+1];     // 处理完
bool discovered[MAXV+1];    // 已找到
int parent[MAXV+1];


void initialize_search(graph *g) {
    int i;
    for(i = 1; i <= g->nvertices; i++) {
        processed[i] = discovered[i] = false; // 初始化为未发现
        parent[i] = -1;
    }
}

void bfs(graph *g, int start) {
    queue q;
    int v;      // 当前顶点
    int y;      // 下一个顶点
    edgenode *p;

    init_queue(&q);
    enqueue(&q, start);
    discovered[start] = true;

    while(empty_queue(&q) == false) {
        v = dequeue(&q);
        process_vertex_early(v);
        processed[v] = true;
        p = g->edges[v];
        while(p != NULL) {
            y = p->y;
            if((processed[y] == false) || g->directed) {
                process_edge(v, y);
            }
            if(discovered[y] == false) {
                enqueue(&q, y);
                discovered[y] = true;
                parent[y] = v;
            }
            p = p->next;
        }
        process_vertex_late(v);
    }
}
```

#### 遍历的功用
`bfs`的具体执行结果取决于下面的三个函数，不同的算法在遇到顶点或边时会有不同的处理方案，因此我们可以自由定制
```c
void process_vertex_early(int v) {

}

void process_vertex_late(int v) {
    printf("processed vertex %d\n", v);
}

void process_edge(int x, int y) {
    printf("processed edge (%d, %d)\n", x, y);
}
```


#### 寻找路径
`parent`数组对寻找图中某些特殊路径来说非常有用，路径就是图中所有从根到x路径中边数最少的

我们可以通过追随x到根的祖先链来重建上述路径，因此可以用递归
```c
void find_path(int start, int end, int parents[]) {
    if((start == end) || end == -1) {
        printf("\n%d", start);
    } else {
        find_path(start, parents[end], parents);
        printf(" %d", end);
    }
}
```
使用广度优先搜索寻找从x到y的最短路径时，要注意两点：
1. 最短路径树只在广度优先搜索将x设为搜索的根去执行才会发挥作用
2. 广度优先搜索只能对无权图给出最短路径


#### 广度优先搜索的引用
##### 连通分量
无向图的连通分量是满足任意顶点间都存在路径的一个最大项子集

顶点的次序对分量而言不重要，所以我们可用广度优先搜索去找连通分量
```c
void conected_components(graph *g) {
    int c;
    int i;

    initialize_search(g);
    c = 0;
    for(i = 1; i <= g->nvertices; i++) {
        if(discovered[i] == false) {
            c++;
            printf("Component %d:", c);
            bfs(g, i);
            printf("\n");
        }
    }
}

void process_vertex_early(int v) {
    printf(" %d", v);
}

void process_edge(int x, int y) {

}
```


##### 双色图
我们可以扩充广度优先搜索的功能，让它再找到新顶点时对该点涂上与其父亲相反的颜色

对于那些没找到新顶点的边，我们检查它是否连接了两个同色顶点，要是有的话则意味着图不能分涂二色

```c
void twocolor(graph *g) {
    int i;
    for(i = 1; i <= g->nvertices; i++) {
        color[i] = UNCOLORED;
    }
    bipartite = true;
    initialize_serrch(&g);
    for(i = 1; i <= g->nvertices; i++) {
        if(discovered[i] == false) {
            color[i] = WHITE;
            bfs(g, i);
        }
    }
}

void process_edge(int x, int y) {
    if(color[x] == color[y]) {
        bipartite = false;
        printf("Warning: not bipartite due to (%d %d)\n", x, y);
    }
    color[y] = complement(color[x]);
}

int complement(int color) {
    if(color == WHITE)
        return BLACK;
    if(color == BLACK)
        return WHITE;
    return UNCOLORED;
}
```


### 深度优先搜索
我们的`dfs`实现为每个顶点引入了一个概念称为遍历时间并对其实时维护，每当我们进入或离开任意顶点时，我们的`time`时钟就会走一格，对每一个顶点我们都会记录进入时间和离开时间

时间差值的一半就是`v`的子孙数

深度优先搜索的一个重要特性就是它将无向图的边分为两类：树边和反向边

+ 数边会找到新顶点，而这种父子关系记录在`parent`数组中

+ 反向边中一个端点是当前正在进行扩展的顶点，而另一个端点则是该顶点的祖先，所以这种边会指回到树中而不是扩展出新顶点



```c
int entry_time[MAXV+1];
int exit_time[MAXV+1];
int time;           
bool finished = false;

void dfs(graph *g, int v) {
    edgenode *p;
    int y;

    if(finished)
        return;

    discovered[v] = true;
    time++;
    entry_time[v] = time;

    process_vertex_early(v);

    p = g->edges[v];
    while(p != NULL) {
        y = p->y;
        if(discovered[y] == false) {
            parent[y] = v;
            process_edge(v, y);
            dfs(g, y);
        } else if((!processed[y]) || (g->directed)) {
            process_edge(v, y);
        }
        if(finished)
            return;
        p = p->next;
    }

    process_vertex_late(v);
    time++;
    exit_time[v] = time;

    processed[v] = true;
}
```

#### 深度优先搜索的应用
##### 寻找环
反向边是无向图中寻找环的关键，如果没有反向边那么所有边都是树边，而树中不存在环

只要从`x`到其祖先`y`的反向边，就会创建一个包含`y`到`x`路径的环

```c
void process_edge(int x, int y) {
    if(discoverd[y] && (parent[x] != y)) {
        printf("Cycle from %d to %d:", y, x);
        find_path(y, x, parent);
        printf("\n\n");
        finished = true;
    }
}
```
处理每条无向边仅在第一次遇到时检测处理，否则任意一条无向边的两次遍历都能建立一个两顶点假环(x, y, x)


#### 关节点
连通度描述了图中最少需要删除多少个顶点能让图断开

关节点的连通度是1


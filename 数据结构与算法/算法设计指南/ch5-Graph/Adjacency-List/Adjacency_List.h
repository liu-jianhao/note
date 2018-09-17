#ifndef __ADJACENCY_LIST__H
#define __ADJACENCY_LIST__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


void process_vertex_early(int v) {

}

void process_vertex_late(int v) {
    printf("processed vertex %d\n", v);
}

void process_edge(int x, int y) {
    printf("processed edge (%d, %d)\n", x, y);
}


void find_path(int start, int end, int parents[]) {
    if((start == end) || end == -1) {
        printf("\n%d", start);
    } else {
        find_path(start, parents[end], parents);
        printf(" %d", end);
    }
}


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

#endif
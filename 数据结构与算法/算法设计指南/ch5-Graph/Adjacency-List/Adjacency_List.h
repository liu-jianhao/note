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

#endif
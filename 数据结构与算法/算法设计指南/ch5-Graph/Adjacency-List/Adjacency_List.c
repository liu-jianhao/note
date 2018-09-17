#include "Adjacency_List.h"

int main() {
    graph *g = malloc(sizeof(graph));
    initialize_graph(g, true);
    
    printf("有向图：\n");
    read_graph(g, true);
    print_graph(g);

    printf("无向图：\n");
    read_graph(g, false);
    print_graph(g);
    return 0;
}
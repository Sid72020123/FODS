/* === Graph [Traversal only], using Adjacency Matrix === */

#include <stdio.h>
#include <stdlib.h>

#include "headers/queue.h"
#include "headers/stack.h"

// === Global Variables / Structures ===

struct Graph
{
    char *vertices_names;
    int *vertices_links;

    int *vertices_visited;

    int vertices_count;
};

struct Queue *MAIN_QUEUE;
struct Stack *MAIN_STACK;

// === Global Variables / Structures ===

struct Graph *createNewGraph(char *vn, int *vl, int size)
{
    struct Graph *newGraph = (struct Graph *)malloc(sizeof(struct Graph));

    newGraph->vertices_count = size;
    newGraph->vertices_names = vn;
    newGraph->vertices_links = vl;
    newGraph->vertices_visited = (int *)calloc(size, sizeof(int));

    return newGraph;
}

int main(void)
{
    int size = 6;
    char vertices_names[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int vertices_links[6][6] = {{0, 1, 1, 0, 0, 0},
                                {1, 0, 0, 1, 0, 0},
                                {1, 0, 0, 0, 1, 0},
                                {0, 1, 0, 0, 1, 0},
                                {0, 0, 1, 1, 0, 1},
                                {0, 0, 0, 0, 1, 0}};
    struct Graph *graph1 = createNewGraph(vertices_names, vertices_links, size);
    return 0;
}
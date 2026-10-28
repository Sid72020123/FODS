/* === Graph [Traversal only], using Adjacency Matrix === */

#include <stdio.h>
#include <stdlib.h>

#include "headers/queue.h"
#include "headers/stack.h"

// === Global Variables / Structures ===

struct Graph
{
    char *vertices_names;
    int **vertices_links;

    int *vertices_visited;

    int vertices_count;
};

struct Queue *MAIN_QUEUE;
struct Stack *MAIN_STACK;

// === Global Variables / Structures ===

struct Graph *createNewGraph(int size, char *vn, int vl[size][size])
{
    // allocate memory to new Graph structure
    struct Graph *newGraph = (struct Graph *)malloc(sizeof(struct Graph));

    // set graph vertices size
    newGraph->vertices_count = size;

    // copy the contents of parameter vn to new array of the same size
    newGraph->vertices_names = (char *)malloc(size * sizeof(char));
    for (int i = 0; i < size; i++)
    {
        newGraph->vertices_names[i] = vn[i];
    }

    // copy the contents of parameter vl to new array of the same size
    newGraph->vertices_links = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        newGraph->vertices_links[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            newGraph->vertices_links[i][j] = vl[i][j];
        }
    }

    // set vertices visited as 0 for each vertex in graph
    newGraph->vertices_visited = (int *)calloc(size, sizeof(int));

    return newGraph;
}

void depthFirstTraverse(struct Graph *graph, char start)
{
    
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
    struct Graph *graph1 = createNewGraph(size, vertices_names, vertices_links);

    return 0;
}
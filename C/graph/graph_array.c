/* === Graph [Traversal only], using Adjacency Matrix === */

#include <stdio.h>
#include <stdlib.h>

// #include "headers/queue.h"
#include "headers/stack.h"

// === Global Variables / Structures ===

struct Graph
{
    char *vertices_names;
    int **vertices_links;

    int *vertices_visited;

    int vertices_count;
};

// struct Queue *MAIN_QUEUE;
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

// === Graph Traversal Methods ===

int get_index(struct Graph *graph, char character, int *result)
{
    if (graph == NULL)
    {
        return 0;
    }

    for (int i = 0; i < graph->vertices_count; i++)
    {
        if (graph->vertices_names[i] == character)
        {
            *result = i;
            return 1;
        }
    }

    return 0;
}

void depthFirstTraverse(struct Graph *graph, char start)
{
    int start_index;
    // get the starting character's index from the vertices names array
    if (!get_index(graph, start, &start_index))
    {
        printf("\n[*] Error getting the index of start character '%c'.\n", start);
        return;
    }

    emptyStack(MAIN_STACK);
    // reset vertices visited booleans for each vertex
    for (int i = 0; i < graph->vertices_count; i++)
    {
        graph->vertices_visited[i] = 0;
    }

    graph->vertices_visited[start_index] = 1;
    push(start_index, MAIN_STACK);

    printf("Depth-first Traverse [start = '%c', index = %d]: ", start, start_index);

    while (!isStackEmpty(MAIN_STACK))
    {
        int traverse;
        pop(&traverse, MAIN_STACK);

        printf("%c ", graph->vertices_names[traverse]);

        for (int i = 0; i < graph->vertices_count; i++)
        {
            if (graph->vertices_links[traverse][i] == 1 && graph->vertices_visited[i] == 0)
            {
                graph->vertices_visited[i] = 1;
                push(i, MAIN_STACK);
            }
        }
    }
    printf("\n");
}

int main(void)
{
    MAIN_STACK = createNewStack("MAIN STACK");

    char graph1_vertices_names[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int graph1_vertices_links[6][6] = {{0, 1, 1, 0, 0, 0},
                                       {1, 0, 0, 1, 0, 0},
                                       {1, 0, 0, 0, 1, 0},
                                       {0, 1, 0, 0, 1, 0},
                                       {0, 0, 1, 1, 0, 1},
                                       {0, 0, 0, 0, 1, 0}};
    struct Graph *graph1 = createNewGraph(6, graph1_vertices_names, graph1_vertices_links);

    depthFirstTraverse(graph1, 'C');
    depthFirstTraverse(graph1, 'E');
    depthFirstTraverse(graph1, 'F');
    return 0;
}
/* === Graph [Traversal only], using Adjacency Lists === */

#include <stdio.h>
#include <stdlib.h>

#include "headers/queue.h"
#include "headers/stack.h"

// === Global Variables / Structures ===

struct Node
{
    int data;
    struct Node *next;
};

struct Graph
{
    char *vertices_names;
    struct Node **vertices_links;
    int vertices_count;

    int *vertices_visited;
};

struct Queue *MAIN_QUEUE;
struct Stack *MAIN_STACK;

// === Graph Traversal Methods ===

struct Graph *createNewGraph(int size, char *vn)
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

    // create the necessary memory space for the vertices_links array
    newGraph->vertices_links = (struct Node **)malloc(size * sizeof(struct Node *));
    for (int i = 0; i < size; i++)
    {
        newGraph->vertices_links[i] = NULL;
    }

    // set vertices visited as 0 for each vertex in graph
    newGraph->vertices_visited = (int *)calloc(size, sizeof(int));

    return newGraph;
}

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

void addLink(struct Graph *graph, char source, char destination)
{
    if (source == destination)
    {
        printf("\n[addLink] A vertex cannot be linked to itself.\n");
    }

    int source_index, destination_index;
    if (!get_index(graph, source, &source_index))
    {
        printf("\n[addLink - Source] Error getting the index of character '%c'.\n", source);
        return;
    }

    if (!get_index(graph, destination, &destination_index))
    {
        printf("\n[addLink - Destination] Error getting the index of character '%c'.\n", destination);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = destination_index;
    newNode->next = NULL;

    struct Node *traverse = graph->vertices_links[source_index]; // start from the source index in the array

    if (traverse == NULL)
    {
        graph->vertices_links[source_index] = newNode;
    }
    else
    {
        // find the empty / last Node
        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newNode;
    }
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
            struct Node *traverseVertex = graph->vertices_links[i];
            while (traverseVertex != NULL)
            {
                if (graph->vertices_visited[traverseVertex->data] == 0)
                {
                    graph->vertices_visited[traverseVertex->data] = 1;
                    push(traverseVertex->data, MAIN_STACK);
                }
                traverseVertex = traverseVertex->next;
            }
        }
    }
    printf("\n");
}

// void breadthFirstTraverse(struct Graph *graph, char start)
// {
//     int start_index;
//     // get the starting character's index from the vertices names array
//     if (!get_index(graph, start, &start_index))
//     {
//         printf("\n[*] Error getting the index of start character '%c'.\n", start);
//         return;
//     }

//     emptyQueue(MAIN_QUEUE);
//     // reset vertices visited booleans for each vertex
//     for (int i = 0; i < graph->vertices_count; i++)
//     {
//         graph->vertices_visited[i] = 0;
//     }

//     graph->vertices_visited[start_index] = 1;
//     enqueue(start_index, MAIN_QUEUE);

//     printf("Breadth-first Traverse [start = '%c', index = %d]: ", start, start_index);

//     while (!isQueueEmpty(MAIN_QUEUE))
//     {
//         int traverse;
//         dequeue(&traverse, MAIN_QUEUE);

//         printf("%c ", graph->vertices_names[traverse]);

//         for (int i = 0; i < graph->vertices_count; i++)
//         {
//             if (graph->vertices_links[traverse][i] == 1 && graph->vertices_visited[i] == 0)
//             {
//                 graph->vertices_visited[i] = 1;
//                 enqueue(i, MAIN_QUEUE);
//             }
//         }
//     }
//     printf("\n");
// }

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    // Graph 1
    char graph1_vertices_names[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    struct Graph *graph1 = createNewGraph(6, graph1_vertices_names);
    addLink(graph1, 'A', 'B');
    addLink(graph1, 'A', 'C');
    addLink(graph1, 'B', 'D');
    addLink(graph1, 'C', 'E');
    addLink(graph1, 'D', 'E');
    addLink(graph1, 'E', 'F');
    depthFirstTraverse(graph1, 'C');
    // breadthFirstTraverse(graph1, 'C');

    // Graph 2
    // char graph2_vertices_names[] = {'A', 'B', 'C', 'D', 'E'};
    // int graph2_vertices_links[5][5] = {{0, 1, 0, 1, 0},
    //                                    {1, 0, 0, 0, 1},
    //                                    {0, 0, 0, 0, 1},
    //                                    {1, 0, 0, 0, 1},
    //                                    {0, 1, 1, 1, 0}};
    // struct Graph *graph2 = createNewGraph(5, graph2_vertices_names, graph2_vertices_links);
    // depthFirstTraverse(graph2, 'C');
    // breadthFirstTraverse(graph2, 'C');

    // // Graph 3
    // char graph3_vertices_names[] = {'A', 'B', 'C', 'D', 'E'};
    // int graph3_vertices_links[5][5] = {{0, 1, 1, 0, 1},
    //                                    {1, 0, 1, 0, 1},
    //                                    {1, 1, 0, 1, 0},
    //                                    {0, 0, 1, 0, 1},
    //                                    {1, 1, 0, 1, 0}};
    // struct Graph *graph3 = createNewGraph(5, graph3_vertices_names, graph3_vertices_links);
    // depthFirstTraverse(graph3, 'C');
    // breadthFirstTraverse(graph3, 'C');
    return 0;
}
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

    int vertices_count;
};

struct Queue *MAIN_QUEUE;
struct Stack *MAIN_STACK;

// === Utilities ===

int get_int_input(const char *prompt, int max_tries, int *result)
{
    int input;
    char extra;
    char buffer[100];
    int tries = 0;

    while (tries < max_tries)
    {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d %c", &input, &extra) == 1)
        {
            *result = input;
            return 1; // SUCCESS
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

int get_char_input(const char *prompt, int max_tries, char *result)
{
    char input;
    char buffer[100];
    int tries = 0;
    char extra;

    while (tries < max_tries)
    {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%c %c", &input, &extra) == 1 && input != '\n')
        {
            *result = input;
            return 1; // SUCCESS
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

// === Graph Traversal Methods ===

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

int addNewVertex(char vertex_name, struct Graph *graph)
{
    if (graph == NULL)
    {
        return 0;
    }

    int old_size = graph->vertices_count;
    int new_size = old_size + 1;

    char *new_vertices_names = (char *)malloc(new_size * sizeof(char));
    int **new_vertices_links = (int **)malloc(new_size * sizeof(int *));

    if (new_vertices_names == NULL || new_vertices_links == NULL)
    {
        free(new_vertices_names);
        free(new_vertices_links);
        printf("\n[addNewVertex] Error allocating memory.\n");
        return 0;
    }

    for (int i = 0; i < new_size; i++)
    {
        new_vertices_links[i] = (int *)malloc(new_size * sizeof(int));
        if (new_vertices_links[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(new_vertices_links[j]);
            }
            free(new_vertices_links);
            free(new_vertices_names);
            printf("\n[addNewVertex] Error allocating memory.\n");
            return 0;
        }
    }

    for (int i = 0; i < old_size; i++)
    {
        new_vertices_names[i] = graph->vertices_names[i];
        for (int j = 0; j < old_size; j++)
        {
            new_vertices_links[i][j] = graph->vertices_links[i][j];
        }
        new_vertices_links[i][old_size] = 0;
    }

    new_vertices_names[old_size] = vertex_name;
    for (int j = 0; j < new_size; j++)
    {
        new_vertices_links[old_size][j] = 0;
    }

    for (int i = 0; i < old_size; i++)
    {
        free(graph->vertices_links[i]);
    }
    free(graph->vertices_links);
    free(graph->vertices_names);

    graph->vertices_names = new_vertices_names;
    graph->vertices_links = new_vertices_links;
    graph->vertices_count = new_size;
    return 1;
}

int addEdge(char start_char, char end_char, struct Graph *graph)
{
    int start_index, end_index;

    if (!get_index(graph, start_char, &start_index))
    {
        printf("\n[addEdge] Error getting the index of start character '%c'.\n", start_char);
        return 0;
    }
    if (!get_index(graph, end_char, &end_index))
    {
        printf("\n[addEdge] Error getting the index of end character '%c'.\n", end_char);
        return 0;
    }

    graph->vertices_links[start_index][end_index] = 1;
    graph->vertices_links[end_index][start_index] = 1;
    return 1;
}

void depthFirstTraverse(struct Graph *graph, char start)
{
    int start_index;
    int *vertices_visited = (int *)malloc(graph->vertices_count * sizeof(int));

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
        vertices_visited[i] = 0;
    }

    vertices_visited[start_index] = 1;
    push(start_index, MAIN_STACK);

    printf("Depth-first Traverse [start = '%c', index = %d]: ", start, start_index);

    while (!isStackEmpty(MAIN_STACK))
    {
        int traverse;
        pop(&traverse, MAIN_STACK);

        printf("%c ", graph->vertices_names[traverse]);

        for (int i = 0; i < graph->vertices_count; i++)
        {
            if (graph->vertices_links[traverse][i] == 1 && vertices_visited[i] == 0)
            {
                vertices_visited[i] = 1;
                push(i, MAIN_STACK);
            }
        }
    }
    printf("\n");
    free(vertices_visited); // free the temporary memory
}

void breadthFirstTraverse(struct Graph *graph, char start)
{
    int start_index;
    int *vertices_visited = (int *)malloc(graph->vertices_count * sizeof(int));

    // get the starting character's index from the vertices names array
    if (!get_index(graph, start, &start_index))
    {
        printf("\n[*] Error getting the index of start character '%c'.\n", start);
        return;
    }

    emptyQueue(MAIN_QUEUE);
    // reset vertices visited booleans for each vertex
    for (int i = 0; i < graph->vertices_count; i++)
    {
        vertices_visited[i] = 0;
    }

    vertices_visited[start_index] = 1;
    enqueue(start_index, MAIN_QUEUE);

    printf("Breadth-first Traverse [start = '%c', index = %d]: ", start, start_index);

    while (!isQueueEmpty(MAIN_QUEUE))
    {
        int traverse;
        dequeue(&traverse, MAIN_QUEUE);

        printf("%c ", graph->vertices_names[traverse]);

        for (int i = 0; i < graph->vertices_count; i++)
        {
            if (graph->vertices_links[traverse][i] == 1 && vertices_visited[i] == 0)
            {
                vertices_visited[i] = 1;
                enqueue(i, MAIN_QUEUE);
            }
        }
    }
    printf("\n");
    free(vertices_visited); // free the temporary memory
}

// === CRUD Methods ===

void printVertexNames(struct Graph *graph)
{

    for (int i = 0; i < graph->vertices_count; i++)
    {
        printf("   %c", graph->vertices_names[i]);
    }
    printf("\n");
}

void showConnectionsMatrix(struct Graph *graph)
{
    printf("\n[*] Connections of Graph [size = %d]:\n", graph->vertices_count);
    printVertexNames(graph);
    for (int i = 0; i < graph->vertices_count; i++)
    {
        printf("%c ", graph->vertices_names[i]);
        for (int j = 0; j < graph->vertices_count; j++)
        {
            printf("[%i] ", graph->vertices_links[i][j]);
        }
        printf("\n");
    }
}

void crud_addNewVertex(struct Graph *graph)
{
    char new_char;
    int temp_result;

    if (!get_char_input("Enter vertex character name: ", 3, &new_char))
    {
        return;
    };

    if (get_index(graph, new_char, &temp_result))
    {
        printf("\n[*] Vertex with that character already exists!\n");
        return;
    }

    if (!addNewVertex(new_char, graph))
    {
        printf("\n[*] Unable to add vertex '%c'.\n", new_char);
    }
    else
    {
        printf("\n[*] Added new vertex with name '%c'.\n", new_char);
    }
}

void crud_addEdge(struct Graph *graph)
{
    char start_char, end_char;

    if (!get_char_input("Enter starting vertex character name: ", 3, &start_char))
    {
        return;
    };

    if (!get_char_input("Enter ending vertex character name: ", 3, &end_char))
    {
        return;
    };

    if (addEdge(start_char, end_char, graph))
        printf("\n[*] Added new edge '%c' -> '%c'.\n", start_char, end_char);
}

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    char graph_vertices_names[] = {'A', 'B', 'C', 'D', 'E'};
    int graph_vertices_links[5][5] = {{0, 1, 1, 0, 1},
                                      {1, 0, 1, 0, 1},
                                      {1, 1, 0, 1, 0},
                                      {0, 0, 1, 0, 1},
                                      {1, 1, 0, 1, 0}};
    struct Graph *graph = createNewGraph(5, graph_vertices_names, graph_vertices_links);
    // depthFirstTraverse(graph, 'C');
    // breadthFirstTraverse(graph, 'C');

    int choice = 0;
    char start_char;
    do
    {
        printf("\n===== MENU [Graph using Array] =====\n");
        printf("1. Display Vertices Names\n");
        printf("2. Display Connection Matrix\n");
        printf("3. Add New Vertex\n");
        printf("4. Add Edge\n");
        printf("5. Print Graph [depth-first]\n");
        printf("6. Print Graph [breadth-first]\n");
        printf("7. Exit\n");

        if (get_int_input("Enter your choice: ", 3, &choice))
        {
            switch (choice)
            {
            case 1:
                printf("\n[*] Vertices of Graph: [size = %d]:\n", graph->vertices_count);
                printVertexNames(graph);
                break;
            case 2:
                showConnectionsMatrix(graph);
                break;
            case 3:
                crud_addNewVertex(graph);
                break;
            case 4:
                crud_addEdge(graph);
                break;
            case 5:
                if (get_char_input("Enter starting vertex character name: ", 3, &start_char))
                {
                    depthFirstTraverse(graph, start_char);
                }
                break;
            case 6:
                if (get_char_input("Enter starting vertex character name: ", 3, &start_char))
                {
                    breadthFirstTraverse(graph, start_char);
                }
                break;
            case 7:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
            }
        }
    } while (choice != 7);

    emptyQueue(MAIN_QUEUE);
    emptyStack(MAIN_STACK);

    return 0;
}
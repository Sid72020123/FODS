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
        if (fgets(buffer, sizeof(buffer), stdin) != NULL &&
            sscanf(buffer, "%d %c", &input, &extra) == 1)
        {
            *result = input;
            return 1;
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0;
}

int get_char_input(const char *prompt, int max_tries, char *result)
{
    char input;
    char extra;
    char buffer[100];
    int tries = 0;

    while (tries < max_tries)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL &&
            sscanf(buffer, " %c %c", &input, &extra) == 1)
        {
            *result = input;
            return 1;
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0;
}

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
    struct Node **new_vertices_links = (struct Node **)malloc(new_size * sizeof(struct Node *));

    if (new_vertices_names == NULL || new_vertices_links == NULL)
    {
        free(new_vertices_names);
        free(new_vertices_links);
        printf("\n[addNewVertex] Error allocating memory.\n");
        return 0;
    }

    for (int i = 0; i < old_size; i++)
    {
        new_vertices_names[i] = graph->vertices_names[i];
        new_vertices_links[i] = graph->vertices_links[i];
    }
    new_vertices_names[old_size] = vertex_name;
    new_vertices_links[old_size] = NULL;

    free(graph->vertices_names);
    free(graph->vertices_links);
    graph->vertices_names = new_vertices_names;
    graph->vertices_links = new_vertices_links;
    graph->vertices_count = new_size;
    return 1;
}

void _addItemToLinkedList(struct Node *newItem, struct Node **linkedList)
{
    if (*linkedList == NULL)
    {
        *linkedList = newItem;
    }
    else
    {
        struct Node *traverse = *linkedList;

        // find the empty / last Node
        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newItem;
    }
}

void addLink(struct Graph *graph, char source, char destination)
{
    if (source == destination)
    {
        printf("\n[addLink] A vertex cannot be linked to itself.\n");
        return;
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

    // two pointers needed for two-way links
    struct Node *newSourceNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *newDestinationNode = (struct Node *)malloc(sizeof(struct Node));

    newSourceNode->data = destination_index;
    newSourceNode->next = NULL;

    newDestinationNode->data = source_index;
    newDestinationNode->next = NULL;

    _addItemToLinkedList(newSourceNode, &graph->vertices_links[source_index]);
    _addItemToLinkedList(newDestinationNode, &graph->vertices_links[destination_index]);
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

        struct Node *traverseVertex = graph->vertices_links[traverse];
        while (traverseVertex != NULL)
        {
            if (vertices_visited[traverseVertex->data] == 0)
            {
                vertices_visited[traverseVertex->data] = 1;
                push(traverseVertex->data, MAIN_STACK);
            }
            traverseVertex = traverseVertex->next;
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

        struct Node *traverseVertex = graph->vertices_links[traverse];
        while (traverseVertex != NULL)
        {
            if (vertices_visited[traverseVertex->data] == 0)
            {
                vertices_visited[traverseVertex->data] = 1;
                enqueue(traverseVertex->data, MAIN_QUEUE);
            }
            traverseVertex = traverseVertex->next;
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

void showConnectionsList(struct Graph *graph)
{
    printf("\n[*] Connections of Graph [size = %d]:\n", graph->vertices_count);
    for (int i = 0; i < graph->vertices_count; i++)
    {
        printf("%c -> ", graph->vertices_names[i]);
        struct Node *traverse = graph->vertices_links[i];
        while (traverse != NULL)
        {
            printf("%c", graph->vertices_names[traverse->data]);
            if (traverse->next != NULL)
            {
                printf(" -> ");
            }
            traverse = traverse->next;
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
    }

    if (get_index(graph, new_char, &temp_result))
    {
        printf("\n[*] Vertex with that character already exists!\n");
        return;
    }

    if (addNewVertex(new_char, graph))
    {
        printf("\n[*] Added new vertex with name '%c'.\n", new_char);
    }
    else
    {
        printf("\n[*] Unable to add vertex '%c'.\n", new_char);
    }
}

void crud_addEdge(struct Graph *graph)
{
    char start_char, end_char;

    if (!get_char_input("Enter starting vertex character name: ", 3, &start_char) ||
        !get_char_input("Enter ending vertex character name: ", 3, &end_char))
    {
        return;
    }

    addLink(graph, start_char, end_char);
}

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    char graph_vertices_names[] = {'A', 'B', 'C', 'D', 'E'};
    struct Graph *graph = createNewGraph(5, graph_vertices_names);
    addLink(graph, 'A', 'B');
    addLink(graph, 'A', 'C');
    addLink(graph, 'A', 'E');
    addLink(graph, 'B', 'C');
    addLink(graph, 'B', 'E');
    addLink(graph, 'C', 'D');
    addLink(graph, 'D', 'E');

    int choice = 0;
    char start_char;
    do
    {
        printf("\n===== MENU [Graph using Linked List] =====\n");
        printf("1. Display Vertices Names\n");
        printf("2. Display Connections List\n");
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
                showConnectionsList(graph);
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
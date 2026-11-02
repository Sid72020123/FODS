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

int removeEdge(char start_char, char end_char, struct Graph *graph)
{
    int start_index, end_index;

    if (!get_index(graph, start_char, &start_index))
    {
        printf("\n[removeEdge] Error getting the index of start character '%c'.\n", start_char);
        return 0;
    }

    if (!get_index(graph, end_char, &end_index))
    {
        printf("\n[removeEdge] Error getting the index of end character '%c'.\n", end_char);
        return 0;
    }

    if (start_char == end_char)
    {
        printf("\n[removeEdge]: Cannot unlink the same vertices.\n");
        return 0;
    }

    struct Node **link = &graph->vertices_links[start_index];
    while (*link != NULL)
    {
        if ((*link)->data == end_index)
        {
            struct Node *removed_link = *link;
            *link = removed_link->next;
            free(removed_link);
        }
        else
        {
            link = &(*link)->next;
        }
    }

    link = &graph->vertices_links[end_index];
    while (*link != NULL)
    {
        if ((*link)->data == start_index)
        {
            struct Node *removed_link = *link;
            *link = removed_link->next;
            free(removed_link);
        }
        else
        {
            link = &(*link)->next;
        }
    }

    return 1;
}

void freeLinkedList(struct Node *head)
{
    while (head != NULL)
    {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

int removeVertex(char vertex_name, struct Graph *graph)
{
    int vertex_index;
    if (graph == NULL || !get_index(graph, vertex_name, &vertex_index))
    {
        printf("\n[removeVertex] Error getting the index of character '%c'.\n", vertex_name);
        return 0;
    }

    int old_size = graph->vertices_count;
    int new_size = old_size - 1;
    char *new_vertices_names = NULL;
    struct Node **new_vertices_links = NULL;

    if (new_size > 0)
    {
        new_vertices_names = (char *)malloc(new_size * sizeof(char));
        new_vertices_links = (struct Node **)malloc(new_size * sizeof(struct Node *));

        if (new_vertices_names == NULL || new_vertices_links == NULL)
        {
            free(new_vertices_names);
            free(new_vertices_links);
            printf("\n[removeVertex] Error allocating memory.\n");
            return 0;
        }
    }

    int new_index = 0;
    for (int old_index = 0; old_index < old_size; old_index++)
    {
        if (old_index == vertex_index)
        {
            freeLinkedList(graph->vertices_links[old_index]);
            continue;
        }

        struct Node **link = &graph->vertices_links[old_index];
        while (*link != NULL)
        {
            if ((*link)->data == vertex_index)
            {
                struct Node *removed_link = *link;
                *link = removed_link->next;
                free(removed_link);
            }
            else
            {
                if ((*link)->data > vertex_index)
                {
                    (*link)->data--;
                }
                link = &(*link)->next;
            }
        }

        if (new_size > 0)
        {
            new_vertices_names[new_index] = graph->vertices_names[old_index];
            new_vertices_links[new_index] = graph->vertices_links[old_index];
            new_index++;
        }
    }

    free(graph->vertices_names);
    free(graph->vertices_links);
    graph->vertices_names = new_vertices_names;
    graph->vertices_links = new_vertices_links;
    graph->vertices_count = new_size;
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

void crud_removeEdge(struct Graph *graph)
{
    char start_char, end_char;

    if (!get_char_input("Enter starting vertex character: ", 3, &start_char) ||
        !get_char_input("Enter ending vertex character: ", 3, &end_char))
    {
        return;
    }

    if (removeEdge(start_char, end_char, graph))
    {
        printf("\n[*] Removed edge '%c' --X-> '%c'.\n", start_char, end_char);
    }
}

void crud_removeVertex(struct Graph *graph)
{
    char vertex_name;

    if (!get_char_input("Enter vertex character name to remove: ", 3, &vertex_name))
    {
        return;
    }

    if (removeVertex(vertex_name, graph))
    {
        printf("\n[*] Removed vertex with name '%c'.\n", vertex_name);
    }
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
        printf("5. Remove Vertex\n");
        printf("6. Remove Edge\n");
        printf("7. Print Graph [depth-first]\n");
        printf("8. Print Graph [breadth-first]\n");
        printf("9. Exit\n");

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
                crud_removeVertex(graph);
                break;
            case 6:
                crud_removeEdge(graph);
                break;
            case 7:
                if (get_char_input("Enter starting vertex character name: ", 3, &start_char))
                {
                    depthFirstTraverse(graph, start_char);
                }
                break;
            case 8:
                if (get_char_input("Enter starting vertex character name: ", 3, &start_char))
                {
                    breadthFirstTraverse(graph, start_char);
                }
                break;
            case 9:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
            }
        }
    } while (choice != 9);

    emptyQueue(MAIN_QUEUE);
    emptyStack(MAIN_STACK);
    return 0;
}
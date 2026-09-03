#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// === Global Variables / Structures ===
struct QueueNode
{
    struct Node *location;
    struct QueueNode *next;
};

struct QueueNode *front = NULL, *rear = NULL;

// === Queue Methods ===

int isQueueEmpty()
{
    return front == NULL;
}

int getSize()
{
    if (isQueueEmpty())
        return 0;
    else
    {
        int size = 0;
        struct QueueNode *traverse = front;

        while (traverse != NULL)
        {
            size++;
            traverse = traverse->next;
        }
        return size;
    }
}

void enqueue(struct Node *location)
{
    struct QueueNode *newNode = (struct QueueNode *)(malloc(sizeof(struct QueueNode)));
    newNode->location = location;
    newNode->next = NULL;

    if (front == NULL)
        front = newNode, rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue(struct Node **location)
{
    if (front == NULL)
        return 0;

    *location = front->location;

    if (front == rear)
    {
        free(front);
        front = rear = NULL;
    }
    else
    {
        struct QueueNode *deleteNode = front;
        front = front->next;
        free(deleteNode);
    }
    return 1;
}

int peek(struct Node **location)
{
    if (isQueueEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return 0;
    }
    *location = front->location;
    return 1;
}

void emptyQueue()
{
    if (isQueueEmpty())
        return;

    struct Node *temp;
    while (front != NULL)
    {
        dequeue(&temp);
    }
}

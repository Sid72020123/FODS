#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// === Global Variables / Structures ===
struct QueueNode
{
    int value;
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

void enqueue(int value)
{
    struct QueueNode *newNode = (struct QueueNode *)(malloc(sizeof(struct QueueNode)));
    newNode->value = value;
    newNode->next = NULL;

    if (front == NULL)
        front = newNode, rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue(int *value)
{
    if (front == NULL)
        return 0;

    *value = front->value;

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

int peek(int *value)
{
    if (isQueueEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return 0;
    }
    *value = front->value;
    return 1;
}

void emptyQueue()
{
    if (isQueueEmpty())
        return;

    int temp;
    while (front != NULL)
    {
        dequeue(&temp);
    }
}

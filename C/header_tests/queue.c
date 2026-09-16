#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// === Global Variables / Structures ===
struct QueueNode
{
    struct Node *location;
    struct QueueNode *next;
};

struct Queue
{
    struct QueueNode *front;
    struct QueueNode *rear;
};

// struct QueueNode *front = NULL, *rear = NULL;

// === Queue Methods ===

int isQueueEmpty(struct Queue *location)
{
    return location->front == NULL;
}

int getSizeQueue(struct Queue *location)
{
    if (isQueueEmpty(location))
        return 0;
    else
    {
        int size = 0;
        struct QueueNode *traverse = location->front;

        while (traverse != NULL)
        {
            size++;
            traverse = traverse->next;
        }
        return size;
    }
}

void enqueue(struct Node *location, struct Queue *queueLocation)
{
    struct QueueNode *newNode = (struct QueueNode *)(malloc(sizeof(struct QueueNode)));
    newNode->location = location;
    newNode->next = NULL;

    if (queueLocation->front == NULL)
        queueLocation->front = newNode, queueLocation->rear = newNode;
    else
    {
        queueLocation->rear->next = newNode;
        queueLocation->rear = newNode;
    }
}

int dequeue(struct Node **location, struct Queue *queueLocation)
{
    if (queueLocation->front == NULL)
        return 0;

    *location = queueLocation->front->location;

    if (queueLocation->front == queueLocation->rear)
    {
        free(queueLocation->front);
        queueLocation->front = queueLocation->rear = NULL;
    }
    else
    {
        struct QueueNode *deleteNode = queueLocation->front;
        queueLocation->front = queueLocation->front->next;
        free(deleteNode);
    }
    return 1;
}

int peekQueue(struct Node **location, struct Queue *queueLocation)
{
    if (isQueueEmpty(queueLocation))
    {
        return 0;
    }
    *location = queueLocation->front->location;
    return 1;
}

void emptyQueue(struct Queue *queueLocation)
{
    if (isQueueEmpty(queueLocation))
        return;

    struct Node *temp;
    while (queueLocation->front != NULL)
    {
        dequeue(&temp, queueLocation);
    }
}

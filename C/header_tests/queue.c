// === Includes ===

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

// === Private Structures ===
struct QueueNode
{
    struct Node *location;
    struct QueueNode *next;
};

struct Queue
{
    char queueName[15];
    struct QueueNode *front;
    struct QueueNode *rear;
};

// === Queue Methods ===

struct Queue *createNewQueue(char *name)
{
    struct Queue *newQueue = (struct Queue *)malloc(sizeof(struct Queue));

    if (newQueue == NULL)
    {
        return NULL;
    }

    newQueue->front = NULL;
    newQueue->rear = NULL;
    snprintf(newQueue->queueName, sizeof newQueue->queueName, "%s", name);

    return newQueue;
}

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

int enqueue(struct Node *location, struct Queue *queueLocation)
{
    struct QueueNode *newNode = (struct QueueNode *)(malloc(sizeof(struct QueueNode)));

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->location = location;
    newNode->next = NULL;

    if (queueLocation->front == NULL)
        queueLocation->front = newNode, queueLocation->rear = newNode;
    else
    {
        queueLocation->rear->next = newNode;
        queueLocation->rear = newNode;
    }

    return 1;
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

void destroyQueue(struct Queue *queueLocation)
{
    if (queueLocation == NULL)
        return;

    emptyQueue(queueLocation);
    free(queueLocation);
}

void _debugPrintQueueContents(struct Queue *queueLocation)
{
    int isEmpty = isQueueEmpty(queueLocation);

    printf("===== Queue Details [%p] =====\n", queueLocation);

    printf("Name: %s\n", queueLocation->queueName);
    printf("Size: %d\n", getSizeQueue(queueLocation));
    printf("Is Empty? %s\n", (isEmpty ? "YES" : "NO"));

    printf("Contents: ");

    if (isEmpty)
    {
        printf("[EMPTY]");
    }
    else
    {
        struct QueueNode *traverse = queueLocation->front;

        while (traverse != NULL)
        {
            printf("[%p] ", traverse->location);
            traverse = traverse->next;
        }
    }
    printf("\n\n");
}

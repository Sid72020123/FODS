// === Includes ===

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// === Private Structures ===
struct QueueNode
{
    void *data;
    struct QueueNode *next;
};

struct Queue
{
    char queueName[15];
    struct QueueNode *front;
    struct QueueNode *rear;
    size_t size;
};

// === Queue Methods ===

struct Queue *createNewQueue(const char *name)
{
    struct Queue *newQueue = malloc(sizeof *newQueue);

    if (newQueue == NULL)
    {
        return NULL;
    }

    if (name == NULL)
    {
        name = "";
    }

    newQueue->front = NULL;
    newQueue->rear = NULL;
    newQueue->size = 0;
    snprintf(newQueue->queueName, sizeof newQueue->queueName, "%s", name);

    return newQueue;
}

int isQueueEmpty(struct Queue *queue)
{
    return queue == NULL || queue->front == NULL;
}

size_t getSizeQueue(struct Queue *queue)
{
    return queue == NULL ? 0 : queue->size;
}

int enqueue(void *data, struct Queue *queue)
{
    if (queue == NULL)
    {
        return 0;
    }

    struct QueueNode *newNode = malloc(sizeof *newNode);

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (queue->front == NULL)
        queue->front = newNode, queue->rear = newNode;
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;

    return 1;
}

int dequeue(void **data, struct Queue *queue)
{
    if (queue == NULL || data == NULL || queue->front == NULL)
        return 0;

    *data = queue->front->data;

    if (queue->front == queue->rear)
    {
        free(queue->front);
        queue->front = queue->rear = NULL;
    }
    else
    {
        struct QueueNode *deleteNode = queue->front;
        queue->front = queue->front->next;
        free(deleteNode);
    }

    queue->size--;

    return 1;
}

int peekQueue(void **data, struct Queue *queue)
{
    if (data == NULL || isQueueEmpty(queue))
    {
        return 0;
    }
    *data = queue->front->data;
    return 1;
}

void emptyQueue(struct Queue *queue)
{
    if (queue == NULL)
        return;

    void *temp;
    while (queue->front != NULL)
    {
        dequeue(&temp, queue);
    }
}

void destroyQueue(struct Queue *queue)
{
    if (queue == NULL)
        return;

    emptyQueue(queue);
    free(queue);
}

void _debugPrintQueueContents(struct Queue *queue)
{
    if (queue == NULL)
    {
        printf("===== Queue Details [NULL] =====\n");
        printf("Queue is NULL\n\n");
        return;
    }

    int isEmpty = isQueueEmpty(queue);

    printf("===== Queue Details [%p] =====\n", (void *)queue);

    printf("Name: %s\n", queue->queueName);
    printf("Size: %zu\n", getSizeQueue(queue));
    printf("Is Empty? %s\n", (isEmpty ? "YES" : "NO"));

    printf("Contents: ");

    if (isEmpty)
    {
        printf("[EMPTY]");
    }
    else
    {
        struct QueueNode *traverse = queue->front;

        while (traverse != NULL)
        {
            printf("[%p] ", traverse->data);
            traverse = traverse->next;
        }
    }
    printf("\n\n");
}

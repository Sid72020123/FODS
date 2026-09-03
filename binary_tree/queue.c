#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// === Global Variables / Structures ===

struct Node
{
    int value;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

// === Queue Methods ===

int isEmpty()
{
    return front == NULL;
}

int getSize()
{
    if (isEmpty())
        return 0;
    else
    {
        int size = 0;
        struct Node *traverse = front;

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
    struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
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
        struct Node *deleteNode = front;
        front = front->next;
        free(deleteNode);
    }
    return 1;
}

int peek(int *value)
{
    if (isEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return 0;
    }
    *value = front->value;
    return 1;
}
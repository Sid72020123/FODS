#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// === Global Variables / Structures ===

struct StackNode
{
    struct Node *location;
    struct StackNode *next;
};

struct StackNode *top = NULL;

// === Stack Methods ===

int isStackEmpty()
{
    return top == NULL;
}

int getSizeStack()
{
    if (isStackEmpty())
        return 0;
    else
    {
        int size = 0;
        struct StackNode *traverse = top;

        while (traverse != NULL)
        {
            size++;
            traverse = traverse->next;
        }
        return size;
    }
}

void push(struct Node *location)
{
    struct StackNode *newNode = (struct StackNode *)(malloc(sizeof(struct StackNode)));
    newNode->location = location;
    newNode->next = NULL;

    if (top == NULL)
        top = newNode;
    else
    {
        newNode->next = top;
        top = newNode;
    }
}

int pop(struct Node **location)
{
    if (top == NULL)
    {
        return 0;
    }

    *location = top->location;

    struct StackNode *deleteNode = top;

    top = top->next;

    free(deleteNode);

    return 1;
}

int peekStack(struct Node **location)
{
    if (isStackEmpty())
    {
        return 0;
    }

    *location = top->location;
    return 1;
}

void emptyStack()
{
    if (isStackEmpty())
        return;

    struct Node *temp;
    while (top != NULL)
    {
        pop(&temp);
    }
}

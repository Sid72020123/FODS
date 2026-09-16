// === Includes ===

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// === Private Structures ===
struct StackNode
{
    struct Node *location;
    struct StackNode *next;
};

struct Stack
{
    char stackName[15];
    struct StackNode *top;
};

// === Stack Methods ===

struct Stack *createNewStack(char *name)
{
    struct Stack *newStack = (struct Stack *)malloc(sizeof(struct Stack));

    if (newStack == NULL)
    {
        return NULL;
    }

    newStack->top = NULL;
    snprintf(newStack->stackName, sizeof newStack->stackName, "%s", name);

    return newStack;
}

int isStackEmpty(struct Stack *location)
{
    return location->top == NULL;
}

int getSizeStack(struct Stack *location)
{
    if (isStackEmpty(location))
        return 0;
    else
    {
        int size = 0;
        struct StackNode *traverse = location->top;

        while (traverse != NULL)
        {
            size++;
            traverse = traverse->next;
        }
        return size;
    }
}

int push(struct Node *location, struct Stack *stackLocation)
{
    struct StackNode *newNode = (struct StackNode *)(malloc(sizeof(struct StackNode)));

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->location = location;
    newNode->next = NULL;

    if (stackLocation->top == NULL)
        stackLocation->top = newNode;
    else
    {
        newNode->next = stackLocation->top;
        stackLocation->top = newNode;
    }

    return 1;
}

int pop(struct Node **location, struct Stack *stackLocation)
{
    if (stackLocation->top == NULL)
    {
        return 0;
    }

    *location = stackLocation->top->location;

    struct StackNode *deleteNode = stackLocation->top;

    stackLocation->top = stackLocation->top->next;
    free(deleteNode);

    return 1;
}

int peekStack(struct Node **location, struct Stack *stackLocation)
{
    if (isStackEmpty(stackLocation))
    {
        return 0;
    }

    *location = stackLocation->top->location;
    return 1;
}

void emptyStack(struct Stack *stackLocation)
{
    if (isStackEmpty(stackLocation))
        return;

    struct Node *temp;
    while (stackLocation->top != NULL)
    {
        pop(&temp, stackLocation);
    }
}

void destroyStack(struct Stack *stackLocation)
{
    if (stackLocation == NULL)
        return;

    emptyStack(stackLocation);
    free(stackLocation);
}

void _debugPrintStackContents(struct Stack *stackLocation)
{
    int isEmpty = isStackEmpty(stackLocation);

    printf("===== Stack Details [%p] =====\n", stackLocation);

    printf("Name: %s\n", stackLocation->stackName);
    printf("Size: %d\n", getSizeQueue(stackLocation));
    printf("Is Empty? %s\n", (isEmpty ? "YES" : "NO"));

    printf("Contents:");

    if (isEmpty)
    {
        printf("\n\t[EMPTY]");
    }
    else
    {
        struct StackNode *traverse = stackLocation->top;

        while (traverse != NULL)
        {
            printf("\n\t[%p]", traverse->location);
            traverse = traverse->next;
        }
    }
    printf("\n\n");
}

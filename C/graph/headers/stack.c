// NOTE: This file is modified to make it easier to work with normal integers.
// === Includes ===

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// === Private Structures ===
struct StackNode
{
    int data;
    struct StackNode *next;
};

struct Stack
{
    char stackName[15];
    struct StackNode *top;
    size_t size;
};

// === Stack Methods ===

struct Stack *createNewStack(const char *name)
{
    struct Stack *newStack = malloc(sizeof *newStack);

    if (newStack == NULL)
    {
        return NULL;
    }

    if (name == NULL)
    {
        name = "";
    }

    newStack->top = NULL;
    newStack->size = 0;
    snprintf(newStack->stackName, sizeof newStack->stackName, "%s", name);

    return newStack;
}

int isStackEmpty(struct Stack *stack)
{
    return stack == NULL || stack->top == NULL;
}

size_t getSizeStack(struct Stack *stack)
{
    return stack == NULL ? 0 : stack->size;
}

int push(int data, struct Stack *stack)
{
    if (stack == NULL)
    {
        return 0;
    }

    struct StackNode *newNode = malloc(sizeof *newNode);

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (stack->top == NULL)
        stack->top = newNode;
    else
    {
        newNode->next = stack->top;
        stack->top = newNode;
    }

    stack->size++;

    return 1;
}

int pop(int *data, struct Stack *stack)
{
    if (stack == NULL || data == NULL || stack->top == NULL)
    {
        return 0;
    }

    *data = stack->top->data;

    struct StackNode *deleteNode = stack->top;

    stack->top = stack->top->next;
    free(deleteNode);

    stack->size--;

    return 1;
}

int peekStack(int *data, struct Stack *stack)
{
    if (data == NULL || isStackEmpty(stack))
    {
        return 0;
    }

    *data = stack->top->data;
    return 1;
}

void emptyStack(struct Stack *stack)
{
    if (stack == NULL)
        return;

    int temp;
    while (stack->top != NULL)
    {
        pop(&temp, stack);
    }
}

void destroyStack(struct Stack *stack)
{
    if (stack == NULL)
        return;

    emptyStack(stack);
    free(stack);
}

void _debugPrintStackContents(struct Stack *stack)
{
    if (stack == NULL)
    {
        printf("===== Stack Details [NULL] =====\n");
        printf("Stack is NULL\n\n");
        return;
    }

    int isEmpty = isStackEmpty(stack);

    printf("===== Stack Details [%p] =====\n", (void *)stack);

    printf("Name: %s\n", stack->stackName);
    printf("Size: %zu\n", getSizeStack(stack));
    printf("Is Empty? %s\n", (isEmpty ? "YES" : "NO"));

    printf("Contents:");

    if (isEmpty)
    {
        printf("\n\t[EMPTY]");
    }
    else
    {
        struct StackNode *traverse = stack->top;

        while (traverse != NULL)
        {
            printf("\n\t[%d]", traverse->data);
            traverse = traverse->next;
        }
    }
    printf("\n\n");
}

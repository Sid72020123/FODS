#ifndef STACK_H
#define STACK_H

struct Node;
struct Stack;

struct Stack *createNewStack(const char *name);
int isStackEmpty(struct Stack *stack);
int getSizeStack(struct Stack *stack);
int push(struct Node *node, struct Stack *stack);
int pop(struct Node **node, struct Stack *stack);
int peekStack(struct Node **node, struct Stack *stack);
void emptyStack(struct Stack *stack);
void destroyStack(struct Stack *stack);
void _debugPrintStackContents(struct Stack *stack);

#endif
#ifndef STACK_H
#define STACK_H

struct Node;

int isStackEmpty(void);
int getSizeStack(void);
void push(struct Node *);
int pop(struct Node **);
int peekStack(struct Node **);
void emptyQueue(void);

#endif
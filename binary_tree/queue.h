#ifndef QUEUE_H
#define QUEUE_H

struct Node;

int isQueueEmpty(void);
void enqueue(struct Node *);
int dequeue(struct Node **);
int peek(struct Node **);
void emptyQueue(void);

#endif
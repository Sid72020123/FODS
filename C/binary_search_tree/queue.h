#ifndef QUEUE_H
#define QUEUE_H

struct Node;

int isQueueEmpty(void);
int getSizeQueue(void);
void enqueue(struct Node *);
int dequeue(struct Node **);
int peekQueue(struct Node **);
void emptyQueue(void);

#endif
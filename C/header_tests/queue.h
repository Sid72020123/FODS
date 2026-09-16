#ifndef QUEUE_H
#define QUEUE_H

struct Node;
struct Queue;

struct Queue *createNewQueue(void);
int isQueueEmpty(struct Queue *);
int getSizeQueue(struct Queue *);
void enqueue(struct Node *, struct Queue *);
int dequeue(struct Node **, struct Queue *);
int peekQueue(struct Node **, struct Queue *);
void emptyQueue(struct Queue *);

#endif
#ifndef QUEUE_H
#define QUEUE_H

int isQueueEmpty(void);
int getSize(void);
void enqueue(int);
int dequeue(int *);
int peek(int *);
void emptyQueue(void);

#endif
/*
 * queue.h
 *
 * Linked-list implementation of FIFO queue.
 *
 * Version: 0.1
 * Last Modified: 16/09/2026
 *
 * Copyright (c) 2026 Siddhesh Chavan (@Sid72020123 on Github)
 *
 * This code is licensed under the MIT License.
 * See LICENSE for details.
 *
 * Version History:
 *      16/09/2026: first release
 */

#ifndef QUEUE_H
#define QUEUE_H

struct Node;
struct Queue;

/**
 * @brief Creates an empty queue.
 *
 * @param name Name assigned to the queue.
 * @return Pointer to the new queue, or NULL if allocation fails.
 */
struct Queue *createNewQueue(char *name);

/**
 * @brief Checks whether a queue is empty.
 *
 * @param queue Queue to check.
 * @return Non-zero if empty, otherwise 0.
 */
int isQueueEmpty(struct Queue *queue);

/**
 * @brief Returns the number of elements in a queue.
 *
 * @param queue Queue to inspect.
 * @return Number of elements currently in the queue.
 */
int getSizeQueue(struct Queue *queue);

/**
 * @brief Adds a node to the rear of the queue.
 *
 * @param node Node to add.
 * @param queue Queue to modify.
 * @return 1 on success, 0 if memory allocation fails.
 */
int enqueue(struct Node *node, struct Queue *queue);

/**
 * @brief Removes the front node from the queue.
 *
 * The QueueNode is freed, but the Node object itself is not freed.
 * Ownership of the Node remains with the caller.
 *
 * @param[out] node Receives the removed node.
 * @param queue Queue to modify.
 * @return 1 if a node was removed, 0 if the queue is empty.
 */
int dequeue(struct Node **node, struct Queue *queue);

/**
 * @brief Retrieves the front node without removing it.
 *
 * @param[out] node Receives the front node.
 * @param queue Queue to inspect.
 * @return 1 if a node was retrieved, 0 if the queue is empty.
 */
int peekQueue(struct Node **node, struct Queue *queue);

/**
 * @brief Removes all elements from the queue.
 *
 * QueueNode objects are freed. Node objects stored in the queue
 * are not freed.
 *
 * @param queue Queue to empty.
 */
void emptyQueue(struct Queue *queue);

/**
 * @brief Destroys a queue.
 *
 * The queue is emptied and its memory is released.
 *
 * @param queue Queue to destroy.
 */
void destroyQueue(struct Queue *queue);

/**
 * @brief Prints the current contents of a queue for debugging.
 *
 * @param queue Queue to print.
 */
void _debugPrintQueueContents(struct Queue *queue);

#endif /* QUEUE_H */
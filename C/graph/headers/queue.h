/*
 * queue.h
 *
 * Linked-list implementation of FIFO queue.
 *
 * Version: 0.1
 * Last Modified: 20/09/2026
 *
 * Copyright (c) 2026 Siddhesh Chavan (@Sid72020123 on Github)
 *
 * This code is licensed under the MIT License.
 * See LICENSE for details.
 *
 * Version History:
 *      16/09/2026: first release
 *      20/09/2026: replaced the Node data-type with void*
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

struct Queue;

/**
 * @brief Creates an empty queue.
 *
 * @param name Name assigned to the queue.
 * @return Pointer to the new queue, or NULL if allocation fails.
 */
struct Queue *createNewQueue(const char *name);

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
size_t getSizeQueue(struct Queue *queue);

/**
 * @brief Adds data to the rear of the queue.
 *
 * The queue stores the pointer only. It does not copy or free
 * the object pointed to by data.
 *
 * @param data Pointer to data to add.
 * @param queue Queue to modify.
 * @return 1 on success, 0 if the queue is NULL or memory allocation fails.
 */
int enqueue(void *data, struct Queue *queue);

/**
 * @brief Removes the front data from the queue.
 *
 * The QueueNode is freed, but the stored data is not freed.
 * Ownership of the data remains with the caller.
 *
 * @param[out] data Receives the removed data pointer.
 * @param queue Queue to modify.
 * @return 1 on success, 0 if queue, data, or the queue contents are invalid.
 */
int dequeue(void **data, struct Queue *queue);

/**
 * @brief Retrieves the front data without removing it.
 *
 * @param[out] data Receives the front data pointer.
 * @param queue Queue to inspect.
 * @return 1 on success, 0 if queue, data, or the queue contents are invalid.
 */
int peekQueue(void **data, struct Queue *queue);

/**
 * @brief Removes all elements from the queue.
 *
 * QueueNode objects are freed.
 * The data stored in the queue is not freed.
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
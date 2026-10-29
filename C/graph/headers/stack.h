/*
 * stack.h
 *
 * Linked-list implementation of LIFO stack.
 *
 * NOTE: This file is modified to make it easier to work with normal integers.
 *
 * Version: 0.1
 * Last Modified: 23/09/2026
 *
 * Copyright (c) 2026 Siddhesh Chavan (@Sid72020123 on Github)
 *
 * This code is licensed under the MIT License.
 * See LICENSE for details.
 *
 * Version History:
 *      16/09/2026: first release
 *      23/09/2026: replaced the Node data-type with void*
 */

#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct Stack;

/**
 * @brief Creates an empty stack.
 *
 * @param name Name assigned to the stack.
 * @return Pointer to the new stack, or NULL if allocation fails.
 */
struct Stack *createNewStack(const char *name);

/**
 * @brief Checks whether a stack is empty.
 *
 * @param stack Stack to check.
 * @return Non-zero if empty, otherwise 0.
 */
int isStackEmpty(struct Stack *stack);

/**
 * @brief Returns the number of elements in a stack.
 *
 * @param stack Stack to inspect.
 * @return Number of elements currently in the stack.
 */
size_t getSizeStack(struct Stack *stack);

/**
 * @brief Pushes the data onto the top of the stack.
 *
 * The stack stores the pointer only. It does not copy or free
 * the object pointed to by data.
 *
 * @param data Integer data to push.
 * @param stack Stack to modify.
 * @return 1 on success, 0 if stack is NULL or memory allocation fails.
 */
int push(int data, struct Stack *stack);

/**
 * @brief Removes the top data from the stack.
 *
 *
 * @param[out] data Receives the removed integer.
 * @param stack Stack to modify.
 * @return 1 on success, 0 if stack, data, or the stack contents are invalid.
 */
int pop(int *data, struct Stack *stack);

/**
 * @brief Retrieves the top data without removing it.
 *
 * @param[out] data Receives the top integer.
 * @param stack Stack to inspect.
 * @return 1 on success, 0 if stack is NULL, data is NULL, or the stack is empty.
 */
int peekStack(int *data, struct Stack *stack);

/**
 * @brief Removes all elements from the stack.
 *
 * StackNode objects are freed.
 * The data stored in the stack is not freed.
 *
 * @param stack Stack to empty.
 */
void emptyStack(struct Stack *stack);

/**
 * @brief Destroys a stack and releases its memory.
 *
 * The stack is emptied and its memory is released.
 *
 * @param stack Stack to destroy.
 */
void destroyStack(struct Stack *stack);

/**
 * @brief Prints the current contents of a stack for debugging.
 *
 * @param stack Stack to print.
 */
void _debugPrintStackContents(struct Stack *stack);

#endif /* STACK_H */
/*
 * stack.h
 *
 * Linked-list implementation of LIFO stack.
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

#ifndef STACK_H
#define STACK_H

struct Node;
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
int getSizeStack(struct Stack *stack);

/**
 * @brief Pushes a node onto the top of the stack.
 *
 * @param node Node to push.
 * @param stack Stack to modify.
 * @return 1 on success, 0 if memory allocation fails.
 */
int push(struct Node *node, struct Stack *stack);

/**
 * @brief Removes the top node from the stack.
 *
 * The StackNode is freed, but the Node itself is not freed.
 *
 * @param[out] node Receives the removed node.
 * @param stack Stack to modify.
 * @return 1 if a node was removed, 0 if the stack is empty.
 */
int pop(struct Node **node, struct Stack *stack);

/**
 * @brief Retrieves the top node without removing it.
 *
 * @param[out] node Receives the top node.
 * @param stack Stack to inspect.
 * @return 1 if a node was retrieved, 0 if the stack is empty.
 */
int peekStack(struct Node **node, struct Stack *stack);

/**
 * @brief Removes all elements from the stack.
 *
 * StackNode objects are freed. Node objects are not freed.
 *
 * @param stack Stack to empty.
 */
void emptyStack(struct Stack *stack);

/**
 * @brief Destroys a stack and releases its memory.
 *
 * @param stack Stack to destroy.
 */
void destroyStack(struct Stack *stack);

/**
 * @brief Prints stack information for debugging.
 *
 * @param stack Stack to print.
 */
void _debugPrintStackContents(struct Stack *stack);

#endif /* STACK_H */
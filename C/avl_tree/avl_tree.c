#include <stdio.h>
#include <stdlib.h>

#include "headers/queue.h"
#include "headers/stack.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct Node
{
    int value;

    int height;

    struct Node *left;
    struct Node *right;
};

struct Queue *MAIN_QUEUE;
struct Stack *MAIN_STACK;
struct Node *root = NULL;

int getNodeHeight(struct Node *n)
{
    if (n == NULL)
        return -1;
    else
    {
        if (n->height == -1)
            return 0;
        else
            return n->height;
    }
}

void rightRotateNode(struct Node *node)
{
    struct Node *child = node->left;

    // Perform rotation
    node->left = child->right;
    child->right = node;

    // Connect rotated subtree to parent
    struct Node *parent = NULL;
    if (!isStackEmpty(MAIN_STACK))
    {
        peekStack(&parent, MAIN_STACK);

        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
    {
        // node was the root
        root = child;
    }
    // peekStack(&parent, MAIN_STACK);

    // parent->left = child;
}

void leftRotateNode(struct Node *node)
{
    struct Node *child = node->right;

    // Perform rotation
    node->right = child->left;
    child->left = node;

    // Connect rotated subtree to parent
    struct Node *parent = NULL;

    if (!isStackEmpty(MAIN_STACK))
    {
        peekStack(&parent, MAIN_STACK);

        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
    {
        // node was the root
        root = child;
    }
    // struct Node *parent;
    // peekStack(&parent, MAIN_STACK);

    // parent->right = child;
}

int addNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = -1;

    emptyStack(MAIN_STACK);

    if (root == NULL)
    {
        root = newNode;
        // push(root, MAIN_STACK); // No need to balance if there is only one element in tree
    }
    else
    {
        struct Node *traverse = root;

        while (traverse != NULL)
        {
            push(traverse, MAIN_STACK);

            if (traverse->value > value)
            {
                // Left side
                if (traverse->left == NULL)
                {
                    traverse->left = newNode;
                    traverse = NULL;
                }
                else
                {
                    traverse = traverse->left;
                }
            }
            else
            {
                // Right side
                if (traverse->right == NULL)
                {
                    traverse->right = newNode;
                    traverse = NULL;
                }
                else
                {
                    traverse = traverse->right;
                }
            }
        }
    }

    printf("=============================================\n");
    struct Node *node = NULL;
    while (!isStackEmpty(MAIN_STACK))
    {

        // _debugPrintStackContents(MAIN_STACK);
        pop(&node, MAIN_STACK);

        int leftHeight = getNodeHeight(node->left);
        int rightHeight = getNodeHeight(node->right);

        node->height = 1 + MAX(leftHeight, rightHeight);
        printf("%i %i %i %i\n", node->value, node->height, leftHeight, rightHeight);
        int balanceFactor = leftHeight - rightHeight;

        if (balanceFactor > 1)
        {
            // Left
            if (value < node->left->value)
            {
                // Left-Left
                rightRotateNode(node);
            }
            else
            {
                // Left-Right
                leftRotateNode(node->left);
                rightRotateNode(node);
            }
        }
        else if (balanceFactor < -1)
        {
            // Right
            if (value > node->right->value)
            {
                // Right-Right
                leftRotateNode(node);
            }
            else
            {
                // Right-Left
                rightRotateNode(node->right);
                leftRotateNode(node);
            }
        }
    }

    return 1;
}

// Breadth-First traversal / Level-Order traversal
void printTreeBreadthFirst()
{
    if (root == NULL)
    {
        printf("[*] Tree is Empty!");
    }
    else
    {
        emptyQueue(MAIN_QUEUE);
        enqueue(root, MAIN_QUEUE);
        struct Node *traverse;

        printf("[*] TREE: ");

        while (!isQueueEmpty(MAIN_QUEUE))
        {
            dequeue(&traverse, MAIN_QUEUE);
            printf("[%3d] ", traverse->value);

            if (traverse->left != NULL)
                enqueue(traverse->left, MAIN_QUEUE);

            if (traverse->right != NULL)
                enqueue(traverse->right, MAIN_QUEUE);
        }

        printf("\n");
    }
}

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    addNode(10);
    printTreeBreadthFirst();
    addNode(20);
    printTreeBreadthFirst();
    addNode(30);
    printTreeBreadthFirst();

    return 0;
}
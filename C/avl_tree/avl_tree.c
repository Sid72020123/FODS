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
    node->left = child->right;
    child->right = node;

    struct Node *parent;
    peekStack(&parent, MAIN_STACK);

    parent->left = child;
}

void leftRotateNode(struct Node *node)
{
    struct Node *child = node->right;
    node->right = child->left;
    child->left = node;

    struct Node *parent;
    peekStack(&parent, MAIN_STACK);

    parent->right = child;
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

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        struct Node *traverse = root;

        while (traverse != NULL)
        {
            push(traverse, MAIN_STACK);

            if (traverse->value > value)
            {
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

        struct Node *node = NULL;
        while (!isStackEmpty(MAIN_STACK))
        {
            pop(&node, MAIN_STACK);

            int leftHeight = getNodeHeight(node->left);
            int rightHeight = getNodeHeight(node->right);

            node->height = 1 + MAX(leftHeight, rightHeight);

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
    }

    return 1;
}

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    addNode(10);
    addNode(20);
    addNode(30);

    return 0;
}
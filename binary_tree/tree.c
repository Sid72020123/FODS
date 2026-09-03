#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// === Global Variables / Structures ===
struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;

// === Binary Tree Methods ===

void addNode(int value)
{
    struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        emptyQueue();
        enqueue(root);

        struct Node *traverse;
        struct Node *parentNode = NULL;

        while (!isQueueEmpty())
        {
            dequeue(&traverse);
            printf("%d\n", traverse->value);
            parentNode = traverse;
            if (traverse->left == NULL || traverse->right == NULL)
            {
                emptyQueue();
                // break;
            }
            else
            {
                enqueue(traverse->left);
                enqueue(traverse->right);
            }
        }

        if (parentNode->left == NULL)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;
    }
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
        enqueue(root);
        struct Node *traverse;

        while (!isQueueEmpty())
        {
            dequeue(&traverse);
            printf("[%3d] ", traverse->value);

            if (traverse->left != NULL)
                enqueue(traverse->left);

            if (traverse->right != NULL)
                enqueue(traverse->right);
        }

        printf("\n");
    }
}

int main(void)
{
    printTree();
    addNode(10);
    addNode(20);
    addNode(30);
    addNode(40);
    addNode(50);
    printTree();
    return 0;
}
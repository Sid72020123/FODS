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
        emptyQueue();
        enqueue(root);
        struct Node *traverse;

        printf("[*] TREE: ");

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

void updateNode(int old_value, int new_value)
{
    if (root == NULL)
    {
        printf("[*] Tree is Empty!");
    }
    else
    {
        emptyQueue();
        enqueue(root);
        struct Node *traverse;
        int found = 0;

        while (!isQueueEmpty() && !found)
        {
            dequeue(&traverse);

            if (traverse->value == old_value)
            {
                traverse->value = new_value;
                emptyQueue();
                found = 1;
            }

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
    printTreeBreadthFirst();
    addNode(10);
    addNode(10);
    addNode(10);
    addNode(10);
    addNode(10);
    addNode(20);
    addNode(30);
    addNode(40);
    addNode(50);
    printTreeBreadthFirst();

    updateNode(30, 99);
    printTreeBreadthFirst();
    return 0;
}
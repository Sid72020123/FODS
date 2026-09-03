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
            dequeue(traverse);

            if (traverse->left == NULL || traverse->right == NULL)
            {
                emptyQueue();
            }
            else
            {
                parentNode = traverse;
                if (traverse->left != NULL)
                    enqueue(traverse->left);
                if (traverse->right != NULL)
                    enqueue(traverse->right);
            }
        }

        if (parentNode->left == NULL)
            parentNode->left = newNode;
        else if (parentNode->right == NULL)
            parentNode->right = newNode;
    }
}

int main(void)
{
    addNode(10);
    addNode(20);
    addNode(30);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

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
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        struct Node *traverse = root;

        while (traverse != NULL)
        {
            if (value < traverse->value)
            {
                if (traverse->left == NULL)
                    traverse->left = newNode;
                else
                    traverse = traverse->left;
            }

            if (value >= traverse->value)
            {
                if (traverse->right == NULL)
                    traverse->right = newNode;
                else
                    traverse = traverse->right;
            }
        }
    }
}

int main(void)
{

    return 0;
}
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
        // replace the NULL root node with the new node
        root = newNode;
    }
    else
    {
        // find the empty link / location according to BST rules
        // and link the new node accordingly

        struct Node *traverse = root;

        while (traverse != NULL)
        {
            if (value < traverse->value)
            {
                // try the left side
                if (traverse->left == NULL)
                    // link the new node
                    traverse->left = newNode;
                else
                    traverse = traverse->left;
            }

            if (value >= traverse->value)
            {
                // try the right side
                if (traverse->right == NULL)
                    // link the new node
                    traverse->right = newNode;
                else
                    traverse = traverse->right;
            }
        }
    }
}

int main(void)
{
    addNode(10);
    return 0;
}
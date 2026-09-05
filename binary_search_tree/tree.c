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

int main(void)
{
    addNode(10);
    addNode(10);
    // addNode(10);
    // printTreeBreadthFirst();
    return 0;
}
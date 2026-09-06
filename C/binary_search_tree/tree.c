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
                {
                    // link the new node
                    traverse->left = newNode;
                    traverse = NULL;
                }
                else
                    traverse = traverse->left;
            }
            else
            {
                if (value >= traverse->value)
                {
                    // try the right side
                    if (traverse->right == NULL)
                    {
                        // link the new node
                        traverse->right = newNode;
                        traverse = NULL;
                    }
                    else
                        traverse = traverse->right;
                }
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

// TODO: Fix the bugs...
int updateNode(int old_value, int new_value)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        // find / traverse the tree according to BST rules
        // and update the value of the node accordingly

        struct Node *traverse = root;

        while (traverse != NULL)
        {
            if (old_value < traverse->value)
            {
                // try the left side
                if (traverse->left->value == old_value)
                {
                    // replace the value
                    traverse->left->value = new_value;
                    traverse = NULL;
                }
                else
                    traverse = traverse->left;
            }
            else
            {
                if (old_value >= traverse->value)
                {
                    // try the right side
                    if (traverse->right->value == old_value)
                    {
                        // replace the value
                        traverse->right->value = new_value;
                        traverse = NULL;
                    }
                    else
                        traverse = traverse->right;
                }
            }
        }
    }
}

int main(void)
{
    addNode(10);
    addNode(70);
    addNode(5);
    addNode(15);
    addNode(10);
    printTreeBreadthFirst();
    updateNode(70, 88);
    printTreeBreadthFirst();
    return 0;
}
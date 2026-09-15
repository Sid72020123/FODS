/*
=== Threaded Binary Search Tree (TBST) ===

The code in this file implements right-threaded binary tree.
*/

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

    short int leftThread;
    short int rightThread;
};

struct Node *root = NULL;

// === Threaded Binary Search Tree Methods ===

// Breadth-First traversal / Level-Order traversal
void printTreeBreadthFirst()
{
    /* For Breath-First / Level-Order traversal,
    queue is required as "threads" are based on inorder
    relationships while breath first traversal
    requires level relationships */

    if (root == NULL)
    {
        printf("[*] Tree is Empty!\n");
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

            if (traverse->right != NULL && !traverse->rightThread)
                enqueue(traverse->right);
        }

        printf("\n");
    }
}

struct Node *leftMostNode(struct Node *parent)
{
    // this functions returns the leftmost node a particular node
    if (parent == NULL)
        return NULL;

    struct Node *leftMost = parent;

    while (leftMost->left != NULL)
    {
        leftMost = leftMost->left;
    }

    return leftMost;
}

// Function to get the rightmost node in tree
struct Node *getRightMostNode(struct Node *node, struct Node **replacementParent)
{
    if (node == NULL)
        return NULL;

    struct Node *searchNode = node;

    while (searchNode->right != NULL && !searchNode->rightThread)
    {
        *replacementParent = searchNode;
        searchNode = searchNode->right;
    }

    return searchNode;
}

// inorder traversal (left -> root -> right) [Depth-First traversal]
void printTreeInorder()
{
    /* This method of traversal uses the "threads" */
    if (root == NULL)
    {
        printf("[*] Tree is Empty!\n");
    }
    else
    {
        struct Node *traverse = leftMostNode(root);

        printf("[*] TREE (inorder): ");

        while (traverse != NULL)
        {
            printf("[%3d] ", traverse->value);

            if (traverse->rightThread)
            {
                traverse = traverse->right;
            }
            else
            {
                traverse = leftMostNode(traverse->right);
            }
        }
    }

    printf("\n");
}

int getSize()
{
    /* This method of traversal uses the "threads" */
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        struct Node *traverse = leftMostNode(root);

        int size = 0;
        while (traverse != NULL)
        {
            size++;
            if (traverse->rightThread)
                traverse = traverse->right;
            else
                traverse = leftMostNode(traverse->right);
        }

        return size;
    }
}

void addNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->leftThread = 0;
    newNode->rightThread = 0;

    if (root == NULL)
        root = newNode; // replace the NULL root node with the new node
    else
    {
        struct Node *traverse = root;
        short int node_inserted = 0;

        // Find / search the empty left or right links
        while (!node_inserted)
        {
            if (traverse->value > value)
            {
                if (traverse->left == NULL)
                {
                    traverse->left = newNode;
                    newNode->right = traverse;
                    newNode->rightThread = 1;

                    node_inserted = 1;
                }
                else
                {
                    traverse = traverse->left;
                }
            }
            else
            {
                if (traverse->right == NULL || traverse->rightThread == 1)
                {
                    newNode->right = traverse->right;
                    newNode->rightThread = traverse->rightThread;
                    traverse->right = newNode;

                    node_inserted = 1;
                }
                else
                {
                    traverse = traverse->right;
                }
            }
        }
    }
}

int main(void)
{
    printTreeBreadthFirst();
    printTreeInorder();
    addNode(100);
    printTreeInorder();
    return 0;
}
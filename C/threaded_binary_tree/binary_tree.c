/*
=== Threaded Binary Tree (TBT) ===

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

// === Threaded Binary Tree Methods ===

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
        emptyQueue();
        enqueue(root);

        struct Node *traverse;
        struct Node *parentNode = NULL;

        // Find / search the empty left or right links
        while (!isQueueEmpty())
        {
            dequeue(&traverse);
            parentNode = traverse;

            if (traverse->left == NULL || (traverse->right == NULL || traverse->rightThread))
            {
                // (the condition also checks if the right link is not null but is a thread)
                emptyQueue();
            }
            else
            {
                enqueue(traverse->left);
                enqueue(traverse->right);
            }
        }

        if (parentNode->left == NULL)
        {
            // change the left node
            parentNode->left = newNode;
            newNode->right = parentNode;
            newNode->rightThread = 1;
        }
        else if (parentNode->right != NULL && parentNode->rightThread)
        {
            // keep (store) the "thread" of the parent node and link it's right to the new node
            // then thread / link the right of the new node to the stored parent's thread node
            struct Node *threadParentNode = parentNode->right;
            parentNode->right = newNode;
            parentNode->rightThread = 0;

            newNode->right = threadParentNode;
            newNode->rightThread = 1;
        }
        else
        {
            // if the parent node has no right child, just link the new node to it
            parentNode->right = newNode;
        }
    }
}

int updateNode(int old_value, int new_value)
{
    /* This method does traversal using "threads" */
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        struct Node *traverse = leftMostNode(root);
        int found = 0;

        while (traverse != NULL && !found)
        {
            if (traverse->value == old_value)
            {
                traverse->value = new_value;
                found = 1;
            }

            if (traverse->rightThread)
            {
                traverse = traverse->right;
            }
            else
            {
                traverse = leftMostNode(traverse->right);
            }
        }

        return found;
    }
}

int main(void)
{
    // printTreeBreadthFirst();
    // printTreeInorder();

    addNode(10);
    addNode(20);
    addNode(30);
    addNode(40);
    addNode(50);
    addNode(60);
    addNode(70);

    printTreeInorder();
    // printTreeBreadthFirst();

    updateNode(30, 99);
    updateNode(99, 100);
    updateNode(50, 500);
    updateNode(70, 999);
    printTreeInorder();
    return 0;
}
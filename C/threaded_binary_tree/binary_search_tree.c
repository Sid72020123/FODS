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

int deleteNode(int value)
{
    if (root == NULL)
        return 0;

    int found = 0;
    struct Node *searchNode = root;
    struct Node *parent = NULL;

    while (searchNode != NULL && !found)
    {
        if (searchNode->value == value)
        {
            found = 1;
        }
        else if (searchNode->value > value)
        {
            // traverse left side
            parent = searchNode;
            searchNode = searchNode->left;
        }
        else if (searchNode->value < value) // this condition checking is not required
        {
            // traverse right side
            parent = searchNode;
            searchNode = searchNode->right;
        }
    }

    if (!found)
        return 0;

    // --- For leaf node ---
    if (searchNode->left == NULL && searchNode->right == NULL)
    {
        if (parent != NULL)
        {
            // delete after removing the link to the parent pointer
            if (parent->left == searchNode)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else
            root = NULL; // the node to delete was a root node
        free(searchNode);
    }
    // --- For mid-level / parent-child node ---
    else
    {
        struct Node *deleteNode = NULL;
        struct Node *deleteNodeParent = searchNode;

        if (searchNode->left != NULL)
        {
            // get the rightmost node from left subtree
            deleteNode = searchNode->left;

            while (deleteNode->right != NULL)
            {
                deleteNodeParent = deleteNode;
                deleteNode = deleteNode->right;
            }
        }
        else
        {
            // get the leftmost node from right subtree
            deleteNode = searchNode->right;

            while (deleteNode->left != NULL)
            {
                deleteNodeParent = deleteNode;
                deleteNode = deleteNode->left;
            }
        }

        if (deleteNode->left == NULL && deleteNode->right == NULL)
        {
            // if the node to be deleted is a leaf node
            if (deleteNodeParent->left == deleteNode)
                deleteNodeParent->left = NULL;
            else
                deleteNodeParent->right = NULL;
        }
        else
        {
            if (deleteNode->left != NULL)
            {
                // attach any left child / subtree of delete node to delete node's parent
                if (deleteNodeParent == searchNode)
                    deleteNodeParent->left = deleteNode->left;
                else
                    deleteNodeParent->right = deleteNode->left;
            }
            else
            {
                // attach any right child / subtree of delete node to delete node's parent
                if (deleteNodeParent == searchNode)
                    deleteNodeParent->right = deleteNode->right;
                else
                    deleteNodeParent->left = deleteNode->right;
            }
        }

        searchNode->value = deleteNode->value; // copy the value
        free(deleteNode);                      // free the node / memory
    }

    return 1;
}

int main(void)
{
    printTreeBreadthFirst();
    printTreeInorder();
    addNode(100);
    addNode(200);
    addNode(300);
    addNode(400);
    addNode(500);
    // addNode(100);
    // addNode(200);
    // addNode(300);
    // addNode(400);
    // addNode(500);
    printTreeInorder();
    printTreeBreadthFirst();
    deleteNode(100);
    printTreeInorder();
    return 0;
}
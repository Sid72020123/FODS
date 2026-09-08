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
        root = newNode; // replace the NULL root node with the new node
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

// TODO: Fix the update node bugs
// It should actually delete the value and then add the new value
int updateNode(int old_value, int new_value)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        if (root->value == old_value)
        {
            // if the value is found in root itself, update the root
            root->value = new_value;
            return 1;
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
            return 1;
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
            parent = searchNode;
            searchNode = searchNode->left;
        }
        else if (searchNode->value < value) // this condition checking is not required
        {
            parent = searchNode;
            searchNode = searchNode->right;
        }
    }

    if (!found)
        return 0;
}

int main(void)
{
    addNode(10);
    addNode(70);
    addNode(5);
    addNode(15);
    addNode(99);
    printTreeBreadthFirst();
    updateNode(10, 88);
    updateNode(99, 55);
    printTreeBreadthFirst();
    return 0;
}
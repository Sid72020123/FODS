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
    printf("Inside!\n");
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

        searchNode->value = deleteNode->value;
        free(deleteNode);
    }

    return 1;
}

int updateNode(int old_value, int new_value)
{
    /*
    if (root == NULL)
        return 0;
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

            int found = 0;
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
                        found = 1;
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
                            found = 1;
                            traverse = NULL;
                        }
                        else
                            traverse = traverse->right;
                    }
                }
            }
            return found;
        }
    }
    */
    if (deleteNode(old_value))
    {
        addNode(new_value);
        return 1;
    }
    return 0;
}

int main(void)
{
    addNode(10);
    addNode(70);
    addNode(5);
    addNode(15);
    addNode(99);
    // printTreeBreadthFirst();
    // updateNode(10, 88);
    // updateNode(99, 55);
    printTreeBreadthFirst();
    int result = deleteNode(70);
    printf("%i\n", result);
    printTreeBreadthFirst();
    return 0;
}
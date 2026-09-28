#include <stdio.h>
#include <stdlib.h>

#include "headers/queue.h"
#include "headers/stack.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct Node
{
    int value;

    int height;

    struct Node *left;
    struct Node *right;
};

struct Queue *MAIN_QUEUE;
struct Stack *MAIN_STACK;
struct Node *root = NULL;

int getNodeHeight(struct Node *n)
{
    if (n == NULL)
        return -1;
    // else
    // {
    //     if (n->height == -1)
    //         return 0;
    //     else
    //         return n->height;
    // }
    return n->height;
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
        emptyQueue(MAIN_QUEUE);
        enqueue(root, MAIN_QUEUE);
        struct Node *traverse;

        printf("[*] TREE: ");

        while (!isQueueEmpty(MAIN_QUEUE))
        {
            dequeue(&traverse, MAIN_QUEUE);
            printf("[%3d => %d] ", traverse->value, traverse->height);

            if (traverse->left != NULL)
                enqueue(traverse->left, MAIN_QUEUE);

            if (traverse->right != NULL)
                enqueue(traverse->right, MAIN_QUEUE);
        }
    }
    printf("\n");
}

void rightRotateNode(struct Node *node, struct Node *parent)
{
    struct Node *child = node->left;

    // Perform rotation
    node->left = child->right;
    child->right = node;

    // Recalculate heights
    node->height = 1 + MAX(getNodeHeight(node->left), getNodeHeight(node->right));
    child->height = 1 + MAX(getNodeHeight(child->left), getNodeHeight(child->right));

    // Connect rotated subtree to parent
    if (parent == NULL)
    {
        // node was the root
        root = child;
    }
    else if (parent->left == node)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
    // peekStack(&parent, MAIN_STACK);

    // parent->left = child;
}

void leftRotateNode(struct Node *node, struct Node *parent)
{
    struct Node *child = node->right;

    // Perform rotation
    node->right = child->left;
    child->left = node;

    // Recalculate heights
    node->height = 1 + MAX(getNodeHeight(node->left), getNodeHeight(node->right));
    child->height = 1 + MAX(getNodeHeight(child->left), getNodeHeight(child->right));

    // Connect rotated subtree to parent
    if (parent == NULL)
    {
        // node was the root
        root = child;
    }
    else if (parent->left == node)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
    // struct Node *parent;
    // peekStack(&parent, MAIN_STACK);

    // parent->right = child;
}

int addNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;

    emptyStack(MAIN_STACK);

    if (root == NULL)
    {
        root = newNode;
        // push(root, MAIN_STACK); // No need to balance if there is only one element in tree
    }
    else
    {
        struct Node *traverse = root;

        while (traverse != NULL)
        {
            push(traverse, MAIN_STACK);

            if (traverse->value > value)
            {
                // Left side
                if (traverse->left == NULL)
                {
                    traverse->left = newNode;
                    traverse = NULL;
                }
                else
                {
                    traverse = traverse->left;
                }
            }
            else
            {
                // Right side
                if (traverse->right == NULL)
                {
                    traverse->right = newNode;
                    traverse = NULL;
                }
                else
                {
                    traverse = traverse->right;
                }
            }
        }
    }

    printf("=============================================\n");
    _debugPrintStackContents(MAIN_STACK);
    struct Node *node = NULL;
    while (!isStackEmpty(MAIN_STACK))
    {

        pop(&node, MAIN_STACK);

        // get parent of node
        struct Node *parent = NULL;
        if (!isStackEmpty(MAIN_STACK))
        {
            peekStack(&parent, MAIN_STACK);
        }

        int leftHeight = getNodeHeight(node->left);
        int rightHeight = getNodeHeight(node->right);

        node->height = 1 + MAX(leftHeight, rightHeight);
        printf("%i %i %i %i\n", node->value, node->height, leftHeight, rightHeight);
        int balanceFactor = leftHeight - rightHeight;

        if (balanceFactor > 1)
        {
            // Left
            if (value < node->left->value)
            {
                // Left-Left
                rightRotateNode(node, parent);
            }
            else
            {
                // Left-Right
                leftRotateNode(node->left, node);
                rightRotateNode(node, parent);
            }
        }
        else if (balanceFactor < -1)
        {
            // Right
            if (value >= node->right->value) // greater-than-or-equal-to sign because duplicate values are added to the right
            {
                // Right-Right
                leftRotateNode(node, parent);
            }
            else
            {
                // Right-Left
                rightRotateNode(node->right, node);
                leftRotateNode(node, parent);
            }
        }
    }

    return 1;
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

int updateNode(int old_value, int new_value)
{
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
}

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    // addNode(10);
    // addNode(20);
    // addNode(30);
    // addNode(40);
    // addNode(50);

    /* ===== Test Cases ===== */

    // => Left-Left Rotation
    // addNode(30);
    // addNode(20);
    // addNode(10);

    // => Right-Right Rotation
    // addNode(10);
    // addNode(20);
    // addNode(30);

    // => Left-Right Rotation
    // addNode(30);
    // addNode(10);
    // addNode(20);

    // => Right-Right Rotation
    // addNode(10);
    // addNode(30);
    // addNode(20);

    addNode(50);
    addNode(30);
    addNode(70);
    addNode(20);
    addNode(40);
    addNode(35);
    addNode(45);

    // addNode(10);
    // addNode(10);
    // addNode(10);
    // addNode(10);
    // addNode(5);
    printTreeBreadthFirst();

    return 0;
}
/* === AVL + BST [Adelson-Velsky & Landis + Binary Search Tree] === */

#include <stdio.h>
#include <stdlib.h>

#include "headers/queue.h"
#include "headers/stack.h"

// Macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// === Global Variables / Structures ===
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

// === Utilities ===

int get_int_input(const char *prompt, int max_tries, int *result)
{
    int input;
    char extra;
    char buffer[100];
    int tries = 0;

    while (tries < max_tries)
    {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d %c", &input, &extra) == 1)
        {
            *result = input;
            return 1; // SUCCESS
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

// === AVL Tree Methods ===

int getNodeHeight(struct Node *n)
{
    if (n == NULL)
        return -1;

    return n->height;
}

int getSize()
{
    if (root == NULL)
        return 0;
    else
    {
        emptyQueue(MAIN_QUEUE);
        enqueue(root, MAIN_QUEUE);
        struct Node *traverse;

        int size = 0;

        while (!isQueueEmpty(MAIN_QUEUE))
        {
            dequeue(&traverse, MAIN_QUEUE);
            size++;

            if (traverse->left != NULL)
                enqueue(traverse->left, MAIN_QUEUE);

            if (traverse->right != NULL)
                enqueue(traverse->right, MAIN_QUEUE);
        }
        return size;
    }
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

    emptyStack(MAIN_STACK);

    while (searchNode != NULL && !found)
    {
        push(searchNode, MAIN_STACK);

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
        else
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

        struct Node *deleteNode;
        pop(&deleteNode, MAIN_STACK); // this is required in leaf node case because the node to delete is also pushed in the stack

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
                push(deleteNodeParent, MAIN_STACK);

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
                push(deleteNodeParent, MAIN_STACK);

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

    // re-calculate height & balance all the traversed parent nodes

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

        int balanceFactor = leftHeight - rightHeight;

        if (balanceFactor > 1)
        {
            // Left

            int childBalance = getNodeHeight(node->left->left) - getNodeHeight(node->left->right);

            if (childBalance >= 0)
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

            int childBalance = getNodeHeight(node->right->left) - getNodeHeight(node->right->right);

            if (childBalance <= 0)
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

int updateNode(int old_value, int new_value)
{
    if (deleteNode(old_value))
    {
        addNode(new_value);
        return 1;
    }
    return 0;
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

// preorder traversal (root -> left -> right) [Depth-First traversal]
void printTreePreorder()
{
    if (root == NULL)
    {
        printf("[*] Tree is Empty!");
    }
    else
    {
        emptyStack(MAIN_STACK);
        push(root, MAIN_STACK);
        struct Node *traverse;

        printf("[*] TREE (preorder): ");

        while (!isStackEmpty(MAIN_STACK))
        {
            pop(&traverse, MAIN_STACK);
            printf("[%3d => %d] ", traverse->value, traverse->height);

            if (traverse->right != NULL)
                push(traverse->right, MAIN_STACK);

            if (traverse->left != NULL)
                push(traverse->left, MAIN_STACK);
        }
    }
    printf("\n");
}

// inorder traversal (left -> root -> right) [Depth-First traversal]
void printTreeInorder()
{
    if (root == NULL)
    {
        printf("[*] Tree is Empty!");
    }
    else
    {
        emptyStack(MAIN_STACK);
        struct Node *traverse = root;

        printf("[*] TREE (inorder): ");

        while (traverse != NULL || !isStackEmpty(MAIN_STACK))
        {
            while (traverse != NULL)
            {
                push(traverse, MAIN_STACK);
                traverse = traverse->left;
            }

            pop(&traverse, MAIN_STACK);
            printf("[%3d => %d] ", traverse->value, traverse->height);

            traverse = traverse->right;
        }
    }
    printf("\n");
}

// postorder traversal (left -> right -> root) [Depth-First traversal]
void printTreePostorder()
{
    if (root == NULL)
    {
        printf("[*] Tree is Empty!");
    }
    else
    {
        emptyStack(MAIN_STACK);
        struct Node *traverse = root;
        struct Node *previous = NULL;

        printf("[*] TREE (postorder): ");

        while (traverse != NULL || !isStackEmpty(MAIN_STACK))
        {
            while (traverse != NULL)
            {
                push(traverse, MAIN_STACK);
                traverse = traverse->left;
            }

            pop(&traverse, MAIN_STACK);

            if (traverse->right != NULL && traverse->right != previous)
            {
                push(traverse, MAIN_STACK);
                traverse = traverse->right;
            }
            else
            {
                printf("[%3d => %d] ", traverse->value, traverse->height);
                previous = traverse;
                traverse = NULL;
            }
        }
    }
    printf("\n");
}

// [RECURSION] inorder traversal (left -> root -> right) [Depth-First traversal]
void printTreeInorderRecursive(struct Node *node)
{
    if (node == NULL)
        return;
    printTreeInorderRecursive(node->left);
    printf("[%3d => %d] ", node->value, node->height);
    printTreeInorderRecursive(node->right);
}

// [RECURSION] preorder traversal (root -> left -> right) [Depth-First traversal]
void printTreePreorderRecursive(struct Node *node)
{
    if (node == NULL)
        return;
    printf("[%3d => %d] ", node->value, node->height);
    printTreePreorderRecursive(node->left);
    printTreePreorderRecursive(node->right);
}

// [RECURSION] postorder traversal (left -> right -> root) [Depth-First traversal]
void printTreePostorderRecursive(struct Node *node)
{
    if (node == NULL)
        return;
    printTreePostorderRecursive(node->left);
    printTreePostorderRecursive(node->right);
    printf("[%3d => %d] ", node->value, node->height);
}

// === CRUD Methods ===

void displayTree()
{
    if (root == NULL)
    {
        printf("\n[*] Tree is Empty!\n");
        return;
    }
    printTreeBreadthFirst();
    printTreePreorder();
    printTreeInorder();
    printTreePostorder();
}

void addValue()
{
    printf("\n{ TREE - ADDING New Value [%d] }\n", getSize() + 1);
    int value;
    if (get_int_input("Enter a value: ", 5, &value))
    {
        addNode(value);
        printf("\nAdded '%d' to tree.\n", value);
    }
}

void deleteValue()
{
    if (root == NULL)
    {
        printf("\n[*] Tree is Empty!\n");
        return;
    }

    printf("\n{ TREE - DELETING Value [size of tree - %d] }\n", getSize());
    int value;
    if (!get_int_input("Enter a value: ", 5, &value))
        return;

    int found = deleteNode(value);

    if (!found)
        printf("\n[*] Couldn't delete value '%d' as it was not found!\n", value);
    else
        printf("\nDeleted '%d' from tree.\n", value);
}

void updateValue()
{
    if (root == NULL)
    {
        printf("\n[*] Tree is Empty!\n");
        return;
    }

    printf("\n{ TREE - UPDATING Value [size of tree - %d] }\n", getSize());

    int value;
    if (!get_int_input("Enter a value: ", 5, &value))
        return;

    int new_value;
    if (!get_int_input("Enter the new value: ", 5, &new_value))
        return;

    int found = updateNode(value, new_value);

    if (!found)
        printf("\n[*] Couldn't update value '%d' as it was not found!\n", value);
    else
        printf("\nUpdated the value '%d' to '%d' in the tree.\n", value, new_value);
}

int main(void)
{
    MAIN_QUEUE = createNewQueue("MAIN QUEUE");
    MAIN_STACK = createNewStack("MAIN STACK");

    addNode(50);
    addNode(30);
    addNode(70);
    addNode(20);
    addNode(40);
    addNode(60);
    addNode(80);
    addNode(10);
    addNode(25);
    addNode(35);
    addNode(45);
    addNode(55);
    addNode(65);
    addNode(75);
    addNode(85);
    printTreeBreadthFirst();

    return 0;
}
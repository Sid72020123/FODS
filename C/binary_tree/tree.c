/* === Simple Binary Tree === */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

// === Utilities ===

void clearInputBuffer()
{
    // Clear input buffer
    while (getchar() != '\n')
        ;
}

int validateDigits(char *input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        if (isdigit(input[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}

int get_int_input(const char *prompt, int max_tries, int *result)
{
    char input[100];
    // char extra;
    // char buffer[100];
    // char *buffer;
    int tries = 0;

    while (tries < max_tries)
    {
        // clearInputBuffer();
        printf("%s", prompt);
        // gets(input);

        // fgets(buffer, sizeof(buffer), stdin);
        // scanf("%s", buffer);

        // char ch = getchar();

        // if (!(ch == '\n'))
        // {
        // ungetc(ch, stdin); // put the extracted character back into input buffer

        if (gets(input) != NULL)
        {
            if (input[0] != '\0')
            {
                if (validateDigits(input))
                {
                    *result = atoi(input);
                    return 1; // SUCCESS
                }
            }
        }

        // clearInputBuffer();
        printf("Invalid input. Try again.\n");

        tries++;
    }

    printf("\nMaximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

// === Binary Tree Methods ===

int getSize()
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        emptyQueue();
        enqueue(root);
        struct Node *traverse;

        int size = 0;

        while (!isQueueEmpty())
        {
            dequeue(&traverse);
            size++;

            if (traverse->left != NULL)
                enqueue(traverse->left);

            if (traverse->right != NULL)
                enqueue(traverse->right);
        }
        return size;
    }
}

void addNode(int value)
{
    struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        emptyQueue();
        enqueue(root);

        struct Node *traverse;
        struct Node *parentNode = NULL;

        while (!isQueueEmpty())
        {
            dequeue(&traverse);
            parentNode = traverse;
            if (traverse->left == NULL || traverse->right == NULL)
            {
                emptyQueue();
                // break;
            }
            else
            {
                enqueue(traverse->left);
                enqueue(traverse->right);
            }
        }

        if (parentNode->left == NULL)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;
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

// preorder traversal (root -> left -> right) [Depth-First traversal]
void printTreePreorder()
{
    if (root == NULL)
    {
        printf("[*] Tree is Empty!");
    }
    else
    {
        emptyStack();
        push(root);
        struct Node *traverse;

        printf("[*] TREE (preorder): ");

        while (!isStackEmpty())
        {
            pop(&traverse);
            printf("[%3d] ", traverse->value);

            if (traverse->right != NULL)
                push(traverse->right);

            if (traverse->left != NULL)
                push(traverse->left);
        }

        printf("\n");
    }
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
        emptyStack();
        struct Node *traverse = root;

        printf("[*] TREE (inorder): ");

        while (traverse != NULL || !isStackEmpty())
        {
            while (traverse != NULL)
            {
                push(traverse);
                traverse = traverse->left;
            }

            pop(&traverse);
            printf("[%3d] ", traverse->value);

            traverse = traverse->right;
        }

        printf("\n");
    }
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
        emptyStack();
        struct Node *traverse = root;
        struct Node *previous = NULL;

        printf("[*] TREE (postorder): ");

        while (traverse != NULL || !isStackEmpty())
        {
            while (traverse != NULL)
            {
                push(traverse);
                traverse = traverse->left;
            }

            pop(&traverse);

            if (traverse->right != NULL && traverse->right != previous)
            {
                push(traverse);
                traverse = traverse->right;
            }
            else
            {
                printf("[%3d] ", traverse->value);
                previous = traverse;
                traverse = NULL;
            }
        }

        printf("\n");
    }
}

// [RECURSION] inorder traversal (left -> root -> right) [Depth-First traversal]
void printTreeInorderRecursive(struct Node *node)
{
    if (node == NULL)
        return;
    printTreeInorderRecursive(node->left);
    printf("[%3d] ", node->value);
    printTreeInorderRecursive(node->right);
}

// [RECURSION] preorder traversal (root -> left -> right) [Depth-First traversal]
void printTreePreorderRecursive(struct Node *node)
{
    if (node == NULL)
        return;
    printf("[%3d] ", node->value);
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
    printf("[%3d] ", node->value);
}

int updateNode(int old_value, int new_value)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        emptyQueue();
        enqueue(root);
        struct Node *traverse;
        int found = 0;

        while (!isQueueEmpty() && !found)
        {
            dequeue(&traverse);

            if (traverse->value == old_value)
            {
                traverse->value = new_value;
                emptyQueue();
                found = 1;
            }

            if (traverse->left != NULL)
                enqueue(traverse->left);

            if (traverse->right != NULL)
                enqueue(traverse->right);
        }

        return found;
    }
}

// Function to get the rightmost node in tree
struct Node *getRightmost(struct Node *node, struct Node **replacementParent)
{
    if (node == NULL)
        return NULL;

    struct Node *searchNode = node;

    while (searchNode->right != NULL)
    {
        *replacementParent = searchNode;
        searchNode = searchNode->right;
    }

    return searchNode;
}

int deleteNode(int value)
{
    if (root == NULL)
    {
        return 0;
    }

    // --- If the value is found in the root itself ---
    /*
        -> Delete the root node if it has no children.
        -> Else, get the rightmost node and replace the root node's value with that node,
            then, delete the rightmost node
    */

    if (root->value == value)
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->right == NULL)
        {
            struct Node *onlyChild = root->left;
            free(root);
            root = onlyChild;
        }
        else if (root->left == NULL)
        {
            struct Node *onlyChild = root->right;
            free(root);
            root = onlyChild;
        }
        else
        {
            struct Node *replacementParent = root;
            struct Node *replacement = getRightmost(root, &replacementParent);

            root->value = replacement->value;
            replacementParent->right = replacement->left;

            free(replacement);
        }
        return 1;
    }

    emptyQueue();
    enqueue(root);

    struct Node *traverse;
    struct Node *parent = NULL;
    int found = 0;

    while (!isQueueEmpty())
    {
        dequeue(&traverse);

        if (traverse->value == value)
        {
            emptyQueue();
            found = 1;
        }
        else
        {
            if (traverse->left != NULL && traverse->left->value == value && !found)
            {

                parent = traverse;
                emptyQueue();
                enqueue(traverse->left);
            }
            else if (traverse->right != NULL && traverse->right->value == value && !found)
            {

                parent = traverse;
                emptyQueue();
                enqueue(traverse->right);
            }
            else
            {
                if (traverse->left != NULL)
                    enqueue(traverse->left);
                if (traverse->right != NULL)
                    enqueue(traverse->right);
            }
        }
    }

    if (!found)
        return 0;

    // --- If the value is found in the leaf node ---
    if (traverse->left == NULL && traverse->right == NULL)
    {
        if (parent->left == traverse)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(traverse);
    }
    // --- If traverse has only a left child, promote that child up directly ---
    else if (traverse->right == NULL)
    {
        struct Node *onlyChild = traverse->left;
        if (parent->left == traverse)
            parent->left = onlyChild;
        else
            parent->right = onlyChild;
        free(traverse);
    }
    // --- If the value is found in the sibling nodes / middle-level nodes which have two children ---
    else
    {
        struct Node *replacementParent = traverse;
        struct Node *replacement = getRightmost(traverse, &replacementParent);

        traverse->value = replacement->value;
        replacementParent->right = replacement->left;

        free(replacement);
    }
    return 1;
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
    addNode(10);
    addNode(20);
    addNode(30);
    addNode(40);
    addNode(50);
    addNode(60);
    addNode(70);

    int choice = 0;
    do
    {
        printf("\n===== MENU [TREE] =====\n");
        printf("1. Display Tree (using various methods)\n");
        printf("2. Add value\n");
        printf("3. Delete Value\n");
        printf("4. Update Value\n");
        printf("5. Exit\n");

        if (get_int_input("Enter your choice: ", 3, &choice))
        {
            switch (choice)
            {
            case 1:
                printf("\n");
                displayTree();
                break;
            case 2:
                addValue();
                break;
            case 3:
                deleteValue();
                break;
            case 4:
                updateValue();
                break;
            case 5:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
            }
        }

    } while (choice != 5);

    return 0;
    /*
    printTreeBreadthFirst();
    addNode(10);
    addNode(10);
    addNode(10);
    addNode(10);
    addNode(10);
    addNode(20);
    addNode(30);
    addNode(40);
    addNode(50);
    printTreeBreadthFirst();

    updateNode(30, 99);
    printTreeBreadthFirst();

    deleteNode(10);
    printTreeBreadthFirst();
    deleteNode(20);
    printTreeBreadthFirst();
    printTreePreorder();
    printTreeInorder();
    printTreePostorder();

    printf("[*] TREE (preorder - RECURSION): ");
    printTreePreorderRecursive(root);
    printf("\n");
    printf("[*] TREE (inorder - RECURSION): ");
    printTreeInorderRecursive(root);
    printf("\n");
    printf("[*] TREE (postorder - RECURSION): ");
    printTreePostorderRecursive(root);
    printf("\n");
    */
    return 0;
}
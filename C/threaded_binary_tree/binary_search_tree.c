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

// === Utilities ===

int get_int_input(const char *prompt, int max_tries, int *result)
{
    int input;
    char extra;
    // char buffer[100];
    // char *buffer;
    int tries = 0;

    while (tries < max_tries)
    {
        printf("%s", prompt);

        // fgets(buffer, sizeof(buffer), stdin);
        // scanf("%s", buffer);

        char ch = getchar();

        if (!(ch == '\n'))
        {
            ungetc(ch, stdin); // put the extracted character back into input buffer

            if (scanf("%d%c", &input, &extra) == 2 && extra == '\n')
            {
                *result = input;
                return 1; // SUCCESS
            }

            // Clear input buffer
            while (getchar() != '\n')
                ;
        }

        printf("Invalid input. Try again.\n");

        tries++;
    }

    printf("\nMaximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

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
        else
        {
            // traverse right side
            parent = searchNode;

            if (searchNode->right != NULL && !searchNode->rightThread)
                searchNode = searchNode->right;
            else
                searchNode = NULL;
        }
    }

    if (!found)
        return 0;

    // --- For leaf node ---
    if (searchNode->left == NULL &&
        (searchNode->right == NULL || searchNode->rightThread))
    {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == searchNode)
            parent->left = NULL;
        else
        {
            // delete after preserving the inorder thread
            parent->right = searchNode->right;
            parent->rightThread = searchNode->rightThread;
        }

        free(searchNode);
    }

    // --- If traverse has only a left child, promote that child up directly ---
    else if (searchNode->right == NULL || searchNode->rightThread)
    {
        struct Node *onlyChild = searchNode->left;
        struct Node *replacement = onlyChild;

        while (replacement->right != NULL && !replacement->rightThread)
            replacement = replacement->right;

        replacement->right = searchNode->right;
        replacement->rightThread = searchNode->rightThread;

        if (parent == NULL)
        {
            root = onlyChild;
        }
        else if (parent->left == searchNode)
        {
            parent->left = onlyChild;
        }
        else
        {
            parent->right = onlyChild;
            parent->rightThread = 0;
        }

        free(searchNode);
    }

    // --- If the value is found in the sibling nodes / middle-level nodes which have two children ---
    else
    {
        struct Node *deleteNode = searchNode->right;
        struct Node *deleteNodeParent = searchNode;

        // get the leftmost node from right subtree
        while (deleteNode->left != NULL)
        {
            deleteNodeParent = deleteNode;
            deleteNode = deleteNode->left;
        }

        searchNode->value = deleteNode->value; // copy the value

        /*
            deleteNode cannot have a left child because it is the
            leftmost node of the right subtree.
        */
        if (deleteNodeParent == searchNode)
        {
            searchNode->right = deleteNode->right;
            searchNode->rightThread = deleteNode->rightThread;
        }
        else
        {
            if (deleteNode->right != NULL && !deleteNode->rightThread)
            {
                // attach any right child / subtree of delete node to delete node's parent
                deleteNodeParent->left = deleteNode->right;
            }
            else
            {
                // deleteNode was a leaf / threaded leaf
                deleteNodeParent->left = NULL;
            }
        }

        free(deleteNode); // free the node / memory
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
// === CRUD Methods ===

void displayTree()
{
    if (root == NULL)
    {
        printf("\n[*] Tree is Empty!\n");
        return;
    }
    printTreeBreadthFirst();
    printTreeInorder();
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
    addNode(100);
    addNode(200);
    addNode(300);
    addNode(400);
    addNode(500);
    addNode(600);
    addNode(700);

    int choice = 0;
    do
    {
        printf("\n===== MENU [THREADED - SEARCH TREE] =====\n");
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
    printTreeInorder();
    // addNode(100);
    // addNode(200);
    // addNode(300);
    // addNode(400);
    // addNode(500);
    // addNode(100);
    // addNode(200);
    // addNode(300);
    // addNode(400);
    // addNode(500);

    addNode(500);
    addNode(300);
    addNode(700);
    addNode(200);
    addNode(400);
    addNode(600);
    addNode(800);
    printTreeInorder();
    printTreeBreadthFirst();
    deleteNode(500);
    // updateNode(200, 999);
    printTreeInorder();
    return 0;
    */
}
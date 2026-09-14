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

// Function to get the rightmost node in tree
struct Node *getRightMostNode(struct Node *node, struct Node **replacementParent)
{
    if (node == NULL)
        return NULL;

    struct Node *searchNode = node;

    while (searchNode->right != NULL)
    {
        *replacementParent = searchNode;
        if (searchNode->rightThread)
            break;
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
        if (root->left == NULL && (root->right == NULL || root->rightThread))
        {
            free(root);
            root = NULL;
        }
        else if (root->right == NULL || root->rightThread)
        {
            struct Node *onlyChild = root->left;

            struct Node *parent = onlyChild;
            struct Node *replacement = getRightMostNode(onlyChild, &parent);

            replacement->right = root->rightThread ? root->right : NULL;
            replacement->rightThread = root->rightThread;

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
            struct Node *replacement = getRightMostNode(root->left, &replacementParent);

            root->value = replacement->value;

            if (replacementParent == root)
            {
                replacementParent->left = replacement->left;
            }
            else
            {
                if (replacement->left != NULL)
                {
                    replacementParent->right = replacement->left;
                    replacementParent->rightThread = 0;
                }
                else
                {
                    // replacement was the rightmost node, so replacementParent
                    // becomes the inorder predecessor of root
                    replacementParent->right = root;
                    replacementParent->rightThread = 1;
                }
            }

            if (replacement->left != NULL)
            {
                struct Node *p = replacement->left;

                while (p->right != NULL && !p->rightThread)
                    p = p->right;

                p->right = replacement->rightThread ? replacement->right : root;
                p->rightThread = 1;
            }

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
            if (traverse->left != NULL &&
                traverse->left->value == value &&
                !found)
            {
                parent = traverse;
                emptyQueue();
                enqueue(traverse->left);
            }
            else if (traverse->right != NULL &&
                     !traverse->rightThread &&
                     traverse->right->value == value &&
                     !found)
            {
                parent = traverse;
                emptyQueue();
                enqueue(traverse->right);
            }
            else
            {
                if (traverse->left != NULL)
                    enqueue(traverse->left);

                if (traverse->right != NULL && !traverse->rightThread)
                    enqueue(traverse->right);
            }
        }
    }

    if (!found)
        return 0;

    // --- If the value is found in the leaf node ---
    if (traverse->left == NULL &&
        (traverse->right == NULL || traverse->rightThread))
    {
        if (parent->right == traverse)
        {
            parent->right = traverse->rightThread ? traverse->right : NULL;
            parent->rightThread = traverse->rightThread;
        }

        if (parent->left == traverse)
            parent->left = NULL;
        else if (parent->right == traverse)
            parent->right = NULL;

        free(traverse);
    }

    // --- If traverse has only a left child, promote that child up directly ---
    else if (traverse->right == NULL || traverse->rightThread)
    {
        struct Node *onlyChild = traverse->left;

        struct Node *predParent = onlyChild;
        struct Node *pred = getRightMostNode(onlyChild, &predParent);

        pred->right = traverse->rightThread ? traverse->right : NULL;
        pred->rightThread = traverse->rightThread;

        if (parent->left == traverse)
            parent->left = onlyChild;
        else
        {
            parent->right = onlyChild;
            parent->rightThread = 0;
        }

        free(traverse);
    }

    // --- If traverse has only a right child, promote that child up directly ---
    else if (traverse->left == NULL)
    {
        struct Node *onlyChild = traverse->right;

        if (parent->left == traverse)
            parent->left = onlyChild;
        else
        {
            parent->right = onlyChild;
            parent->rightThread = 0;
        }

        free(traverse);
    }

    // --- If the value is found in the sibling nodes / middle-level nodes which have two children ---
    else
    {
        struct Node *replacementParent = traverse;
        struct Node *replacement = getRightMostNode(traverse->left, &replacementParent);

        traverse->value = replacement->value;

        if (replacementParent == traverse)
        {
            replacementParent->left = replacement->left;
        }
        else
        {
            if (replacement->left != NULL)
            {
                replacementParent->right = replacement->left;
                replacementParent->rightThread = 0;
            }
            else
            {
                // replacement was the rightmost node, so replacementParent
                // becomes the inorder predecessor of traverse
                replacementParent->right = traverse;
                replacementParent->rightThread = 1;
            }
        }

        if (replacement->left != NULL)
        {
            struct Node *p = replacement->left;

            while (p->right != NULL && !p->rightThread)
                p = p->right;

            p->right = replacement->rightThread ? replacement->right : traverse;
            p->rightThread = 1;
        }

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
        printf("\n===== MENU [THREADED - TREE] =====\n");
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
    // deleteNode(500);
    deleteNode(40);
    printTreeInorder();
    return 0;
    */
}
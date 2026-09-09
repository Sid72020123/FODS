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

// === Binary Tree Methods ===

int getSize()
{
    if (root == NULL)
        return 0;
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
    addNode(100);
    addNode(300);
    addNode(50);
    addNode(250);
    addNode(70);
    addNode(800);
    addNode(700);

    int choice = 0;
    do
    {
        printf("\n===== MENU [Binary Search Tree] =====\n");
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
}

// int main(void)
// {
//     addNode(10);
//     addNode(70);
//     addNode(5);
//     addNode(15);
//     addNode(99);
//     // printTreeBreadthFirst();
//     // updateNode(10, 88);
//     // updateNode(99, 55);
//     printTreeBreadthFirst();
//     int result = deleteNode(70);
//     printf("%i\n", result);
//     printTreeBreadthFirst();
//     printf("%d\n", getSize());
//     printTreeBreadthFirst();
//     printTreePreorder();
//     printTreeInorder();
//     printTreePostorder();
//     printTreePreorderRecursive(root);
//     printTreeInorderRecursive(root);
//     printTreePostorderRecursive(root);
//     return 0;
// }
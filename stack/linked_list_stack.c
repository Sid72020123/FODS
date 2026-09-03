#include <stdio.h>
#include <stdlib.h>

// === Global Variables / Structures ===

struct Node
{
    int value;
    struct Node *next;
};

struct Node *top = NULL;

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

// === Stack Methods ===

int isEmpty()
{
    return top == NULL;
}

int getSize()
{
    if (isEmpty())
        return 0;
    else
    {
        int size = 0;
        struct Node *traverse = top;

        while (traverse != NULL)
        {
            size++;
            traverse = traverse->next;
        }
        return size;
    }
}

void push(int value)
{
    struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
    newNode->value = value;
    newNode->next = NULL;

    if (top == NULL)
        top = newNode;
    else
    {
        newNode->next = top;
        top = newNode;
    }
}

int pop()
{
    if (top == NULL)
    {
        printf("\n[*] Stack is Empty!\n");
        return -0;
    }

    int value = top->value;
    struct Node *deleteNode = top;

    top = top->next;

    free(deleteNode);
    return value;
}

int peek()
{
    if (isEmpty())
    {
        printf("\n[*] Stack is Empty!\n");
        return -0;
    }

    return top->value;
}

// === CRUD Methods ===

void displayStack()
{
    if (isEmpty())
    {
        printf("\n[*] Stack is Empty!\n");
        return;
    }

    printf("\n[*] STACK:\n");

    struct Node *traverse = top;

    while (traverse != NULL)
    {
        printf("\t[%3d]\n", traverse->value);
        traverse = traverse->next;
    }

    printf("\n");
}

void addValue()
{
    printf("\n{ STACK - ADDING New Value [%d] }\n", getSize() + 1);
    int value;
    if (get_int_input("Enter a value: ", 5, &value))
        push(value);
}

void deleteValue()
{
    if (isEmpty())
    {
        printf("\n[*] Stack is Empty!\n");
        return;
    }

    printf("\n{ STACK - DELETING Value [size of stack - %d] }\n", getSize());

    int value;
    if (!get_int_input("Enter a value: ", 5, &value))
        return;

    struct Node *searchNode = top, *parentNode = NULL;
    int found = 0;

    while (searchNode != NULL && !found)
    {
        if (searchNode->value == value)
        {
            found = 1;
        }
        else
        {
            parentNode = searchNode;
            searchNode = searchNode->next;
        }
    }

    if (!found)
        printf("\n[*] Couldn't delete value '%d' as it was not found!\n", value);
    else
    {
        // Deleting top
        if (searchNode == top)
            top = top->next;
        else
            parentNode->next = searchNode->next;

        free(searchNode);
    }
}

void updateValue()
{
    if (isEmpty())
    {
        printf("\n[*] Stack is Empty!\n");
        return;
    }

    printf("\n{ STACK - UPDATING Value [size of stack - %d] }\n", getSize());

    int value;
    if (!get_int_input("Enter a value: ", 5, &value))
        return;

    int new_value;
    if (!get_int_input("Enter the new value: ", 5, &new_value))
        return;

    struct Node *searchNode = top;
    int found = 0;

    while (searchNode != NULL && !found)
    {
        if (searchNode->value == value)
        {
            searchNode->value = new_value;
            found = 1;
        }
        else
        {
            searchNode = searchNode->next;
        }
    }

    if (!found)
        printf("\n[*] Couldn't update value '%d' as it was not found!\n", value);
}

int main()
{
    push(100);
    push(200);
    push(300);
    push(400);

    // displayStack();

    // pop();
    // pop();

    // displayStack();

    // push(50);
    // push(60);

    // displayStack();

    int choice = 0;
    do
    {
        printf("\n===== MENU [STACK - Linked List] =====\n");
        printf("1. Display Stack\n");
        printf("2. Add value\n");
        printf("3. Delete Value\n");
        printf("4. Update Value\n");
        printf("5. Exit\n");

        if (get_int_input("Enter your choice: ", 3, &choice))
        {
            switch (choice)
            {
            case 1:
                displayStack();
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
#include <stdio.h>
#include <stdlib.h>

// === Global Variables / Structures ===

struct Node
{
    int value;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

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

// === Queue Methods ===

int isEmpty()
{
    return front == NULL;
}

int getSize()
{
    if (isEmpty())
        return 0;
    else
    {
        int size = 0;
        struct Node *traverse = front;

        while (traverse != NULL)
        {
            size++;
            traverse = traverse->next;
        }
        return size;
    }
}

void enqueue(int value)
{
    struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
    newNode->value = value;
    newNode->next = NULL;

    if (front == NULL)
        front = newNode, rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
        // struct Node *traverse = front;
        // while (traverse->next != NULL)
        // {
        //     traverse = traverse->next;
        // }
        // traverse->next = newNode;
        // rear = traverse->next;
    }
}

int dequeue()
{
    if (front == NULL)
    {
        printf("\n[*] Queue is Empty!\n");
        return -0;
    }

    int value = front->value;

    if (front == rear)
    {
        free(front);
        front = rear = NULL;
    }
    else
    {
        struct Node *deleteNode = front;
        front = front->next;
        free(deleteNode);
    }
    return value;
}

int peek()
{
    if (isEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return -0;
    }

    return front->value;
}

// === CRUD Methods ===

void displayQueue()
{
    if (isEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return;
    }

    printf("\n[*] Queue: ");

    struct Node *traverse = front;

    while (traverse != NULL)
    {
        printf("[%3d] ", traverse->value);
        traverse = traverse->next;
    }

    printf("\n");
}

void addValue()
{
    printf("\n{ QUEUE - ADDING New Value [%d] }\n", getSize() + 1);
    int value;
    if (get_int_input("Enter a value: ", 5, &value))
        enqueue(value);
}

void deleteValue()
{
    if (isEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return;
    }

    printf("\n{ QUEUE - DELETING Value [size of queue - %d] }\n", getSize());
    int value;
    if (!get_int_input("Enter a value: ", 5, &value))
        return;

    struct Node *searchNode = front, *parentNode = NULL;
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
        // Deleting front
        if (searchNode == front)
            front = front->next;
        else
            parentNode->next = searchNode->next;

        // Deleting rear
        if (searchNode == rear)
            rear = parentNode;

        free(searchNode);
    }
}

void updateValue()
{
    if (isEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return;
    }

    printf("\n{ QUEUE - UPDATING Value [size of queue - %d] }\n", getSize());

    int value;
    if (!get_int_input("Enter a value: ", 5, &value))
        return;

    int new_value;
    if (!get_int_input("Enter the new value: ", 5, &new_value))
        return;

    struct Node *searchNode = front;
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
    enqueue(100);
    enqueue(200);
    enqueue(300);
    enqueue(400);

    // displayQueue();

    // dequeue();
    // dequeue();

    // displayQueue();

    // enqueue(50);
    // enqueue(60);

    // displayQueue();

    int choice = 0;
    do
    {
        printf("\n===== MENU [QUEUE - Linked List] =====\n");
        printf("1. Display Queue\n");
        printf("2. Add value\n");
        printf("3. Delete Value\n");
        printf("4. Update Value\n");
        printf("5. Exit\n");

        if (get_int_input("Enter your choice: ", 3, &choice))
        {
            switch (choice)
            {
            case 1:
                displayQueue();
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
#include <stdio.h>
#define SIZE 10

// === Global Variables ===

int top = -1;
int STACK[SIZE];

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

// === STACK Methods ===

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return (top + 1) == SIZE;
}

int getSize()
{
    if (isEmpty())
        return 0;
    else
        return top + 1;
}

void push(int value)
{
    if (!isFull())
    {
        top++;
        STACK[top] = value;
    }
}

int pop()
{
    if (top == -1)
    {
        printf("\n[*] Stack is Empty!\n");
        return -0;
    }

    int top_value = STACK[top];

    if (top == 0)
        top = -1;
    else
        top--;

    return top_value;
}

int peek()
{
    if (isEmpty())
    {
        printf("\n[*] Stack is Empty!\n");
        return -0;
    }

    return STACK[top];
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

    for (int i = top; i >= 0; i--)
        printf("\t[%3d]\n", STACK[i]);

    printf("\n");
}

void addValue()
{
    if (isFull())
        printf("\n[*] Stack is Full!\n");
    else
    {
        int value;

        printf("\n{ STACK - ADDING New Value [%d / %d] }\n", getSize() + 1, SIZE);

        if (get_int_input("Enter a value: ", 5, &value))
            push(value);
    }
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
    if (!get_int_input("Enter the value to delete: ", 5, &value))
        return;

    int count = getSize();
    int TEMP_STACK[count];
    int temp_count = 0;
    int found = 0;

    while (!isEmpty())
    {
        int temp_value = pop();

        if (temp_value == value && !found)
        {
            found = 1;
            continue;
        }

        TEMP_STACK[temp_count++] = temp_value;
    }

    for (int i = temp_count - 1; i >= 0; i--)
    {
        push(TEMP_STACK[i]);
    }

    if (!found)
        printf("\n[*] Couldn't delete value '%d' as it was not found!\n", value);
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
    if (!get_int_input("Enter the value to update: ", 5, &value))
        return;

    int new_value;
    if (!get_int_input("Enter the new value: ", 5, &new_value))
        return;

    int found = 0;

    for (int i = top; i >= 0; i--)
    {
        if (STACK[i] == value)
        {
            STACK[i] = new_value;
            found = 1;
            break;
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
        printf("\n===== MENU =====\n");
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

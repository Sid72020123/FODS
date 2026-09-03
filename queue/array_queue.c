#include <stdio.h>
#define SIZE 10

// === Global Variables ===

int front = -1, rear = -1;
int QUEUE[SIZE];

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
    return front == -1;
}

int isFull()
{
    return (rear + 1) % SIZE == front;
}

int getSize()
{
    if (isEmpty())
        return 0;
    else
    {
        // int size = 0, i = front;

        // while (1)
        // {
        //     size++;
        //     if (i == rear)
        //         break;
        //     i = (i + 1) % SIZE;
        // }
        // return size;
        return ((rear - front + SIZE) % SIZE) + 1;
    }
}

void enqueue(int value)
{

    if (front == -1)
        front = 0;

    rear = (rear + 1) % SIZE;
    QUEUE[rear] = value;
}

int dequeue()
{
    if (front == -1)
    {
        printf("\n[*] Queue is Empty!\n");
        return -0;
    }

    int first_value = QUEUE[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
    return first_value;
}

int peek()
{
    if (isEmpty())
    {
        printf("\n[*] Queue is Empty!\n");
        return -0;
    }

    return QUEUE[front];
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

    int i = front;

    while (1)
    {
        printf("[%3d] ", QUEUE[i]);

        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }

    printf("\n");
}

void addValue()
{
    if (isFull())
        printf("\n[*] Queue is Full!\n");
    else
    {
        int value;

        printf("\n{ QUEUE - ADDING New Value [%d / %d] }\n", getSize() + 1, SIZE);

        if (get_int_input("Enter a value: ", 5, &value))
            enqueue(value);
    }
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

    int index = 0, found = 0, count = getSize();
    int TEMP_QUEUE[count];

    for (int i = 0; i < count; i++)
    {
        int temp_value = dequeue();

        if (temp_value == value)
        {
            found = 1;
            continue;
        }

        TEMP_QUEUE[index++] = temp_value;
    }

    for (int i = 0; i < index; i++)
    {
        enqueue(TEMP_QUEUE[i]);
    }

    if (!found)
        printf("\n[*] Couldn't delete value '%d' as it was not found!\n", value);
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
    if (!get_int_input("Enter the value to update: ", 5, &value))
        return;

    int new_value;
    if (!get_int_input("Enter the new value: ", 5, &new_value))
        return;

    int index = front, found = 0, count = getSize();

    for (int i = 0; i < count; i++)
    {
        if (QUEUE[index] == value && !found)
        {
            QUEUE[index] = new_value;
            found = 1;
            break;
        }

        index = (index + 1) % SIZE;
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
        printf("\n===== MENU =====\n");
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

/*
#include <stdio.h>

int front = -1, rear = 0;
int QUEUE[5] = {0};

void enqueue(int n)
{
    if (rear == 5)
    {
        printf("Queue Full\n");
        return;
    }

    if (front < 0)
        front = 0;

    QUEUE[rear++] = n;
}

int dequeue()
{
    if (front == rear)
    {
        printf("Queue Empty\n");
        return -1;
    }

    return QUEUE[front++];
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    enqueue(60);

    printf("%d ", dequeue());
    printf("%d ", dequeue());
    printf("%d ", dequeue());
    printf("%d ", dequeue());
    printf("%d ", dequeue());
    printf("%d ", dequeue());

    return 0;
}
*/
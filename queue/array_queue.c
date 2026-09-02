#include <stdio.h>
#define SIZE 10

// === Global Variables ===

int front = -1, rear = -1;
int QUEUE[SIZE];

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

        printf("Enter a value [%d / %d]: ", getSize() + 1, SIZE);
        scanf("%d", &value);
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

    int value;

    printf("Enter the value to delete [size of queue - %d]: ", getSize());
    scanf("%d", &value);

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

    int value, new_value;

    printf("Enter the value to update [size of queue - %d]: ", getSize());
    scanf("%d", &value);
    printf("Enter the new value: ");
    scanf("%d", &new_value);

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
    // enqueue(10);
    // enqueue(20);
    // enqueue(30);
    // enqueue(40);

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
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Option Entered! Please enter numbers only...\n");
        }
        else
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
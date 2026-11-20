/* === Heap (using Array) === */
// Note: this is a Max Heap (the largest value is always at the root, index 1)
// Index 0 of the array is left empty (unused), so the heap lives in HEAP[1] ... HEAP[count]

#include <stdio.h>
#include <stdlib.h>

// === Global Variables / Structures ===
#define SIZE 15

int HEAP[SIZE + 1]; // +1 because index 0 is never used
int count = 0;

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

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// === Heap Methods ===

int isEmpty()
{
    return count == 0;
}

int isFull()
{
    return count == SIZE;
}

// for a node at index i: parent = i / 2, left child = 2i, right child = 2i + 1

void heapifyUp(int index)
{
    // move the value at "index" up until its parent is greater than or equal to it
    while (index > 1)
    {
        int parent = index / 2;

        if (HEAP[parent] >= HEAP[index])
            break;

        swap(&HEAP[parent], &HEAP[index]);
        index = parent;
    }
}

void heapifyDown(int index)
{
    // move the value at "index" down until both of its children are smaller than or equal to it
    while (1)
    {
        int left = 2 * index;
        int right = 2 * index + 1;
        int largest = index;

        if (left <= count && HEAP[left] > HEAP[largest])
            largest = left;

        if (right <= count && HEAP[right] > HEAP[largest])
            largest = right;

        if (largest == index)
            break;

        swap(&HEAP[index], &HEAP[largest]);
        index = largest;
    }
}

int findValue(int value)
{
    // returns the index of the first matching value, or -1 if not found
    for (int i = 1; i <= count; i++)
    {
        if (HEAP[i] == value)
            return i;
    }

    return -1;
}

void insert(int value)
{
    if (isFull())
        return;

    count++;
    HEAP[count] = value;
    heapifyUp(count);
}

void removeAt(int index)
{
    // replace the value with the last value of the heap, then fix the heap
    HEAP[index] = HEAP[count];
    count--;

    if (index <= count)
    {
        heapifyUp(index);
        heapifyDown(index);
    }
}

// === CRUD Methods ===

void displayHeap()
{
    if (isEmpty())
    {
        printf("\n[*] Heap is Empty!\n");
        return;
    }

    printf("\n[*] HEAP [%d / %d]:\n", count, SIZE);

    for (int i = 1; i <= count; i++)
        printf("\t[%2d] %d\n", i, HEAP[i]);

    printf("\n\tMax (root) = %d\n", HEAP[1]);
}

void addValue()
{
    if (isFull())
    {
        printf("\n[*] Heap is Full!\n");
        return;
    }

    int value;

    printf("\n{ HEAP - ADDING New Value [%d / %d] }\n", count + 1, SIZE);

    if (get_int_input("Enter a value: ", 5, &value))
        insert(value);
}

void deleteValue()
{
    if (isEmpty())
    {
        printf("\n[*] Heap is Empty!\n");
        return;
    }

    printf("\n{ HEAP - DELETING Value [size of heap - %d] }\n", count);

    int value;
    if (!get_int_input("Enter the value to delete: ", 5, &value))
        return;

    int index = findValue(value);

    if (index == -1)
        printf("\n[*] Couldn't delete value '%d' as it was not found!\n", value);
    else
        removeAt(index);
}

void updateValue()
{
    if (isEmpty())
    {
        printf("\n[*] Heap is Empty!\n");
        return;
    }

    printf("\n{ HEAP - UPDATING Value [size of heap - %d] }\n", count);

    int value;
    if (!get_int_input("Enter the value to update: ", 5, &value))
        return;

    int new_value;
    if (!get_int_input("Enter the new value: ", 5, &new_value))
        return;

    int index = findValue(value);

    if (index == -1)
    {
        printf("\n[*] Couldn't update value '%d' as it was not found!\n", value);
        return;
    }

    HEAP[index] = new_value;
    heapifyUp(index);
    heapifyDown(index);
}

int main()
{
    insert(50);
    insert(30);
    insert(40);
    insert(10);
    insert(20);

    int choice = 0;
    do
    {
        printf("\n===== MENU [Heap] =====\n");
        printf("1. Display Heap\n");
        printf("2. Add value\n");
        printf("3. Delete Value\n");
        printf("4. Update Value\n");
        printf("5. Exit\n");

        if (get_int_input("Enter your choice: ", 3, &choice))
        {
            switch (choice)
            {
            case 1:
                displayHeap();
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

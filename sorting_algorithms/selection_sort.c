// Selection Sort

#include <stdio.h>

int *selectionSort(int arr[], int size)
{
    int smallest = arr[0];
    for (int i = 0; i < size - 1; i++)
    {
        int j = i + 1;
        for (; j < size; j++)
        {
            if (arr[j] < smallest)
                smallest = arr[j];
        }
        arr[j] = arr[i];
        arr[i] = smallest;
        printf("%d\n", arr[i]);
    }
    return arr;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int original_array[] = {1, 5, 8, 6, 7, 3, 9, 4, 2, 0};
    int n = sizeof(original_array) / sizeof(original_array[0]);
    printArray(original_array, n);

    int *sorted_array = selectionSort(original_array, n);
    printArray(sorted_array, n);
    return 0;
}
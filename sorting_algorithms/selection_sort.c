// Selection Sort

#include <stdio.h>

void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
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

    selectionSort(original_array, n);
    printArray(original_array, n);
    return 0;
}
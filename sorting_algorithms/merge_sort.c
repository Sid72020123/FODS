/*
*** === Merge Sort === ***

=> Program to perform merge sort on an array.

=> Algorithm:
   -> Split the array into two halves.
   -> Recursively sort the left half.
   -> Recursively sort the right half.
   -> Merge the two sorted halves into one sorted array.
*/

#include <stdio.h>
#include <stdlib.h>

int *copyArray(int arr[], int start_index, int n)
{
    int *newArray = (int *)malloc(n * sizeof(int));
    for (int c = start_index, i = 0; i < n; c++, i++)
    {
        newArray[i] = arr[c];
    }

    return newArray;
}

// Function to print the elements in the array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *merge(int *left, int leftSize, int *right, int rightSize)
{
    int *merged = (int *)malloc((leftSize + rightSize) * sizeof(int));

    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < leftSize)
    {
        if (left[i] <= right[j])
        {
            merged[k++] = left[i];
            i++;
        }
        else
        {
            merged[k++] = right[j];
            j++;
        }
    }

    return merged;
}

/*
Function to do merge sort on an array

Args: arr[] -> the original array
      size -> the size of the array

Returns: the sorted array

Time Complexity: O(n log n)
Space Complexity: O(n)
*/
int *mergeSort(int arr[], int size)
{
    printArray(arr, size);
    if (size <= 1)
    {
        int *base = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++)
            base[i] = arr[i];
        return base;
    }

    int half = size / 2;

    int *left = copyArray(arr, 0, half);
    int *right = copyArray(arr, half, size - half);

    int *sortedLeft = mergeSort(left, half);
    int *sortedRight = mergeSort(right, size - half);

    int *result = merge(sortedLeft, half, sortedRight, size - half);

    free(left);
    free(right);
    free(sortedLeft);
    free(sortedRight);

    return result;
}

int main(void)
{
    int original_array[] = {1, 5, 8, 6, 7, 3, 9, 4, 2, 0};
    int n = sizeof(original_array) / sizeof(original_array[0]);

    // Before Sort
    // printArray(original_array, n);

    // Sort the array
    int *sorted_array = mergeSort(original_array, n);

    // After Sort
    printArray(sorted_array, n);
    return 0;
}
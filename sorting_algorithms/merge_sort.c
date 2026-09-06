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

// Function to print the elements in the array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to copy the elements of an array into a new array
// values are copied from start_index to start_index + (n - 1)
int *copyArray(int arr[], int start_index, int n)
{
    // allocate memory space to the new array
    int *newArray = (int *)malloc(n * sizeof(int));
    for (int c = start_index, i = 0; i < n; c++, i++)
    {
        newArray[i] = arr[c];
    }

    return newArray;
}

// Compare the values in the arrays and merge them into a single array
int *merge(int *left, int leftSize, int *right, int rightSize)
{
    // allocate memory space to the new merged array
    int *merged = (int *)malloc((leftSize + rightSize) * sizeof(int));

    int i = 0, j = 0, k = 0;

    // loop through both the arrays at the same time
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
            // the value in the left array was smaller or equal, so add it first
            merged[k++] = left[i++];
        else
            // the value in the right array was smaller, so add it first
            merged[k++] = right[j++];
    }

    // add the remaining values of the left array
    while (i < leftSize)
        merged[k++] = left[i++];

    // add the remaining values of the right array
    while (j < rightSize)
        merged[k++] = right[j++];

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
    printArray(original_array, n);

    // Sort the array
    int *sorted_array = mergeSort(original_array, n);

    // After Sort
    printArray(sorted_array, n);

    free(sorted_array);
    return 0;
}
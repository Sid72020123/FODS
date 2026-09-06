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

// Function to swap the values of two int variables
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

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
    // if (size == 0)
    //     return arr;
    int half_index = size / 2;
    printf("%d\n", half_index);
    printArray(copyArray(arr, 0, half_index), size / 2);
    // mergeSort(copyArray(arr, 0, half_index), size / 2);
    // mergeSort(copyArray(arr, half_index, size), size / 2);
}

int main(void)
{
    int original_array[] = {1, 5, 8, 6, 7, 3, 9, 4, 2, 0};
    int n = sizeof(original_array) / sizeof(original_array[0]);

    // Before Sort
    printArray(original_array, n);

    // Sort the array
    mergeSort(original_array, n);

    // After Sort
    printArray(original_array, n);
    return 0;
}
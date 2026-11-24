/*
*** === Quick Sort === ***

=> Program to perform quick sort on an array.

=> Algorithm:
   -> Choose the last element as the pivot.
   -> Partition the array such that elements <= pivot
      are placed on its left and elements > pivot
      are placed on its right.
   -> The pivot is now in its final sorted position.
   -> Recursively sort the left part.
   -> Recursively sort the right part.
*/

// Lomuto partition scheme, using the last element as pivot

#include <stdio.h>

// Function to print the elements in the array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array using Lomuto partition scheme
// The last element is chosen as the pivot
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];

    // i marks the end of the region containing elements <= pivot
    int i = low - 1;

    // Compare each element with the pivot
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            // Include the current element in the <= pivot region
            i++;

            // Move the smaller element to the left
            swap(&arr[i], &arr[j]);
        }
    }

    // Place the pivot in its final sorted position
    swap(&arr[i + 1], &arr[high]);

    // Return the final position of the pivot
    return i + 1;
}

/*
Function to perform quick sort on an array

Args: arr[] -> the original array
      low   -> the starting index of the array
      high  -> the ending index of the array

Returns: void (the original array is sorted in-place)

Time Complexity:
    Best Case:    O(n log n)
    Average Case: O(n log n)
    Worst Case:   O(n^2)

Space Complexity:
    Average Case: O(log n) - recursion stack
    Worst Case:   O(n)     - recursion stack
*/
void quickSort(int arr[], int low, int high)
{
    // Base case: the part has at most one element
    if (low < high)
    {
        // Partition the array and get the pivot's final position
        int p = partition(arr, low, high);

        // Recursively sort the left part
        quickSort(arr, low, p - 1);

        // Recursively sort the right part
        quickSort(arr, p + 1, high);
    }
}

int main(void)
{
    int original_array[] = {1, 5, 8, 6, 7, 3, 9, 4, 2, 0};
    int n = sizeof(original_array) / sizeof(original_array[0]);

    // Before Sort
    printArray(original_array, n);

    // Sort the array
    quickSort(original_array, 0, n - 1);

    // After Sort
    printArray(original_array, n);

    return 0;
}
/*
*** === Selection Sort === ***

=> Program to perform selection sort on an array.

=> Algorithm:
   1. Loop the array from index (i) 0 to n - 1
   2. Assume the smallest value from i to n - 1 in the array to be at index i
   3. Find the smallest value index in the array from i + 1 to n
   4. Swap the current index value with the new smallest value
*/

#include <stdio.h>

/*
Function to do selection sort on an array

Args: arr[] -> the original array
      size -> the size of the array

Returns: void (sorting is done in-place)

Time Complexity: O(n2)
Space Complexity: O(1)
*/
void selectionSort(int arr[], int size)
{
    // Loop through the original array from 0 to size - 1
    // because in the nested loop, we do i + 1
    for (int i = 0; i < size - 1; i++)
    {
        // assume the minimum value to be the first value in the
        // array from i to size
        int min_index = i;

        // Loop to find the smallest value index from (i + 1) to size
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        // Swap the minimum value with the first value in the
        // array from i to size
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
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

int main(void)
{
    int original_array[] = {1, 5, 8, 6, 7, 3, 9, 4, 2, 0};
    int n = sizeof(original_array) / sizeof(original_array[0]);

    // Before Sort
    printArray(original_array, n);

    // Sort the array
    selectionSort(original_array, n);

    // After Sort
    printArray(original_array, n);
    return 0;
}
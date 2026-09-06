/*
*** === Bubble Sort === ***

=> Program to perform bubble sort on an array.

=> Algorithm:
   -> Loop the original array from 0 to n - 1.
   -> If array[i] > arr[i + 1], swap them.
   -> If nothing was swapped, exit the loop.
   -> Repeat for the rest of the array.
*/

#include <stdio.h>

// Function to swap the values of two int variables
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
Function to do bubble sort on an array

Args: arr[] -> the original array
      size -> the size of the array

Returns: void (sorting is done in-place)

Time Complexity: O(n2)
Space Complexity: O(1)
*/
void bubbleSort(int arr[], int size)
{
    // Loop through the original array from 0 to size - 1
    // because in the nested loop, we use i + 1
    for (int i = 0; i < size - 1; i++)
    {
        int swapped = 0;

        // Loop to compare all the values from 0 to size - (i + 1)
        for (int j = 0; j < size - i - 1; j++)
        {
            // Swap the values
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            return;
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
    bubbleSort(original_array, n);

    // After Sort
    printArray(original_array, n);
    return 0;
}
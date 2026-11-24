/*
*** === Insertion Sort === ***

=> Program to perform insertion sort on an array.

=> Algorithm:
   -> Treat A[0] as the sorted part. For i = 1 … n − 1 take key = A[i].
   -> Move j down from i − 1: while A[j] > key, shift A[j] one place to the right.
   -> Put key into the gap, at index j + 1.
   -> Now A[0..i] is sorted; repeat until i = n − 1.
*/

#include <stdio.h>

/*
Function to do insertion sort on an array

Args: arr[] -> the original array
      size -> the size of the array

Returns: void (sorting is done in-place)

Time Complexity: O(n2)
Space Complexity: O(1)
*/
void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) { // shift larger elements right
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key; // place the key
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
    insertionSort(original_array, n);

    // After Sort
    printArray(original_array, n);
    return 0;
}
#include <stdio.h>


int binarySearch(int *arr, int n, int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    printf("\nSearch Result: %d\n", binarySearch(arr, 5, 6));
    printf("\nSearch Result: %d\n", binarySearch(arr, 5, 3));
    printf("\nSearch Result: %d\n", binarySearch(arr, 5, 1));
    printf("\nSearch Result: %d\n", binarySearch(arr, 5, 5));
}
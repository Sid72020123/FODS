#include <stdio.h>

void main()
{
    int n, i;
    int arr[20];
    int smallest, largest;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    for (i = 0; i < n; i++)
    {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    smallest = arr[0];
    largest = arr[0];

    for (i = 1; i < n; i++)
    {
        if (arr[i] < smallest)
            smallest = arr[i];

        if (arr[i] > largest)
            largest = arr[i];
    }

    printf("\nSmallest element: %d\n", smallest);
    printf("Largest element: %d\n", largest);
}

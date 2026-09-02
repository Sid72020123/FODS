#include <stdio.h>

void main()
{
    int n, i;
    int arr[20];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    for (i = 0; i < n; i++)
    {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("\nAlternate elements from array: ");
    for (i = 0; i < n; i = i + 2)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

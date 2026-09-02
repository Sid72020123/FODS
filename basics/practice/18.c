#include <stdio.h>

void main()
{
    int start, end, i, count = 0, j;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    printf("\nPrime numbers in range [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        count = 0;
        for (j = 1; j <= i; j++)
        {
            if (i % j == 0)
                count++;
        }
        if (count == 2)
        {
            printf("%d ", i);
        }
    }
}
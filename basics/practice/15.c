#include <stdio.h>

void main()
{
    int start, end, i, sum = 0;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    printf("\nEven numbers in series [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nSum of Even numbers = %d\n", sum);

    sum = 0;
    printf("\nOdd numbers in series [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        if (i % 2 != 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nSum of Odd numbers = %d\n", sum);
}
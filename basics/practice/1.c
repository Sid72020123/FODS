#include <stdio.h>

void main()
{
    int i, n, sum = 0;

    printf("Enter a number: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        sum += i;
    }

    printf("\nSum of %d natural numbers [1 to %d] = %d\n", n, n, sum);
}

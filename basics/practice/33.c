#include <stdio.h>

void main()
{
    // Simple problem: Calculate factorial of a number
    int n, i, fact = 1;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Factorial of negative number is not defined!\n");
    }
    else if (n == 0 || n == 1)
    {
        printf("Factorial of %d = 1\n", n);
    }
    else
    {
        for (i = 2; i <= n; i++)
        {
            fact *= i;
        }
        printf("Factorial of %d = %d\n", n, fact);
    }
}

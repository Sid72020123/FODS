#include <stdio.h>

int factorial(int);

void main()
{
    int n, result;

    printf("Enter a number: ");
    scanf("%d", &n);

    result = factorial(n);

    printf("\nFactorial of %d = %d\n", n, result);
}

int factorial(int n)
{
    int i, result = 1;
    for (i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

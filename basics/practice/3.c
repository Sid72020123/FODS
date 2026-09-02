#include <stdio.h>

void print_table(int);

void main()
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    print_table(n);
}

void print_table(int n)
{
    printf("\nMultiplication table of %d:\n", n);
    int i;

    for (i = 1; i <= 10; i++)
    {
        printf("%d x %d = %d\n", n, i, n * i);
    }
}

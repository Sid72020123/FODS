#include <stdio.h>

void main()
{
    int n, i, j;
    printf("Enter the number of terms in series: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("1");
        }
        printf(" ");
    }
}
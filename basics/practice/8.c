#include <stdio.h>

void main()
{
    int n, i, temp;
    printf("Enter the number of terms in series: ");
    scanf("%d", &n);

    if (n >= 1)
        printf("1 ");

    if (n >= 2)
    {
        temp = 5;
        printf("5 ");
    }

    for (i = 3; i <= n; i++)
    {
        temp = (temp * temp) + 1;
        printf("%d ", temp);
    }
}
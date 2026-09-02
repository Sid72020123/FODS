#include <stdio.h>

void main()
{
    int n, i, temp = 1;
    printf("Enter the number of terms in series: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        temp = (i * temp) + 1;
        printf("%d ", temp);
    }
}
#include <stdio.h>

void main()
{
    int i, j, start, end;

    start = 2;
    end = 20;

    for (i = 1; i <= 10; i++)
    {
        for (j = start; j <= end; j++)
        {
            printf("%3d ", j * i);
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

int main()
{
    int N;
    printf("Size of array: ");
    scanf("%d", &N);
    printf("\n");

    int A[N];

    for (int i = 0; i < N; i++)
    {
        printf("Enter numer for index '%d': ", i);
        scanf("%d", &A[i]);
    }

    qsort(A, N, sizeof(int), compare);

    int maxFreq = 1;
    int currentFreq = 1;

    for (int i = 1; i < N; i++)
    {
        if (A[i] == A[i - 1])
        {
            currentFreq++;
        }
        else
        {
            if (currentFreq > maxFreq)
            {
                maxFreq = currentFreq;
            }
            currentFreq = 1;
        }
    }   

    if (currentFreq > maxFreq)
    {
        maxFreq = currentFreq;
    }

    printf("%d\n", N - maxFreq);

    return 0;
}
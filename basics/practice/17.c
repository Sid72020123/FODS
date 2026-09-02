#include <stdio.h>

void main()
{
    int num, count = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num == 0)
        count = 1; // 0 has 1 digit

    while (num != 0)
    {
        num = num / 10; // remove last digit
        count++;        // increment digit count
    }

    printf("Number of digits: %d\n", count);
}

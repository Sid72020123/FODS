#include <stdio.h>

void main()
{
    int num, rev = 0, rem;

    printf("Enter a number: ");
    scanf("%d", &num);

    while (num != 0)
    {
        rem = num % 10;       // get last digit
        rev = rev * 10 + rem; // append it to reverse
        num = num / 10;       // remove last digit
    }

    printf("Reversed number: %d\n", rev);
}

#include <stdio.h>

void main()
{
    int a, b, c, largest;

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    printf("Enter third number: ");
    scanf("%d", &c);

    largest = a;

    if (b > largest)
        largest = b;

    if (c > largest)
        largest = c;

    printf("\nLargest number among %d, %d, %d is: %d\n", a, b, c, largest);
}

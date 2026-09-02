#include <stdio.h>

void main()
{
    int num1, num2;
    char op;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%d", &num2);

    switch (op)
    {
    case '+':
        printf("\nResult: %d + %d = %d\n", num1, num2, num1 + num2);
        break;

    case '-':
        printf("\nResult: %d - %d = %d\n", num1, num2, num1 - num2);
        break;

    case '*':
        printf("\nResult: %d * %d = %d\n", num1, num2, num1 * num2);
        break;

    case '/':
        if (num2 != 0)
            printf("\nResult: %d / %d = %d\n", num1, num2, num1 / num2);
        else
            printf("\nError: Division by zero!\n");
        break;

    default:
        printf("\nInvalid operator!\n");
    }
}

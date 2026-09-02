#include <stdio.h>

void main()
{
    char str[100];
    int i;

    printf("\nEnter a string: ");
    fgets(str, sizeof str, stdin); // Or normal gets(str) in Turbo C

    printf("\nAlphabets: ");
    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z'))
            printf("%c ", str[i]);
    }

    printf("\nDigits: ");
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            printf("%c ", str[i]);
    }

    printf("\nSpecial Symbols: ");
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= '0' && str[i] <= '9')))
            printf("%c ", str[i]);
    }
}

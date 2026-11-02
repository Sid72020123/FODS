/* === HashMap === */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === Global Variables / Structures ===
#define TABLE_SIZE 100

// int HASH_TABLE[100];

// === Hashing Functions  ===

int hash_string(char *string)
{
    int string_length = strlen(string);
    int sum = 0;

    for (int i = 0; i < string_length; i++)
    {
        sum += (int)string[i];
    }

    return sum % TABLE_SIZE;
}

int main(void)
{
    int result = hash_string();
    printf("%d\n", result);
    return 0;
}
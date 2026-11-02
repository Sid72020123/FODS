/* === HashMap === */
// Note: this is implemented to store and retrieve student records

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === Global Variables / Structures ===
#define TABLE_SIZE 100

struct Node
{
    unsigned int roll_no;
    char *name;
    char *email;
    struct Node *next;
};

struct Node *HASH_TABLE[TABLE_SIZE] = {NULL};

// === Hashing Functions  ===

int hash_string(char *string)
{
    int string_length = strlen(string);
    int sum = 0;

    for (int i = 0; i < string_length; i++)
    {
        sum += (int)string[i];
    }
    printf("%d\n", sum);
    return sum % TABLE_SIZE;
}

// === HashMap Functions ===

void insert(char *key, int roll_no, char *email)
{

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->name = (char *)malloc(strlen(key) + 1); // +1 for the null terminator '\0'
    newNode->email = (char *)malloc(strlen(email) + 1);

    newNode->roll_no = roll_no;
    strcpy(newNode->name, key);
    strcpy(newNode->email, email);
    newNode->next = NULL;

    int hashed_index = hash_string(key);
    struct Node *traverse = HASH_TABLE[hashed_index];
    if (traverse == NULL)
    {
        HASH_TABLE[hashed_index] = newNode;
    }
    else
    {
        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newNode;
    }
}

int main(void)
{
    int result = hash_string("ABCDEF");
    printf("%d\n", result);
    insert("A", 10, "abcdef@gmail.com");
    return 0;
}
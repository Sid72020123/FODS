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

struct Node *copyElement(struct Node *node)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->roll_no = node->roll_no;
    newNode->name = (char *)malloc(strlen(node->name) + 1);
    newNode->email = (char *)malloc(strlen(node->email) + 1);

    if (newNode->name == NULL || newNode->email == NULL)
    {
        free(newNode->name);
        free(newNode->email);
        free(newNode);
        return NULL;
    }

    strcpy(newNode->name, node->name);
    strcpy(newNode->email, node->email);
    newNode->next = NULL;
    return newNode;
}

struct Node *get(char *key)
{
    int hashed_index = hash_string(key);

    struct Node *traverse = HASH_TABLE[hashed_index];

    if (traverse == NULL)
    {
        // No slots in this bucket
        return NULL;
    }
    else
    {
        struct Node *result = NULL;
        struct Node *resultStart = NULL;

        while (traverse != NULL)
        {
            if (strcmp(traverse->name, key) == 0)
            {
                struct Node *copy = copyElement(traverse);
                if (copy == NULL)
                {
                    printf("[get] Unable to copy matching node.");
                    return resultStart;
                }

                if (resultStart == NULL)
                {
                    resultStart = copy;
                }
                else
                {
                    result->next = copy;
                }
                result = copy;
            }

            traverse = traverse->next;
        }

        return resultStart;
    }
}

int main(void)
{
    int result = hash_string("ABCDEF");
    printf("%d\n", result);
    insert("A", 10, "abcdef@gmail.com");
    insert("A", 10, "abcdef@gmail.com");
    insert("A", 10, "abcdef@gmail.com");
    insert("A", 10, "abcdef@gmail.com");
    insert("A", 10, "abcdef@gmail.com");
    insert("A", 10, "abcdef@gmail.com");
    return 0;
}
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

int get_int_input(const char *prompt, int max_tries, int *result)
{
    int input;
    char extra;
    char buffer[100];
    int tries = 0;

    while (tries < max_tries)
    {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d %c", &input, &extra) == 1)
        {
            *result = input;
            return 1; // SUCCESS
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

int get_string_input(const char *prompt, int max_tries, char *result)
{
    char buffer[100];
    int tries = 0;

    while (tries < max_tries)
    {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = '\0'; // remove the trailing "\n" from the input received

        if (buffer[0] != '\0')
        {
            sprintf(result, "%s", buffer);
            return 1; // SUCCESS
        }

        printf("Invalid input. Try again.\n");
        tries++;
    }

    printf("Maximum tries exceeded! Please try again...\n");
    return 0; // FAILURE
}

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

int insert(char *key, int roll_no, char *email)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        return 0;
    }
    newNode->name = (char *)malloc(strlen(key) + 1); // +1 for the null terminator '\0'
    newNode->email = (char *)malloc(strlen(email) + 1);

    if (newNode->name == NULL || newNode->email == NULL)
    {
        free(newNode);
        return 0;
    }

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
    return 1;
}

struct Node *copyElement(struct Node *node)
{
    // deep copy the node from the linked list
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
                    printf("\n[get] Unable to copy matching node.\n");
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

// === CRUD Methods ===

void insertRecord()
{
    char *name;
    char *email;
    int roll_no;

    if (!get_string_input("Enter key (name): ", 3, name))
    {
        return;
    }
    if (!get_int_input("Enter roll no.: ", 3, &roll_no))
    {
        return;
    }
    if (!get_string_input("Enter email: ", 3, email))
    {
        return;
    }

    if (!insert(name, roll_no, email))
    {
        printf("\n[*] Error inserting the record.\n");
    }
    else
    {
        printf("\n[*] New record [key = '%s'] inserted.\n", name);
    }
}

int main(void)
{
    int choice = 0;
    do
    {
        printf("\n===== MENU [HashMap] =====\n");
        printf("1. Insert new Record\n");
        printf("2. Search Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Display Hash Table\n");
        printf("6. Exit\n");

        if (get_int_input("Enter your choice: ", 3, &choice))
        {
            switch (choice)
            {
            case 1:
                insertRecord();
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
            }
        }
    } while (choice != 6);

    return 0;
}
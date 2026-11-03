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
        free(newNode->name);
        free(newNode->email);
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

void freeElement(struct Node *node)
{
    if (node == NULL)
    {
        return;
    }

    free(node->name);
    free(node->email);
    free(node);
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

int removeElement(char *key, int index)
{
    // remove / delete the (index)th element from the block of a hash table with the key "key"
    int hashed_index = hash_string(key);

    struct Node *traverse = HASH_TABLE[hashed_index];

    if (traverse == NULL)
    {
        return 0;
    }
    else
    {
        int i = 0;
        struct Node *parent = NULL;
        while (traverse != NULL)
        {
            if (strcmp(traverse->name, key) == 0)
            {
                if (index == i)
                {
                    if (parent == NULL)
                    {
                        HASH_TABLE[hashed_index] = traverse->next;
                    }
                    else
                    {
                        parent->next = traverse->next;
                    }
                    freeElement(traverse);
                    return 1;
                }
                i++;
            }

            parent = traverse;
            traverse = traverse->next;
        }
    }
    return 0;
}

int updateElement(char *key, int index, int new_roll_no, char *new_email)
{
    // update the (index)th element from the block of a hash table with the key "key"
    int hashed_index = hash_string(key);

    struct Node *traverse = HASH_TABLE[hashed_index];

    if (traverse == NULL)
    {
        return 0;
    }
    else
    {
        int i = 0;
        while (traverse != NULL)
        {
            if (strcmp(traverse->name, key) == 0)
            {
                if (index == i)
                {
                    free(traverse->email);
                    traverse->roll_no = new_roll_no;

                    traverse->email = (char *)malloc(strlen(new_email) + 1);
                    strcpy(traverse->email, new_email);

                    return 1;
                }
                i++;
            }
            traverse = traverse->next;
        }
    }
    return 0;
}

// === CRUD Methods ===

void insertRecord()
{
    char name[100];
    char email[100];
    int roll_no;
    printf("\n");

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

void searchRecords()
{
    char key[100];
    printf("\n");

    if (!get_string_input("Enter key (name): ", 3, key))
    {
        return;
    }
    printf("\n[*] Search Results:\n");
    struct Node *results = get(key);

    if (results == NULL)
    {
        printf("\tNo records found with the key '%s'.\n", key);
        return;
    }

    int index = 1;
    while (results != NULL)
    {
        struct Node *temp = results;
        printf("\t[%3d] %s | %d | %s\n", index, results->name, results->roll_no, results->email);
        results = results->next;
        freeElement(temp);
        index += 1;
    }
}

void deleteRecords()
{
    char key[100];
    printf("\n");

    if (!get_string_input("Enter key to delete (name): ", 3, key))
    {
        return;
    }
    printf("\n[*] Search Results:\n");
    struct Node *results = get(key);

    if (results == NULL)
    {
        printf("\tNo records found with the key '%s'.\n", key);
        return;
    }

    int count = 0;
    while (results != NULL)
    {
        count += 1;
        struct Node *temp = results;
        printf("\t[%3d] %s | %d | %s\n", count, results->name, results->roll_no, results->email);
        results = results->next;
        freeElement(temp);
    }
    printf("\t[%3d] (DELETE ALL)\n", count + 1);

    int choice;
    if (get_int_input("\tEnter index of record you want to delete: ", 3, &choice))
    {
        printf("\n");
        if (choice <= 0 || choice > count + 1)
        {
            printf("[*] Invalid choice entered. No records deleted.\n");
            return;
        }
        if (choice == count + 1)
        {
            for (int i = count; i > 0; i--)
            {
                if (removeElement(key, i - 1))
                {
                    printf("[*] Deleted record no. %d with key '%s'.\n", i, key);
                }
                else
                {
                    printf("[X] Couldn't delete record no. %d with key '%s'.\n", i, key);
                }
            }
        }
        else
        {
            if (removeElement(key, choice - 1))
            {
                printf("[*] Deleted record no. %d with key '%s'.\n", choice, key);
            }
            else
            {
                printf("[X] Couldn't delete record no. %d with key '%s'.\n", choice, key);
            }
        }
    }
}

void updateRecords()
{
    char key[100];
    printf("\n");

    if (!get_string_input("Enter key to update (name): ", 3, key))
    {
        return;
    }
    printf("\n[*] Search Results:\n");
    struct Node *results = get(key);

    if (results == NULL)
    {
        printf("\tNo records found with the key '%s'.\n", key);
        return;
    }

    int count = 0;
    while (results != NULL)
    {
        count += 1;
        struct Node *temp = results;
        printf("\t[%3d] %s | %d | %s\n", count, results->name, results->roll_no, results->email);
        results = results->next;
        freeElement(temp);
    }
    printf("\t[%3d] (UPDATE ALL)\n", count + 1);

    int choice;
    if (get_int_input("\tEnter index of record you want to update: ", 3, &choice))
    {
        printf("\n");
        if (choice <= 0 || choice > count + 1)
        {
            printf("[*] Invalid choice entered. No records will be updated.\n");
            return;
        }

        int new_roll_no;
        char new_email[100];

        if (!get_int_input("\tEnter the new roll no.: ", 3, &new_roll_no))
        {
            return;
        }

        if (!get_string_input("\tEnter the new email: ", 3, new_email))
        {
            return;
        }

        if (choice == count + 1)
        {
            for (int i = count; i > 0; i--)
            {
                if (updateElement(key, i - 1, new_roll_no, new_email))
                {
                    printf("[*] Updated record no. %d with key '%s'.\n", i, key);
                }
                else
                {
                    printf("[X] Couldn't update record no. %d with key '%s'.\n", i, key);
                }
            }
        }
        else
        {
            if (updateElement(key, choice - 1, new_roll_no, new_email))
            {
                printf("[*] Updated record no. %d with key '%s'.\n", choice, key);
            }
            else
            {
                printf("[X] Couldn't update record no. %d with key '%s'.\n", choice, key);
            }
        }
    }
}

void displayHashTable()
{
    // prints the entire hash table, including all records
    printf("\n[*] HASH TABLE:");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("\n\t[%3d]:", i);
        struct Node *traverse = HASH_TABLE[i];
        if (traverse == NULL)
        {
            printf(" (No slots)");
        }
        else
        {
            while (traverse != NULL)
            {
                printf(" (%s, %d, %s) |", traverse->name, traverse->roll_no, traverse->email);
                traverse = traverse->next;
            }
        }
    }
    printf("\n");
}

int main(void)
{
    insert("A", 100, "TESTING");
    insert("A", 101, "TESTING");
    insert("A", 102, "TESTING");
    insert("A", 103, "TESTING");
    insert("A", 104, "TESTING");
    insert("A", 105, "TESTING");
    insert("A", 106, "TESTING");
    insert("A", 107, "TESTING");
    insert("ABCDEF", 108, "TESTING");

    int choice = 0;
    do
    {
        printf("\n===== MENU [HashMap] =====\n");
        printf("1. Insert new Record\n");
        printf("2. Search Records\n");
        printf("3. Update Records\n");
        printf("4. Delete Records\n");
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
                searchRecords();
                break;
            case 3:
                updateRecords();
                break;
            case 4:
                deleteRecords();
                break;
            case 5:
                displayHashTable();
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
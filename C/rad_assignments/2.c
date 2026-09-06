/*
Write A program using C programming feature to implement doubly circular linked list dictionary with different manipulation.
Insert, Delete & Update.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char word[30];
    char meaning[50];
    struct Node *prev, *next;
};

struct Node *head = NULL;

/* Insert */
void insert()
{
    struct Node *newNode = malloc(sizeof(struct Node));

    printf("Enter word: ");
    scanf("%s", newNode->word);

    printf("Enter meaning: ");
    scanf(" %[^\n]", newNode->meaning);

    if (head == NULL)
    {
        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else
    {
        struct Node *last = head->prev;

        newNode->next = head;
        newNode->prev = last;
        last->next = newNode;
        head->prev = newNode;
    }

    printf("Word inserted.\n");
}

/* Delete */
void delete()
{
    char word[30];

    if (head == NULL)
    {
        printf("Dictionary is empty.\n");
        return;
    }

    printf("Enter word to delete: ");
    scanf("%s", word);

    struct Node *temp = head;

    do
    {
        if (strcmp(temp->word, word) == 0)
        {
            if (temp->next == temp)
            {
                head = NULL;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                if (temp == head)
                    head = temp->next;
            }

            free(temp);
            printf("Word deleted.\n");
            return;
        }

        temp = temp->next;
    } while (temp != head);

    printf("Word not found.\n");
}

/* Update */
void update()
{
    char word[30];

    if (head == NULL)
    {
        printf("Dictionary is empty.\n");
        return;
    }

    printf("Enter word to update: ");
    scanf("%s", word);

    struct Node *temp = head;

    do
    {
        if (strcmp(temp->word, word) == 0)
        {
            printf("Enter new meaning: ");
            scanf(" %[^\n]", temp->meaning);

            printf("Word updated.\n");
            return;
        }

        temp = temp->next;
    } while (temp != head);

    printf("Word not found.\n");
}

/* Display */
void display()
{
    if (head == NULL)
    {
        printf("Dictionary is empty.\n");
        return;
    }

    struct Node *temp = head;

    printf("\nWord\tMeaning\n");

    do
    {
        printf("%s\t%s\n", temp->word, temp->meaning);
        temp = temp->next;
    } while (temp != head);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- Dictionary ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Update\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert();
            break;
        case 2:
            delete();
            break;
        case 3:
            update();
            break;
        case 4:
            display();
            break;
        case 5:
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
}
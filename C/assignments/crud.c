#include <stdio.h>
#include <string.h>

#define FILE_NAME "file.txt"

void readContent()
{
    FILE *fptr = fopen(FILE_NAME, "r");

    int lineNo = 1;
    char line[200];

    if (fptr == NULL)
    {
        printf("\nFile not found!");
        return;
    }

    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        printf("%d. %s", lineNo, line);
        lineNo++;
    }
}

void writeContent()
{
    FILE *fptr = fopen(FILE_NAME, "w");
    char ch;

    char text[200];

    printf("Enter text (Type END to stop):\n");

    while (1)
    {
        fgets(text, sizeof(text), stdin);

        if (strncmp(text, "END", 3) == 0)
            break;
        fputs(text, fptr);
    }

    fclose(fptr);
}

void updateContent()
{
    FILE *fptr, *temp;
    char line[200], newLine[200];
    int target, lineNo = 1;

    fptr = fopen(FILE_NAME, "r");

    if (fptr == NULL)
    {
        printf("\nFile not found!");
        return;
    }

    printf("Enter line number to update: ");
    scanf("%d", &target);

    if (target <= 0)
    {
        printf("\nZero or negative line number not allowed...\n");
        return;
    }
    getchar();

    temp = fopen("temp.txt", "w");
    printf("Enter new text: ");
    fgets(newLine, sizeof(newLine), stdin);

    int found = 0;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        if (target == lineNo)
        {
            fputs(newLine, temp);
            found = 1;
        }
        else
            fputs(line, temp);
        lineNo++;
    }

    fclose(fptr);
    fclose(temp);

    if (!found)
        printf("\nThe requested line number was not found...\n");

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}

void deleteContent()
{
    FILE *fptr, *temp;
    char line[100];
    int target, lineNo = 1;

    fptr = fopen(FILE_NAME, "r");
    if (fptr == NULL)
    {
        printf("File not found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("Enter line number to delete: ");
    scanf("%d", &target);

    if (target <= 0)
    {
        printf("\nZero or negative line number not allowed...\n");
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        if (lineNo != target)
            fputs(line, temp);
        else
            found = 1;
        lineNo++;
    }

    fclose(fptr);
    fclose(temp);

    if (!found)
        printf("\nThe requested line number was not found...\n");

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}

void main()
{
    int choice;
    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Create/Write File\n");
        printf("2. Read File\n");
        printf("3. Update a Line\n");
        printf("4. Delete a Line\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Remove newline

        switch (choice)
        {
        case 1:
            writeContent();
            break;
        case 2:
            readContent();
            break;
        case 3:
            updateContent();
            break;
        case 4:
            deleteContent();
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 5);
}

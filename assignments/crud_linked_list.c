#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "file.txt"
#define LINE_LIMIT 200

struct content
{
    char line[LINE_LIMIT];
    struct content *next;
};

struct content *first = NULL;

void clearInputBuffer()
{
    int ch;
    while (1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF)
            break;
    }
}

void freeLinkedList()
{
    struct content *traverse = NULL, *temp = NULL;

    if (first == NULL)
    {
        // printf("\n[freeLinkedList] List is empty!\n");
        return;
    }

    traverse = first;

    while (traverse != NULL)
    {
        temp = traverse;
        traverse = traverse->next;
        free(temp);
    }

    first = NULL;
}

void loadFileIntoLinkedList()
{
    FILE *fptr = fopen(FILE_NAME, "r");

    char line[LINE_LIMIT];
    struct content *traverse = NULL;

    if (fptr == NULL)
    {
        printf("\n[loadFileIntoLinkedList] File not found!\n");
        return;
    }

    freeLinkedList();

    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        struct content *temp = (struct content *)malloc(sizeof(struct content));
        strcpy(temp->line, line);
        temp->next = NULL;

        if (first == NULL)
        {
            first = temp;
            traverse = first;
        }
        else
        {
            while (traverse->next != NULL)
            {
                traverse = traverse->next;
            }
            traverse->next = temp;
        }
    }

    fclose(fptr);
}

int printLinkedListContents()
{
    struct content *traverse = NULL;

    if (first == NULL)
    {
        printf("\n[printLinkedListContents] File is empty!\n");
        return 1;
    }

    traverse = first;
    int lineNo = 1;
    printf("--- File Contents ---\n");
    while (traverse != NULL)
    {
        printf("%d. %s", lineNo, traverse->line);
        lineNo++;
        traverse = traverse->next;
    }
    return 0;
}

int writeLinkedListToFile()
{
    if (first == NULL)
    {
        printf("\n[writeLinkedListToFile] File is empty!\n");
        return 1;
    }

    FILE *fptr = fopen(FILE_NAME, "w");

    if (fptr == NULL)
    {
        printf("\n[writeLinkedListToFile] File not found!");
        return 1;
    }

    struct content *traverse = NULL;

    traverse = first;
    int lineNo = 1;

    while (traverse != NULL)
    {
        printf("[writeLinkedListToFile] Writing line no. %d ...\n", lineNo);
        fputs(traverse->line, fptr);

        lineNo++;
        traverse = traverse->next;
    }

    fclose(fptr);
    return 0;
}

void addLine(char *line)
{
    struct content *newContent = (struct content *)malloc(sizeof(struct content));

    strcpy(newContent->line, line);
    newContent->next = NULL;

    if (first == NULL)
        first = newContent;
    else
    {
        struct content *traverse = first;

        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newContent;
    }
}

int deleteLine(int lineNo)
{
    if (first == NULL)
    {
        printf("\n[deleteLine] File is empty!\n");
        return 1;
    }

    if (lineNo <= 0)
    {
        printf("\n[deleteLine] Zero or Negative line numbers not allowed...\n");
        return 1;
    }

    struct content *traverse = first;
    struct content *previous = NULL;

    int currentLine = 1;
    int found = 0;

    while (traverse->next != NULL && currentLine < lineNo)
    {
        // printf("%d\n", currentLine);
        // if (currentLine == lineNo)
        // {
        //     found = 1;
        //     target = traverse;
        //     traverse = NULL;
        // }
        // traverse = traverse->next;
        // currentLine++;
        previous = traverse;
        traverse = traverse->next;
        currentLine++;
    }

    if (traverse == NULL || currentLine != lineNo)
    {
        printf("\n[deleteLine] Line no. %d was not found!\n", lineNo);
        return 1;
    }

    if (previous == NULL)
    {
        first = traverse->next;
    }
    else
    {
        previous->next = traverse->next;
    }

    free(traverse);
    return 0;
}

int editLine(int lineNo, char *line)
{
    struct content *traverse = NULL;

    if (first == NULL)
    {
        printf("\n[editLine] File is empty!\n");
        return 1;
    }

    if (lineNo <= 0)
    {
        printf("\n[editLine] Zero or Negative line numbers not allowed...\n");
        return 1;
    }

    traverse = first;
    int currentLine = 1;
    int found = 0;

    while (traverse != NULL)
    {
        if (currentLine == lineNo)
        {
            strcpy(traverse->line, line);
            found = 1;
            traverse = NULL;
        }
        else
        {
            traverse = traverse->next;
        }
        currentLine++;
    }

    if (!found)
    {
        printf("\n[editLine] Line no. %d was not found!\n", lineNo);
        return 1;
    }
    return 0;
}

void readContent()
{
    loadFileIntoLinkedList();
    printLinkedListContents();
}

void writeContent()
{
    loadFileIntoLinkedList();
    char text[LINE_LIMIT];

    printf("Enter text (Type END to stop):\n");

    while (1)
    {
        fgets(text, sizeof(text), stdin);

        if (strcmp(text, "END\n") == 0 || strcmp(text, "END") == 0)
            break;
        addLine(text);
    }
    writeLinkedListToFile();
}

void updateContent()
{
    loadFileIntoLinkedList();

    char newLine[LINE_LIMIT];
    int target;

    printf("Enter line number to update: ");
    if (!scanf("%d", &target))
    {
        printf("\nInvalid input!\n");
        return;
    }

    if (target <= 0)
    {
        printf("\nZero or Negative line numbers not allowed!\n");
        return;
    }

    clearInputBuffer();

    printf("Enter new text: ");
    fgets(newLine, sizeof(newLine), stdin);

    if (!editLine(target, newLine))
        writeLinkedListToFile();
}

void deleteContent()
{
    loadFileIntoLinkedList();
    int target;

    printf("Enter line number to delete: ");

    if (!scanf("%d", &target))
    {
        printf("\nInvalid input!\n");
        clearInputBuffer();
        return;
    }

    if (!deleteLine(target))
        writeLinkedListToFile();
}

int validateNumberInput()
{
    int ch;

    ch = getchar();

    if (ch == '\n' || ch == EOF)
        return 1;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // Clear remaining input
    }

    return 0;
}

void main()
{
    // loadFileIntoLinkedList();
    // printLinkedListContents();
    // int lineNo;
    // char line[LINE_LIMIT];
    // scanf("Enter Line: %d", &lineNo);
    // scanf("Enter text: ");
    // fgets(line, sizeof(line), stdin);
    // editLine(lineNo, line);
    // // writeLinkedListToFile();
    // // loadFileIntoLinkedList();
    // printLinkedListContents();

    int choice = 0;
    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Create/Write File\n");
        printf("2. Read File\n");
        printf("3. Update a Line\n");
        printf("4. Delete a Line\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Option Entered! Please enter numbers only...\n");
            clearInputBuffer();
        }
        else if (!validateNumberInput())
        {
            printf("\nInvalid Option Entered! Please enter numbers only...\n");
        }
        else
        {
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
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
            }
        }
    } while (choice != 5);
    freeLinkedList();
}

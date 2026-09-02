/*
#include <stdlib.h>
#include <stdio.h>

struct queue
{
    int value;
    struct queue *next;
};

void enqueue(int, struct queue **, struct queue **);
void printQueue(struct queue *);

void main()
{
    struct queue *first = NULL, *last = NULL;
    printQueue(first);
    enqueue(10, &first, &last);
    enqueue(20, &first, &last);
    printQueue(first);
    enqueue(30, &first, &last);
    enqueue(40, &first, &last);
    enqueue(50, &first, &last);
    printQueue(first);
}

void enqueue(int value, struct queue **first, struct queue **last)
{
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));

    temp->value = value;
    temp->next = NULL;

    if (*last == NULL)
    {
        *last = temp;
        if (*first == NULL)
            *first = temp;
    }
    else
    {
        (*last)->next = temp;
        *last = temp;
    }
}

void printQueue(struct queue *first)
{
    struct queue *temp = first;
    unsigned int index = 0;

    printf("== *** [Queue] *** ==\n");
    if (temp == NULL)
    {
        printf("| [*] Queue is empty!\n\n\n");
        return;
    }

    while (temp != NULL)
    {
        printf("| [%d] %d\n", index, temp->value);
        temp = temp->next;
        index++;
    }
    printf("=====================\n\n");
}
*/

/*
#include <stdio.h>

int clear_input_buffer(char type)
{
    int ch;
    while (1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF)
            return 0;
        switch (type)
        {
        case 'i':
            // for int...
            if (ch < '0' || ch > '9')
                return 0;
            break;
        }
    }
}

int get_int_input(char *prompt)
{
    while (1)
    {
        int input;
        printf("%s", prompt);
        if (!scanf("%d", &input) && !clear_input_buffer('i'))
            continue;
        return input;
    }
}

int main()
{
    int a = get_int_input("Enter a number: ");
    int b = get_int_input("Enter another number: ");
    printf("\n\nRECEIVED A: %d\n\n", a);
    printf("\n\nRECEIVED B: %d\n\n", b);
    return 0;
}
*/

#include <stdio.h>

void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int get_int_input(const char *prompt)
{
    int input;
    char extra;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%d%c", &input, &extra) == 2)
        {
            if (extra == '\n')
                return input;
        }

        clear_input_buffer();
    }
}

int main(void)
{
    int a = get_int_input("Enter a number: ");
    int b = get_int_input("Enter another number: ");

    printf("\nRECEIVED A: %d\n", a);
    printf("RECEIVED B: %d\n", b);

    return 0;
}
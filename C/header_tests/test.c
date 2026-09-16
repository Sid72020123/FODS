#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

typedef struct Node
{
    int rollNo;
    char name[100];
} student;

student *createStudent(int rollNo, char name[])
{
    student *newStudent = (student *)malloc(sizeof(student));
    if (newStudent == NULL)
        return NULL;
    newStudent->rollNo = rollNo;
    strcpy(newStudent->name, name);

    return newStudent;
}

int main(void)
{
    struct Queue *MAIN = createNewQueue("MAIN");
    struct Queue *TEMP = createNewQueue("TEMP");

    printf("Queue Empty: %d\n", isQueueEmpty(MAIN));
    printf("Queue Size: %d\n", getSizeQueue(MAIN));

    enqueue(createStudent(1, "Siddhesh"), MAIN);

    printf("Queue Empty: %d\n", isQueueEmpty(MAIN));
    printf("Queue Size: %d\n", getSizeQueue(MAIN));

    printf("[TEMP] Queue Empty: %d\n", isQueueEmpty(TEMP));
    printf("[TEMP] Queue Size: %d\n", getSizeQueue(TEMP));
    _debugPrintQueueContents(MAIN);
    _debugPrintQueueContents(TEMP);
    return 0;
}
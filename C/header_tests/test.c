#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"
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
    // struct Queue *MAIN = createNewQueue("MAIN");
    // struct Queue *TEMP = createNewQueue("TEMP");

    // _debugPrintQueueContents(MAIN);
    // _debugPrintQueueContents(TEMP);

    // enqueue(createStudent(1, "Siddhesh"), MAIN);
    // enqueue(createStudent(2, "Person A"), MAIN);
    // enqueue(createStudent(3, "Person B"), MAIN);

    // _debugPrintQueueContents(MAIN);
    // enqueue(createStudent(0, "Dummy Person"), TEMP);
    // student *traverse = NULL;

    // while (!isQueueEmpty(MAIN))
    // {
    //     dequeue(&traverse, MAIN);
    //     printf("[%d] ==> [%s]\n", traverse->rollNo, traverse->name);
    //     free(traverse);
    // }

    // _debugPrintQueueContents(TEMP);
    // dequeue(&traverse, TEMP);
    // _debugPrintQueueContents(TEMP);
    // printf("[%d] ==> [%s]\n", traverse->rollNo, traverse->name);
    // free(traverse);

    // (MAIN);
    // free(TEMP);

    struct Stack *MAIN = createNewStack("MAIN");
    struct Stack *TEMP = createNewStack("TEMP");

    _debugPrintStackContents(MAIN);
    _debugPrintStackContents(TEMP);

    push(createStudent(1, "Siddhesh"), MAIN);
    push(createStudent(2, "Person A"), MAIN);
    push(createStudent(3, "Person B"), MAIN);

    _debugPrintStackContents(MAIN);
    push(createStudent(0, "Dummy Person"), TEMP);
    student *traverse = NULL;

    while (!isStackEmpty(MAIN))
    {
        pop(&traverse, MAIN);
        printf("[%d] ==> [%s]\n", traverse->rollNo, traverse->name);
        free(traverse);
    }

    _debugPrintStackContents(TEMP);
    pop(&traverse, TEMP);
    _debugPrintStackContents(TEMP);
    printf("[%d] ==> [%s]\n", traverse->rollNo, traverse->name);
    free(traverse);

    free(MAIN);
    free(TEMP);
    return 0;
}
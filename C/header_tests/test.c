#include <stdio.h>
#include "queue.h"

typedef struct Node
{

} Student;

int main(void)
{
    struct Queue *MAIN = createNewQueue();
    printf("%d\n", isQueueEmpty(MAIN));
    printf("%d\n", getSizeQueue(MAIN));

    return 0;
}
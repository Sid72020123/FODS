#include <stdio.h>
#include "queue.h"

int main(void)
{
    int a;
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("%i\n", isEmpty());
    emptyQueue();
    printf("%i\n", isEmpty());
    printf("%i\n", dequeue(&a));
    printf("%i\n", a);

    return 0;
}
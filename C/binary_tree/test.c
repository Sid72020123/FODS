// #include <stdio.h>
// #include "queue.h"

// int main(int argc, char *argv[])
// {
//     printf("%i\n", argc);
//     printf("%s\n", argv[0]);
//     // int a;
//     // enqueue(10);
//     // enqueue(20);
//     // enqueue(30);
//     // printf("%i\n", isQueueEmpty());
//     // emptyQueue();
//     // printf("%i\n", isQueueEmpty());
//     // printf("%i\n", dequeue(&a));
//     // printf("%i\n", a);

//     return 0;
// }

#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
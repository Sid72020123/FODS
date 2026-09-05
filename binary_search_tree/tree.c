#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

// === Global Variables / Structures ===
struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;
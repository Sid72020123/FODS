/*
Problem Statement: A Vegetable and Fruit Mall wants to organize its vegetables and fruit products in a combination of purchase pattern of customers.
Solve the problem by suggesting appropriate data structures. Design necessary data structures.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int id;
    char name[30];
    char category[15];
    float price;
    struct Node *left, *right;
} Node;

Node *createNode(int id, char name[], char category[], float price)
{
    Node *n = malloc(sizeof(Node));

    n->id = id;
    strcpy(n->name, name);
    strcpy(n->category, category);
    n->price = price;
    n->left = n->right = NULL;

    return n;
}

void add(Node *root, Node *newNode)
{
    Node *q[100];
    int front = 0, rear = 0;

    q[rear++] = root;

    while (front < rear)
    {
        Node *temp = q[front++];

        if (temp->left == NULL)
        {
            temp->left = newNode;
            return;
        }

        if (temp->right == NULL)
        {
            temp->right = newNode;
            return;
        }

        q[rear++] = temp->left;
        q[rear++] = temp->right;
    }
}

void display(Node *root)
{
    Node *q[100];
    int front = 0, rear = 0;

    q[rear++] = root;

    while (front < rear)
    {
        Node *temp = q[front++];

        printf("%d\t%s\t%s\t%.2f\n",
               temp->id, temp->name,
               temp->category, temp->price);

        if (temp->left)
            q[rear++] = temp->left;

        if (temp->right)
            q[rear++] = temp->right;
    }
}

int main()
{
    Node *root = createNode(103, "Apple", "Fruit", 120);

    add(root, createNode(101, "Potato", "Vegetable", 40));
    add(root, createNode(105, "Banana", "Fruit", 60));
    add(root, createNode(102, "Tomato", "Vegetable", 50));
    add(root, createNode(104, "Orange", "Fruit", 90));

    printf("ID\tName\tCategory\tPrice\n");
    display(root);

    return 0;
}

/*
#include <stdio.h>
#include <string.h>

struct Package
{
    int packageID;
    char destination[30];
    float distance;
    int deadline;
    float shippingCost;
};

void sortEmergency(struct Package p[], int n)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].deadline > p[j + 1].deadline)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sortFuel(struct Package p[], int n)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].distance > p[j + 1].distance)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sortRevenue(struct Package p[], int n)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].shippingCost < p[j + 1].shippingCost)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void display(struct Package p[], int n)
{
    int i;

    printf("ID Destination Distance Deadline Cost\n");
    printf("---------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d %-16s %.1f km %d hrs $%.2f\n",
               p[i].packageID,
               p[i].destination,
               p[i].distance,
               p[i].deadline,
               p[i].shippingCost);
    }
}

int main()
{
    struct Package packages[5] = {
        {101, "Downtown", 15.5, 4, 25.00},
        {102, "North Suburb", 42.0, 12, 85.50},
        {103, "Airport District", 8.2, 2, 15.00},
        {104, "West Valley", 23.1, 6, 45.00},
        {105, "East Pier", 19.8, 3, 60.00}};

    int choice;

    printf("1. Emergency Mode\n");
    printf("2. Fuel-Saving Mode\n");
    printf("3. Revenue Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        sortEmergency(packages, 5);

        printf("\n--- EMERGENCY DELIVERY SCHEDULE ---\n");
    }
    else if (choice == 2)
    {
        sortFuel(packages, 5);

        printf("\n--- FUEL-SAVING DELIVERY SCHEDULE ---\n");
    }
    else if (choice == 3)
    {
        sortRevenue(packages, 5);

        printf("\n--- REVENUE DELIVERY SCHEDULE ---\n");
    }
    else
    {
        printf("Invalid choice.\n");
        return 0;
    }

    display(packages, 5);

    return 0;
}
*/

#include <stdio.h>

struct Package
{
    int packageID;
    char destination[30];
    float distance;
    int deadline;
    float shippingCost;
};

void bubbleSort(struct Package p[], int n, int mode)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (mode == 1 && p[j].deadline > p[j + 1].deadline)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

            else if (mode == 2 && p[j].distance > p[j + 1].distance)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

            else if (mode == 3 && p[j].shippingCost < p[j + 1].shippingCost)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

/* Display packages */
void display(struct Package p[], int n)
{
    int i;

    printf("ID Destination       Distance Deadline Cost\n");
    printf("---------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d %-16s %.1f km   %d hrs   $%.2f\n",
               p[i].packageID,
               p[i].destination,
               p[i].distance,
               p[i].deadline,
               p[i].shippingCost);
    }
}

int main()
{
    struct Package packages[5] =
        {
            {101, "Downtown", 15.5, 4, 25.00},
            {102, "North Suburb", 42.0, 12, 85.50},
            {103, "Airport District", 8.2, 2, 15.00},
            {104, "West Valley", 23.1, 6, 45.00},
            {105, "East Pier", 19.8, 3, 60.00}};

    int choice;

    printf("1. Emergency Mode\n");
    printf("2. Fuel-Saving Mode\n");
    printf("3. Revenue Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        bubbleSort(packages, 5, 1);
        printf("\n--- EMERGENCY DELIVERY SCHEDULE ---\n");
    }
    else if (choice == 2)
    {
        bubbleSort(packages, 5, 2);
        printf("\n--- FUEL-SAVING DELIVERY SCHEDULE ---\n");
    }
    else if (choice == 3)
    {
        bubbleSort(packages, 5, 3);
        printf("\n--- REVENUE DELIVERY SCHEDULE ---\n");
    }
    else
    {
        printf("Invalid choice!\n");
        return 0;
    }

    display(packages, 5);

    return 0;
}
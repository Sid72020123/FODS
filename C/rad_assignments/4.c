#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50
#define CATEGORY_SIZE 30

// Structure for storing product details
struct Product
{
    int id;
    char name[NAME_SIZE];
    char category[CATEGORY_SIZE];
    float price;
    float rating;
    int stock;
};

// Function declarations / prototypes
void addProducts(struct Product products[], int n);
void displayProduct(struct Product p);
void displayAllProducts(struct Product products[], int n);

int linearSearch(struct Product products[], int n, int id);

void bubbleSortByPrice(struct Product products[], int n);
void bubbleSortByID(struct Product products[], int n);

int binarySearch(struct Product products[], int n, int id);

void cheapestProduct(struct Product products[], int n);
void expensiveProduct(struct Product products[], int n);
void highestRatedProduct(struct Product products[], int n);

void topFiveProducts(struct Product products[], int n);
void priceRangeSearch(struct Product products[], int n);

void copyProducts(struct Product source[], struct Product destination[], int n);

int main()
{
    struct Product *products;
    struct Product *idSortedProducts;

    int n = 10;
    int choice;
    int id;
    int position;

    // printf("Enter number of products: ");
    // scanf("%d", &n);

    // if (n <= 0)
    // {
    //     printf("Number of products must be greater than 0.\n");
    //     return 0;
    // }

    products = (struct Product *)malloc(n * sizeof(struct Product));
    idSortedProducts = (struct Product *)malloc(n * sizeof(struct Product));

    // Add products
    addProducts(products, n);

    do
    {
        printf("\n========================================\n");
        printf("E-COMMERCE PRODUCT SYSTEM\n");
        printf("========================================\n");
        printf("1. Display all products\n");
        printf("2. Linear Search by Product ID\n");
        printf("3. Sort products by Price\n");
        printf("4. Binary Search by Product ID\n");
        printf("5. Find cheapest product\n");
        printf("6. Find most expensive product\n");
        printf("7. Find highest-rated product\n");
        printf("8. Display top 5 highest-priced products\n");
        printf("9. Search products within price range\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayAllProducts(products, n);
            break;

        case 2:
            printf("\nEnter Product ID to search: ");
            scanf("%d", &id);

            position = linearSearch(products, n, id);

            if (position != -1)
            {
                printf("\nProduct Found:\n");
                displayProduct(products[position]);
            }
            else
            {
                printf("\nProduct not found.\n");
            }
            break;

        case 3:
            bubbleSortByPrice(products, n);

            printf("\nProducts sorted by Price:\n");
            displayAllProducts(products, n);
            break;

        case 4:
            copyProducts(products, idSortedProducts, n);
            bubbleSortByID(idSortedProducts, n);

            printf("\nEnter Product ID to search: ");
            scanf("%d", &id);

            position = binarySearch(idSortedProducts, n, id);

            if (position != -1)
            {
                printf("\nProduct Found:\n");
                displayProduct(idSortedProducts[position]);
            }
            else
            {
                printf("\nProduct not found.\n");
            }
            break;

        case 5:
            cheapestProduct(products, n);
            break;

        case 6:
            expensiveProduct(products, n);
            break;

        case 7:
            highestRatedProduct(products, n);
            break;

        case 8:
            topFiveProducts(products, n);
            break;

        case 9:
            priceRangeSearch(products, n);
            break;

        case 10:
            printf("\nExiting program...\n");
            break;

        default:
            printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 10);

    free(products);
    free(idSortedProducts);

    return 0;
}

// Function to add product records
void addProducts(struct Product products[], int n)
{
    /*
    int i;

    printf("\nEnter Product Details\n");

    for (i = 0; i < n; i++)
    {
        printf("\nProduct %d\n", i + 1);

        printf("Product ID: ");
        scanf("%d", &products[i].id);

        printf("Product Name: ");
        scanf(" %[^\n]", products[i].name);

        printf("Category: ");
        scanf(" %[^\n]", products[i].category);

        printf("Price: ");
        scanf("%f", &products[i].price);

        printf("Rating: ");
        scanf("%f", &products[i].rating);

        printf("Stock Quantity: ");
        scanf("%d", &products[i].stock);
    }
    */

    products[0] = (struct Product){105, "Laptop", "Electronics", 75000, 4.5, 10};
    products[1] = (struct Product){102, "Smartphone", "Electronics", 45000, 4.7, 20};
    products[2] = (struct Product){108, "Headphones", "Electronics", 5000, 4.2, 50};
    products[3] = (struct Product){101, "Keyboard", "Accessories", 2500, 4.0, 30};
    products[4] = (struct Product){110, "Monitor", "Electronics", 18000, 4.6, 15};
    products[5] = (struct Product){103, "Mouse", "Accessories", 1500, 4.3, 40};
    products[6] = (struct Product){107, "Tablet", "Electronics", 30000, 4.4, 12};
    products[7] = (struct Product){104, "Smartwatch", "Wearables", 12000, 4.1, 25};
    products[8] = (struct Product){109, "Camera", "Electronics", 55000, 4.8, 8};
    products[9] = (struct Product){106, "Speaker", "Electronics", 8000, 4.6, 35};
}

// Function to display one product
void displayProduct(struct Product p)
{
    printf("\nProduct ID      : %d", p.id);
    printf("\nProduct Name    : %s", p.name);
    printf("\nCategory        : %s", p.category);
    printf("\nPrice           : %.2f", p.price);
    printf("\nRating          : %.1f", p.rating);
    printf("\nStock Quantity  : %d\n", p.stock);
}

// Function to display all products
void displayAllProducts(struct Product products[], int n)
{
    int i;

    printf("\n========== ALL PRODUCTS ==========\n");

    for (i = 0; i < n; i++)
    {
        printf("\nProduct %d", i + 1);
        displayProduct(products[i]);
    }
}

// Linear Search by Product ID
int linearSearch(struct Product products[], int n, int id)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (products[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// Bubble Sort by Price (ascending order)
void bubbleSortByPrice(struct Product products[], int n)
{
    int i;
    int j;
    struct Product temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (products[j].price > products[j + 1].price)
            {
                temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

// Bubble Sort by Product ID (ascending order)
void bubbleSortByID(struct Product products[], int n)
{
    int i;
    int j;
    struct Product temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (products[j].id > products[j + 1].id)
            {
                temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

// Binary Search by Product ID
int binarySearch(struct Product products[], int n, int id)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (products[mid].id == id)
        {
            return mid;
        }
        else if (products[mid].id < id)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

// Find cheapest product
void cheapestProduct(struct Product products[], int n)
{
    int i;
    int minIndex = 0;

    for (i = 1; i < n; i++)
    {
        if (products[i].price < products[minIndex].price)
        {
            minIndex = i;
        }
    }

    printf("\n========== CHEAPEST PRODUCT ==========\n");
    displayProduct(products[minIndex]);
}

// Find most expensive product
void expensiveProduct(struct Product products[], int n)
{
    int i;
    int maxIndex = 0;

    for (i = 1; i < n; i++)
    {
        if (products[i].price > products[maxIndex].price)
        {
            maxIndex = i;
        }
    }

    printf("\n========== MOST EXPENSIVE PRODUCT ==========\n");
    displayProduct(products[maxIndex]);
}

// Find highest-rated product
void highestRatedProduct(struct Product products[], int n)
{
    int i;
    int maxIndex = 0;

    for (i = 1; i < n; i++)
    {
        if (products[i].rating > products[maxIndex].rating)
        {
            maxIndex = i;
        }
    }

    printf("\n========== HIGHEST-RATED PRODUCT ==========\n");
    displayProduct(products[maxIndex]);
}

// Display top 5 highest-priced products
void topFiveProducts(struct Product products[], int n)
{
    int i;
    int start;

    // Sort by price first
    bubbleSortByPrice(products, n);

    printf("\n========== TOP 5 HIGHEST-PRICED PRODUCTS ==========\n");

    if (n < 5)
    {
        start = n - 1;

        for (i = start; i >= 0; i--)
        {
            displayProduct(products[i]);
        }
    }
    else
    {
        start = n - 1;

        for (i = start; i >= n - 5; i--)
        {
            displayProduct(products[i]);
        }
    }
}

// Search products within a price range
void priceRangeSearch(struct Product products[], int n)
{
    float minPrice;
    float maxPrice;
    int i;
    int found = 0;

    printf("\nEnter minimum price: ");
    scanf("%f", &minPrice);

    printf("Enter maximum price: ");
    scanf("%f", &maxPrice);

    printf("\n========== PRODUCTS IN PRICE RANGE ==========\n");

    for (i = 0; i < n; i++)
    {
        if (products[i].price >= minPrice &&
            products[i].price <= maxPrice)
        {
            displayProduct(products[i]);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No products found in this price range.\n");
    }
}

// Copy one product array into another
void copyProducts(struct Product source[],
                  struct Product destination[],
                  int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        destination[i] = source[i];
    }
}

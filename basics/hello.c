/*
#include <stdio.h>

int main()
{
    printf("Hello from VS Code on Ubuntu!\n");
    return 0;
}
*/

/*
#include <stdio.h>

void main()
{
    int a, b, sum;
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("Enter another number: ");
    scanf("%d", &b);

    sum = a + b;
    printf("The addition result is: %d\n", sum);
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
    printf("%f\n", pow(2, 1.5));
    }
*/

/*
#include <stdio.h>

void main()
{
    int a, b, c, d, e, sum;
    float avg;
    printf("Enter any 5 numbers separated by a space: ");
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    sum = a + b + c + d + e;
    avg = sum / 5.0;
    printf("The sum is: %d\nThe average is: %f\n", sum, avg);
}
*/

/*
// Temperature Converter
#include <stdio.h>

main()
{
    int temperature_F;
    float temperature_C, temperature_K;
    printf("Enter the temperature in F: ");
    scanf("%d", &temperature_F);

    temperature_C = (5.0 / 9.0) * (temperature_F - 32.0);
    temperature_K = temperature_C + 273.15;
    printf("\nConverted Results:\n------------------\nTemperature in C: %f\nTemperature in K: %f\n", temperature_C, temperature_K);
}
*/

/*
#include <stdio.h>

void main()
{
    int length, breadth;
    float perimeter, area;
    printf("Enter the length of a rectangle: ");
    scanf("%d", &length);
    printf("Enter the breadth of a rectangle: ");
    scanf("%d", &breadth);

    perimeter = (length + breadth) / 2.0;
    area = length * breadth;
    printf("\nResults:\n--------\nPerimeter: %f\nArea: %f\n", perimeter, area);
}
*/

/*
#include <stdio.h>

void main()
{
    char name[20];
    printf("Enter your name: ");
    // scanf("%s", name); --> Only the first word is accepted
    // gets(name); --> Unsafe!
    fgets(name, sizeof(name), stdin);

    printf("Hello, %s!\n", name);
    puts(name);
}
*/

/*
#include <stdio.h>

struct student
{
    char name[20];
    int roll_no;
    float marks;
} s;
struct student s2;

void main()
{
    // s.name[] = "Srushti"; // Doesn't work...
    s.roll_no = 32;
    s.marks = 95.5;

    printf("Name: %s\n", s.name);
    printf("Roll No.: %d\n", s2.);
    printf("Marks: %f\n", s.marks);
}
*/

/*

// Example 6:
#include <stdio.h>

void main()
{
    int a, b, c;
    printf("Enter 3 numbers separated by a space: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a > b && a > c)
        printf("%d is the largest number\n", a);
    else if (b > a && b > c)
        printf("%d is the largest number\n", b);
    else if (c > a && c > b)
        printf("%d is the largest number\n", c);
    else if (a == b == c)
        printf("All 3 numbers are equal\n");
}

// Example 7:
#include <stdio.h>

void main()
{
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);

    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        printf("Given character is an alphabet\n");
    else if (ch >= '0' && ch <= '9')
        printf("Given character is a number\n");
    else
        printf("Given character is a special character\n");
}

// Example 8:
#include <stdio.h>

void main()
{
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);

    if ((year % 4 == 0) || (year % 400 == 0))
        printf("%d is a leap year\n", year);
    else
        printf("%d is not a leap year\n", year);
}
    else
        printf("Given character is a special character\n");
}

// Example 8:
#include <stdio.h>

void main()
{
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);

    if ((year % 4 == 0) || (year % 400 == 0))
        printf("%d is a leap year\n", year);
    else
        printf("%d is not a leap year\n", year);
}
*/

/* ----- Prime number checking ----- */

// for loop:
/*
#include <stdio.h>

void main()
{
    int num, i, count = 0;
    printf("Enter a number: ");
    scanf("%d", &num);

    for (i = 1; i <= num; i++)
    {
        if (num % i == 0)
            count++;
    }

    if (count == 2)
        printf("\nThe entered number (%d) is a prime number\n", num);
    else
        printf("\nThe entered number (%d) is not a prime number\n", num);
}
*/

/*
// while loop:
#include <stdio.h>

void main()
{
    int num, i, count = 0;
    printf("Enter a number: ");
    scanf("%d", &num);

    i = 1;
    while (i <= num)
    {
        if (num % i == 0)
            count++;
        i++;
    }

    if (count == 2)
        printf("\nThe entered number (%d) is a prime number\n", num);
    else
        printf("\nThe entered number (%d) is not a prime number\n", num);
}
*/

/*
// do-while loop:
#include <stdio.h>

void main()
{
    int num, i, count = 0;
    printf("Enter a number: ");
    scanf("%d", &num);

    i = 1;
    do
    {
        if (num % i == 0)
            count++;
        i++;
    } while (i <= num);

    if (count == 2)
        printf("\nThe entered number (%d) is a prime number\n", num);
    else
        printf("\nThe entered number (%d) is not a prime number\n", num);
}
*/

/*
#include <stdio.h>

void main()
{
    int a, b;
    float c;
    for (int i = 0; i <= 4; i++)
    {
        a = 10;
        b = 5;
        c = a + b;

        printf("Size of a = %d\nSize of b = %d\nSize of c = %d\n\nResult = %f\n\nAddress of a = %u\nAddress of b = %u\nAddress of c = %u\n", sizeof(a), sizeof(b), sizeof(c), c, &a, &b, &c);
        printf("\n\n");
    }
}
*/

// Pointers

#include <stdio.h>

void main()
{
    int a, b;
    int *loc_a, *loc_b;

    a = 10;
    b = 20;
    loc_a = &a;
    loc_b = &b;

    printf("a = %d\nb = %d\nloc a = %u\nloc b = %u\n\n", a, b, loc_a, loc_b);
}

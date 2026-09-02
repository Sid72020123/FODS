# C Programming Practice Problems & Solutions

## 1) Find Sum of First N Natural Numbers

```c
#include <stdio.h>

void main()
{
    int i, n, sum = 0;

    printf("Enter a number: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        sum += i;
    }

    printf("\nSum of %d natural numbers [1 to %d] = %d\n", n, n, sum);
}
```

## 2) Find Factorial of a Number

```c
#include <stdio.h>

int factorial(int);

void main()
{
    int n, result;

    printf("Enter a number: ");
    scanf("%d", &n);

    result = factorial(n);

    printf("\nFactorial of %d = %d\n", n, result);
}

int factorial(int n)
{
    int i, result = 1;
    for (i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}
```

## 3) Print Multiplication Table of a Number

```c
#include <stdio.h>

void print_table(int);

void main()
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    print_table(n);
}

void print_table(int n)
{
    printf("\nMultiplication table of %d:\n", n);
    int i;

    for (i = 1; i <= 10; i++)
    {
        printf("%d x %d = %d\n", n, i, n * i);
    }
}
```

## 4) Print Even and Odd Series

```c
#include <stdio.h>

void main()
{
    int start, end, i;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    printf("\nEven numbers in series [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        if (i % 2 == 0)
            printf("%d ", i);
    }

    printf("\nOdd numbers in series [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        if (i % 2 != 0)
            printf("%d ", i);
    }
}
```

## 5) Print Alphabets, Digits, and Special Symbols Separately from Given String

```c
#include <stdio.h>

void main()
{
    char str[100];
    int i;

    printf("\nEnter a string: ");
    fgets(str, sizeof str, stdin); // Or normal gets(str) in Turbo C

    printf("\nAlphabets: ");
    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z'))
            printf("%c ", str[i]);
    }

    printf("\nDigits: ");
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            printf("%c ", str[i]);
    }

    printf("\nSpecial Symbols: ");
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= '0' && str[i] <= '9')))
            printf("%c ", str[i]);
    }
}
```

## 6) Display Whether Entered Number is Prime or Not

```c
#include <stdio.h>

void main()
{
    int n, i, count = 0;

    printf("Enter a number: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        if (n % i == 0)
            count++;
    }

    if (count == 2)
        printf("%d is a Prime number\n", n);
    else
        printf("%d is NOT a Prime number\n", n);
}
```

## 7) Display Series 1 11 111 1111 11111…

```c
#include <stdio.h>

void main()
{
    int n, i, j;
    printf("Enter the number of terms in series: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("1");
        }
        printf(" ");
    }
}
```

## 8) Display Series 1 5 26 677…

```c
#include <stdio.h>

void main()
{
    int n, i, temp;
    printf("Enter the number of terms in series: ");
    scanf("%d", &n);

    if (n >= 1)
        printf("1 ");

    if (n >= 2)
    {
        temp = 5;
        printf("5 ");
    }

    for (i = 3; i <= n; i++)
    {
        temp = (temp * temp) + 1;
        printf("%d ", temp);
    }
}
```

## 9) Display Series 1 2 5 16 65 356…

```c
#include <stdio.h>

void main()
{
    int n, i, temp = 1;
    printf("Enter the number of terms in series: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        temp = (i * temp) + 1;
        printf("%d ", temp);
    }
}
```

## 10) Display Fibonacci Series

```c
#include <stdio.h>

void main()
{
    int n, i;
    int a = 0, b = 1, c;

    printf("Enter number of terms in series: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }
}
```

## 11) Display 2D \* Pattern

```c
#include <stdio.h>

void main()
{
    int i, j, n;

    printf("Enter the size: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
}
```

## 12) Display Pyramid or Triangle

```c
#include <stdio.h>

void main()
{
    int i, j, n;

    printf("Enter the size: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
}
```

## 13) Display Table from 2 to 20

```c
#include <stdio.h>

void main()
{
    int i, j, start, end;

    start = 2;
    end = 20;

    for (i = 1; i <= 10; i++)
    {
        for (j = start; j <= end; j++)
        {
            printf("%3d ", j * i);
        }
        printf("\n");
    }
}
```

## 14) Display 1 12 123 1234…

```c
#include <stdio.h>

void main()
{
    int i, j, n;

    printf("Enter the number of terms in pattern: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("%d", j);
        }
        printf(" ");
    }
}
```

## 15) Sum of First N Even and Odd Numbers

```c
#include <stdio.h>

void main()
{
    int start, end, i, sum = 0;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    printf("\nEven numbers in series [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nSum of Even numbers = %d\n", sum);

    sum = 0;
    printf("\nOdd numbers in series [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        if (i % 2 != 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nSum of Odd numbers = %d\n", sum);
}
```

## 16) Reverse a Number

```c
#include <stdio.h>

void main()
{
    int num, rev = 0, rem;

    printf("Enter a number: ");
    scanf("%d", &num);

    while (num != 0)
    {
        rem = num % 10;       // get last digit
        rev = rev * 10 + rem; // append it to reverse
        num = num / 10;       // remove last digit
    }

    printf("Reversed number: %d\n", rev);
}
```

## 17) Count Digits in a Number

```c
#include <stdio.h>

void main()
{
    int num, count = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num == 0)
        count = 1; // 0 has 1 digit

    while (num != 0)
    {
        num = num / 10; // remove last digit
        count++;        // increment digit count
    }

    printf("Number of digits: %d\n", count);
}
```

## 18) Print All Prime Numbers in a Range

```c
#include <stdio.h>

void main()
{
    int start, end, i, count = 0, j;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    printf("\nPrime numbers in range [%d - %d]: ", start, end);
    for (i = start; i <= end; i++)
    {
        count = 0;
        for (j = 1; j <= i; j++)
        {
            if (i % j == 0)
                count++;
        }
        if (count == 2)
        {
            printf("%d ", i);
        }
    }
}
```

## 19) Transpose of Given Matrix (2D)

```c
#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10], transpose[10][10];

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Transpose the matrix
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }

    printf("\nOriginal Matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nTransposed Matrix:\n");
    for (i = 0; i < cols; i++)
    {
        for (j = 0; j < rows; j++)
        {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }
}
```

## 20) Addition of 2 Matrices (2D)

```c
#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix1[10][10], matrix2[10][10], sum[10][10];

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter elements of first matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("\nEnter elements of second matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix2[i][j]);
        }
    }

    // Add matrices
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    printf("\nFirst Matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("\nSecond Matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    printf("\nSum of Matrices:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
}
```

## 21) Display All Even and Odd Numbers in Given Matrix (2D)

```c
#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10];

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nEven numbers in matrix: ");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 2 == 0)
            {
                printf("%d ", matrix[i][j]);
            }
        }
    }

    printf("\n\nOdd numbers in matrix: ");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 2 != 0)
            {
                printf("%d ", matrix[i][j]);
            }
        }
    }
    printf("\n");
}
```

## 22) Addition of All Even and Odd Numbers in Given Matrix (2D)

```c
#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10];
    int evenSum = 0, oddSum = 0;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Calculate sum of even and odd numbers
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 2 == 0)
            {
                evenSum += matrix[i][j];
            }
            else
            {
                oddSum += matrix[i][j];
            }
        }
    }

    printf("\nSum of even numbers: %d\n", evenSum);
    printf("Sum of odd numbers: %d\n", oddSum);
}
```

## 23) Display an Alternate Element from Given 1D Array

```c
#include <stdio.h>

void main()
{
    int n, i;
    int arr[20];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    for (i = 0; i < n; i++)
    {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("\nAlternate elements from array: ");
    for (i = 0; i < n; i = i + 2)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
```

## 24) Find and Display Smallest and Largest Element from Given 1D Array

```c
#include <stdio.h>

void main()
{
    int n, i;
    int arr[20];
    int smallest, largest;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    for (i = 0; i < n; i++)
    {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    smallest = arr[0];
    largest = arr[0];

    for (i = 1; i < n; i++)
    {
        if (arr[i] < smallest)
            smallest = arr[i];

        if (arr[i] > largest)
            largest = arr[i];
    }

    printf("\nSmallest element: %d\n", smallest);
    printf("Largest element: %d\n", largest);
}
```

## 25) Sum and Average of Numbers Given in 1D or 2D Array

```c
#include <stdio.h>

void main()
{
    int n, i, j;
    int arr[10][10];
    int rows, cols;
    float sum = 0, average;
    int count = 0;
    int choice;

    printf("Choose array type:\n");
    printf("1. 1D Array\n");
    printf("2. 2D Array\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\nEnter number of elements: ");
        scanf("%d", &n);

        printf("\nEnter array elements:\n");
        for (i = 0; i < n; i++)
        {
            printf("Element [%d]: ", i);
            scanf("%d", &arr[0][i]);
            sum += arr[0][i];
        }
        average = sum / n;

        printf("\nSum: %.2f\n", sum);
        printf("Average: %.2f\n", average);
    }
    else if (choice == 2)
    {
        printf("\nEnter number of rows: ");
        scanf("%d", &rows);

        printf("Enter number of columns: ");
        scanf("%d", &cols);

        printf("\nEnter matrix elements:\n");
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                printf("Element [%d][%d]: ", i, j);
                scanf("%d", &arr[i][j]);
                sum += arr[i][j];
                count++;
            }
        }
        average = sum / count;

        printf("\nSum: %.2f\n", sum);
        printf("Average: %.2f\n", average);
    }
}
```

## 26) Display Upper Triangle Element from 2D Array

```c
#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10];

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nUpper Triangle Elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (j >= i)
            {
                printf("%d ", matrix[i][j]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}
```

## 27) Display Lower Triangle Element from 2D Array

```c
#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10];

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nLower Triangle Elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (j <= i)
            {
                printf("%d ", matrix[i][j]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}
```

## 28) Arithmetic Operations Using Switch Case

```c
#include <stdio.h>

void main()
{
    int num1, num2;
    char op;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%d", &num2);

    switch (op)
    {
    case '+':
        printf("\nResult: %d + %d = %d\n", num1, num2, num1 + num2);
        break;

    case '-':
        printf("\nResult: %d - %d = %d\n", num1, num2, num1 - num2);
        break;

    case '*':
        printf("\nResult: %d * %d = %d\n", num1, num2, num1 * num2);
        break;

    case '/':
        if (num2 != 0)
            printf("\nResult: %d / %d = %d\n", num1, num2, num1 / num2);
        else
            printf("\nError: Division by zero!\n");
        break;

    default:
        printf("\nInvalid operator!\n");
    }
}
```

## 29) Enter the Marks and Calculate Average of N Numbers Using Either Loop or 1D Array

```c
#include <stdio.h>

void main()
{
    int n, i;
    int marks[20];
    int sum = 0;
    float average;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("\nEnter marks of %d students:\n", n);
    for (i = 0; i < n; i++)
    {
        printf("Marks [%d]: ", i + 1);
        scanf("%d", &marks[i]);
        sum += marks[i];
    }

    average = (float)sum / n;

    printf("\nTotal marks: %d\n", sum);
    printf("Average marks: %.2f\n", average);
}
```

## 30) Find Largest Among Three Variables

```c
#include <stdio.h>

void main()
{
    int a, b, c, largest;

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    printf("Enter third number: ");
    scanf("%d", &c);

    largest = a;

    if (b > largest)
        largest = b;

    if (c > largest)
        largest = c;

    printf("\nLargest number among %d, %d, %d is: %d\n", a, b, c, largest);
}
```

## 31) Display Whether Entered Year is Leap Year or Not

```c
#include <stdio.h>

void main()
{
    int year;

    printf("Enter a year: ");
    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        printf("%d is a Leap Year\n", year);
    }
    else
    {
        printf("%d is not a Leap Year\n", year);
    }
}
```

## 32) Enter the Marks and Calculate Average of N Numbers and Display Result in Which Grade (Distinction, 1st Class, 2nd Class, or Pass Class)

```c
#include <stdio.h>

void main()
{
    int n, i;
    int marks[20];
    int sum = 0;
    float average;
    char grade;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("\nEnter marks of %d students:\n", n);
    for (i = 0; i < n; i++)
    {
        printf("Marks [%d]: ", i + 1);
        scanf("%d", &marks[i]);
        sum += marks[i];
    }

    average = (float)sum / n;

    printf("\nTotal marks: %d\n", sum);
    printf("Average marks: %.2f\n", average);

    if (average >= 75)
    {
        grade = 'D'; // Distinction
        printf("Grade: Distinction\n");
    }
    else if (average >= 60)
    {
        grade = 'A'; // First Class
        printf("Grade: First Class\n");
    }
    else if (average >= 45)
    {
        grade = 'B'; // Second Class
        printf("Grade: Second Class\n");
    }
    else if (average >= 35)
    {
        grade = 'C'; // Pass Class
        printf("Grade: Pass Class\n");
    }
    else
    {
        grade = 'F'; // Fail
        printf("Grade: Fail\n");
    }
}
```

## 33) To Analyze Problem Solving and Program Structures (Calculate Factorial)

```c
#include <stdio.h>

void main()
{
    // Simple problem: Calculate factorial of a number
    int n, i, fact = 1;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Factorial of negative number is not defined!\n");
    }
    else if (n == 0 || n == 1)
    {
        printf("Factorial of %d = 1\n", n);
    }
    else
    {
        for (i = 2; i <= n; i++)
        {
            fact *= i;
        }
        printf("Factorial of %d = %d\n", n, fact);
    }
}
```

## 34) Assignment Based on Operators and Expressions (Area and Perimeter of Rectangle)

```c
#include <stdio.h>

void main()
{
    // Operators and expressions: Area and Perimeter of a rectangle
    float length, width, area, perimeter;

    printf("Enter length of rectangle: ");
    scanf("%f", &length);

    printf("Enter width of rectangle: ");
    scanf("%f", &width);

    area = length * width;
    perimeter = 2 * (length + width);

    printf("\nArea of rectangle: %.2f\n", area);
    printf("Perimeter of rectangle: %.2f\n", perimeter);
}
```

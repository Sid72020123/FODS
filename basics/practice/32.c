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

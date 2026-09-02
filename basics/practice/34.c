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

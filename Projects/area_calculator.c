#include <stdio.h>

#define PI 3.14159265358979323846

int main() {
    int choice;
    float length, width, base, radius, area;

    while (1) {
        printf("\nSelect a shape to calculate it's area:\n");
        printf("1. Rectangle\n");
        printf("2. Triangle\n");
        printf("3. Circle\n");
        printf("4. Quit\n");
        printf("Enter choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Exiting area calculator, Bye!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter length of rectangle: ");
                scanf("%f", &length);
                printf("Enter width of rectangle: ");
                scanf("%f", &width);

                if (length <= 0.0 || width <= 0.0) {
                    printf("Length and width must be greater than 0.\n");
                } else {
                    area = length * width;
                    printf("The area of the rectangle is: %.2f\n", area);
                }
                break;

            case 2:
                printf("Enter the length of the triangle: ");
                scanf("%f", &length);
                printf("Enter base of the triangle: ");
                scanf("%f", &base);

                if (length <= 0.0 || base <= 0.0) {
                    printf("Length and base must be greater than 0.\n");
                } else {
                    area = 0.5 * length * base;
                    printf("The area of the triangle is: %.2f\n", area);
                }
                break;

            case 3:
                printf("Enter radius of circle: ");
                scanf("%f", &radius);

                if (radius <= 0.0) {
                    printf("Radius must be greater than 0.\n");
                } else {
                    area = PI * radius * radius;
                    printf("The area of the circle is: %.2f\n", area);
                }
                break;

            default:
            printf("Please select a number from 1-4.\n");
        }
    }
    
    return 0;
}
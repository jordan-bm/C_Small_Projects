#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Functions
void print_array(int *arr, int size);
int sum_array(int *arr, int size);
int max_array(int *arr, int size);
bool is_prime(int n);
void primes_array(int *arr, int size);

int main() {
    char option;
    int size;

    printf("Choose option:\n");
    printf("  p: Print array elements\n");
    printf("  s: Calculate sum\n");
    printf("  m: Find maximum\n");
    printf("  c: Print primes\n");
    printf("Enter option: ");
    scanf(" %c", &option);

    printf("Enter array size: ");
    scanf("%d", &size);

    int *arr = malloc(size * sizeof(int));
    printf("Enter %d array elements separated by spaces:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    switch (option) {
        case 'p':
            printf("Array elements:");
            print_array(arr, size);
            break;
        case 's':
            printf("Sum: %d\n", sum_array(arr, size));
            break;
        case 'm':
            printf("Max value: %d\n", max_array(arr, size));
            break;
        case 'c':
            primes_array(arr, size);
            break;
        default:
            printf("Invalid option\n");
            free(arr);
            return EXIT_FAILURE;
    }

    free(arr);
    return EXIT_SUCCESS;
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; sum += arr[i++]);
    return sum;
}

int max_array(int *arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void primes_array(int *arr, int size) {
    printf("Prime numbers:");
    bool found = false;
    
    for (int i = 0; i < size; i++) {
        if (is_prime(arr[i])) {
            printf(" %d", arr[i]);
            found = true;
        }
    }
    printf("%s\n", found ? "" : " None");
}

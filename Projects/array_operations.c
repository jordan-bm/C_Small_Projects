#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Functions
void print_array(int *arr, int size);
int sum_array(int *arr, int size);
int max_array(int *arr, int size);
bool is_prime(int n);
void primes_array(int *arr, int size);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <option> <array_size> [array_elements...]\n", argv[0]);
        printf("Options:\n"
               "  -p: Print array elements\n"
               "  -s: Calculate sum\n"
               "  -m: Find maximum\n"
               "  -c: Print primes\n");
        return EXIT_FAILURE;
    }

    char option = argv[1][1];
    int size = atoi(argv[2]);
    int *arr = malloc(size * sizeof(int));

    // Initialize array (set elements to 0 if not provided)
    for (int i = 0; i < size; i++) {
        arr[i] = (i < argc - 3) ? atoi(argv[i + 3]) : 0;
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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NUMBERS 10

int digits(int n) {
    return (int)log10(n) + 1;
}

// Function to check if `a` ends with `b`
bool endswith(int a, int b) {
    int b_digits = digits(b);
    return (a % (int)pow(10, b_digits)) == b;
}

bool is_tractable(int test_value, int *numbers, int size, bool check_concat = true) {
    if (size == 1) {
        return numbers[0] == test_value;
    }

    int n = numbers[size - 1];
    int *head = numbers; // Remaining numbers
    int new_size = size - 1;

    if (is_tractable(test_value - n, head, new_size, check_concat)) {
        return true;
    }

    if (test_value % n == 0) {
        int q = test_value / n;
        if (is_tractable(q, head, new_size, check_concat)) {
            return true;
        }
    }

    if (check_concat && endswith(test_value, n)) {
        int truncated = test_value / (int)pow(10, digits(n));
        if (is_tractable(truncated, head, new_size, check_concat)) {
            return true;
        }
    }

    return false;
}

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int test_value;
    int numbers[MAX_NUMBERS];  // Array to hold numbers
    int num_count;

    int result1 = 0;
    int result2 = 0;

    while (fscanf(file, "%d:", &test_value) == 1) {  // Read the line number
        printf("Line number: %d\n", test_value);

        num_count = 0;
        while (fscanf(file, "%d", &numbers[num_count]) == 1) {
            num_count++;
            if (getc(file) == '\n' || feof(file)) {
                break;
            }
            if (is_tractable(test_value, numbers, False)) {
                result1 += test_value;
                result2 += test_value;
            } else if (is_tractable(test_value, numbers)) {
                result2 += test_value;
            }
        }
        
    }

    // printf("result: %d\n", result_count);

    fclose(file);
    return 0;
}

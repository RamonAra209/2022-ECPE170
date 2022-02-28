#include "demo_functions.h"

int** create_array(int size) {
    int** my_array = calloc(size, sizeof(int *));

    printf("\nFilling array with random numbers in range of 0 to 1000\n\n");
    for (int row = 0; row < size; row++) {
        my_array[row] = calloc(size, sizeof(int));

        for (int col = 0; col < size; col++) {
            my_array[row][col] = rand() % 1001;
        }
    }

    return my_array;
}

int calculate_sum(int** arr, int size) {
    int sum = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            sum += arr[row][col];
        }
    }
    return sum;
}

void print_array(int** arr, int size) {
    printf("\t");
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("%d, ", arr[row][col]);
        }
        printf("\n \t");
    }
}

void free_array(int ** arr, int size) {
    for (int col = 0; col < size; col++) {
        free(arr[col]);
    }
    free(arr);
    //! Check to see if there is any memory leaks with valgrind
    //! ^^ Check lab 4
}
#include "demo_functions.h"
#include <time.h>

// name: Ramon Arambula
// email: r_arambula@u.pacific.edu

int main() {
    srand(time(0));
    int size = 5;
    
    printf("Initializing array with size %d x %d\n", size, size);
    int** my_arr = create_array(size);

    int sum = calculate_sum(my_arr, size);
    printf("Calculating sum for the following array: \n");
    print_array(my_arr, size);
    printf("\nSum of array: %d\n", sum);

    free_array(my_arr, size);
}
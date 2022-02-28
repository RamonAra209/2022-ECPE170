#ifndef DEMO_FUNCTIONS_H
#define DEMO_FUNCTIONS_H

#include "stdio.h"
#include "stdlib.h"

int** create_array(int size);
int calculate_sum(int** arr, int size);
void print_array(int** arr, int size);
void free_array(int ** arr, int size);

#endif
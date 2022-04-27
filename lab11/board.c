#include <stdlib.h>
#include <stdio.h>
#include "board.h"
uint32_t m_w = 50000;
uint32_t m_z = 60000;

char** create_board_arr() {
    char** my_array = calloc(6, sizeof(char *));
    for (int row = 0; row < 6; row++) {
        my_array[row] = calloc(9, sizeof(char));
        for (int col = 0; col < 9; col++) {
            if (col == 0 || col == 8) {
                if (row % 2 == 0) {
                    my_array[row][col] = 'C';
                } else {
                    my_array[row][col] = 'H';
                }
            } else {
                my_array[row][col] = '-';
            }
        }
    }
    return my_array;
}

void print_board(char** board) {
    printf("  1 2 3 4 5 6 7 \n");
    printf("=================\n");

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 9; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }

    printf("=================\n\n");
}

int place_token(char player, int col, char** board) {
    for (int row = 5; row >= 0; row--) {
        if (board[row][col] == '-') {
            board[row][col] = player;
            return 1; //* Ends for loop, returns 1 (True) for valid move
        }
    } 
    return 0; //* Returns 0 if invalid move
}

uint32_t get_random() {
    uint32_t result;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    result = (m_z << 16) + m_w;  /* 32-bit result */
    return result;
}

uint32_t random_in_range(int low, int high) {
    uint32_t range = high-low+1;
    uint32_t rand_num = get_random();
    return (rand_num % range) + low;
}
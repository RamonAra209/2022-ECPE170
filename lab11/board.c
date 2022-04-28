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

int* place_token(char player, int col, char** board) {
    int result[3];
    // result[0] = int representing bool of valid placement
    // result[1] = if result[0] == 1, then result[1] = row placed at ]

    for (int row = 5; row >= 0; row--) {
        if (board[row][col] == '-') {
            board[row][col] = player;
            result[0] = 1;
            result[1] = row;
            result[2] = col;
            // return 1; //* Ends for loop, returns 1 (True) for valid move
            return result;
        }
    } 
    // return 0; //* Returns 0 if invalid move
    result[0] = 0;
    result[1] = 0;
    result[2] = 0; 
    return result;
}

// int check_win(char player, int* pos, char** board) {
int check_win(char player, int l_row, int l_col, char** board) {
    // int start_row = pos[2];
    // int start_col = pos[3];
    int thresh = 5;
    int start_row = l_row;
    int start_col = l_col;
    int count = 0;
    // Checking vertical condition
    // for (int row = 0; row < 6; row++) {
    //     if (board[row][start_col] == player) {
    //         count++;
    //         if (count >= thresh) { 
    //             printf("\n\nVertical Condition Met \n\n");
    //             return 1;
    //         }
    //     } else {
    //         count = 0;
    //     }
    // }

    // Horizontal Condition
    // count = 0;
    // for (int col = 0; col < 9; col++) {
    //     if (board[start_row][col] == player) {
    //         count++;
    //         if (count >= thresh) {
    //             printf("\n\nHorizontal Condition Met \n\n");
    //             return 1;
    //         }
    //     } else {
    //         count = 0;
    //     }
    // }
    
    // Diagonal Check
    count = 0;
    return 0;
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
#include <stdlib.h>
#include <stdio.h>
#include "board.h"

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
    printf("\n  1 2 3 4 5 6 7 \n");
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
    int* result = calloc(3, sizeof(int));
    // result[0] = isValid (i.e. 0 or 1)
    // result[1] = row
    // result[2] = col

    for (int row = 5; row >= 0; row--) {
        if (board[row][col] == '-') {
            board[row][col] = player;
            result[0] = 1;
            result[1] = row;
            result[2] = col;
            return result;
        }
    } 
    result[0] = 0;
    result[1] = 0;
    result[2] = 0; 
    return result;
}

int check_direction(char player, int row, int col, int dx, int dy, char** board) {
    int count = 1;
    for (int i = 0; i < 2; i++) {
        int curr_row = row + dx;
        int curr_col = col + dy;
        while ((curr_row  >= 0 && curr_row < 6) && (curr_col >= 0 && curr_row < 9)) {
            if (board[curr_row][curr_col] == player) {
                count++;
            } else {
                break;
            }
            curr_row += dx;
            curr_col += dy;
        }
        dx *= -1;
        dy *= -1;
    }
    return count >= 5;
}

int check_win(char player, int row, int col, char** board) {
    return check_direction(player, row, col, 0, 1, board)
        || check_direction(player, row, col, -1, 1, board)
        || check_direction(player, row, col, 1, 0, board)
        || check_direction(player, row, col, 1, 1, board);
}

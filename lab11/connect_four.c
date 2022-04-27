#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    char** board = create_board_arr();
    print_board(board, 9, 6);
}


char** create_board_arr() {
    char** my_array = calloc(9, sizeof(char *));
    for (int row = 0; row < 9; row++) {
        my_array[row] = calloc(6, sizeof(char));
        for (int col = 0; col < 6; col++) {
            my_array[row][col] = '-';
        }
    }
    return my_array;
}

void print_board(char** board, int r_size, int c_size) {
    for (int row = 0; row < r_size; row++) {
        for (int col = 0; col < c_size; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

#include <stdlib.h>
#include <stdio.h>
#include "board.h"


int main(int argc, char* argv[]) {
    printf("Welcome to Connect 4, 5-in-a-Row Variant!\n");
    printf("Implemented by Ramon Arambula\n");

    int lower_bound = 123;
    int upper_bound = 456;
    // printf("Enter two positive numbers to initialize the random number generator\n");
    // printf("Number 1: ");
    // scanf("%d", &lower_bound);
    // printf("Number 2: ");
    // scanf("%d", &upper_bound);

    for (int i = 0; i < 30; i++) {
        int random_num = random_in_range(1, 8);
        printf("%d ", random_num);
    }
    printf("\n");

    // printf("Human Player (H) \nComputer Player (C) \n");
    // printf("Coin toss... HUMAN goes first\n\n"); //! Change this later if you put random
    //                                            //! num generator to pick who goes first
    // char** board = create_board_arr();
    // print_board(board);
    // place_token('H', 4, board);
    // print_board(board);

    //TODO Delete board here if you're not fucking lazy
}
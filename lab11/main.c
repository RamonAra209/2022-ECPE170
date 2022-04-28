#include <stdlib.h>
#include <stdio.h>
#include "board.h"


int main(int argc, char* argv[]) {
    printf("Welcome to Connect 4, 5-in-a-Row Variant!\n");
    printf("Implemented by Ramon Arambula\n");

    // int lower_bound = 123;
    // int upper_bound = 456;
    // printf("Enter two positive numbers to initialize the random number generator\n");
    // printf("Number 1: ");
    // scanf("%d", &lower_bound);
    // printf("Number 2: ");
    // scanf("%d", &upper_bound);
    printf("\n");

    // printf("Human Player (H) \nComputer Player (C) \n");
    // printf("Coin toss... HUMAN goes first\n\n"); //! Change this later if you put random
                                                    //! num generator to pick who goes first
    char** board = create_board_arr();

    print_board(board);

    int* location;
    int count = 0;
    int win = 0;
    do {
        int player_choice = 0;
        printf("What column would you like to drop token into? Enter 1-7: ");
        scanf("%d", &player_choice);
        location = place_token('H', player_choice, board);

        if (location[0] == 1) {
            // win = check_win('H', location, board);
        }

        int* location; //? location[isValid, row, col]
        do {
            int computer_choice = random_in_range(1, 7);
            location = place_token('C', computer_choice, board);
            if (location[0] == 1) { // If placement was valid, check win conditions
                printf("Entered\n");
                win = check_win('C', location[1], location[2], board);
                printf("Exited \n");
            }
        } while (location[0] == 0); // As long as isValid != 1 (i.e. True)
        count++;
    // } while (win != 1);
    } while (count <= 22);
    printf("\n Ended");
    print_board(board);

    //TODO Delete board here if you're not fucking lazy
}
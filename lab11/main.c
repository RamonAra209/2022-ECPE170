#include <stdlib.h>
#include <stdio.h>
#include "board.h"
uint32_t m_w = 50000;
uint32_t m_z = 60000;


int main(int argc, char* argv[]) {
    printf("Welcome to Connect 4, 5-in-a-Row Variant!\n");
    printf("Implemented by Ramon Arambula\n");

    printf("Enter two positive numbers to initialize the random number generator\n");
    printf("Number 1: ");
    scanf("%d", &m_w);
    printf("Number 2: ");
    scanf("%d", &m_z);
    printf("\n");

    printf("Human Player (H) \nComputer Player (C) \n");
    printf("Coin toss... HUMAN goes first\n\n"); //! Change this later if you put random
                                                 //! num generator to pick who goes first
                                                    
    char** board = create_board_arr();

    int* location;
    int win = 0;
    do {
        print_board(board);
        int player_choice = 0;
        printf("What column would you like to drop token into? Enter 1-7: ");
        scanf("%d", &player_choice);
        location = place_token('H', player_choice, board);

        if (location[0] == 1) {
            win = check_win('H', location[1], location[2], board);
            if (win) break; 
        }

        do {
            int computer_choice = random_in_range(1, 7);
            location = place_token('C', computer_choice, board);
            if (location[0] == 1) { // If placement was valid, check win conditions
                win = check_win('C', location[1], location[2], board);
            }
        } while (location[0] == 0); // As long as isValid != 1 (i.e. True)
    } while (win != 1);
    print_board(board);

    printf("Location: r=%d c=%d \n", location[1], location[2]);
    if (board[location[1]][location[2]] == 'H') {
        printf("Congratulations, HUMAN winner!\n");
    } else if (board[location[1]][location[2]] == 'C') {
        printf("Congratulations, COMPUTER winner!\n");
    }
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
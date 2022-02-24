#include "ship.h"
#include "board.h"
#include "demo.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// name: Ramon Arambula
// email: r_arambula@u.pacific.edu

struct ship create_ship(char type) {
    struct ship new_ship;
    new_ship.is_dead = 0;
    new_ship.ship_type = type;
    if (type == 'f') {
        new_ship.length = 2;
    } else if (type == 'b') {
        new_ship.length = 4;
    } else if (type == 'c') {
        new_ship.length = 5;
    }

    return new_ship;
}

void generate_position(int board_size, struct ship *ship_to_be_placed, int demo_mode, int is_second_frig) {
    if (demo_mode == 1) {
        FILE *f = fopen("demo_file.txt", "r");
        char line[100];
        int count = 0;
        while (fgets(line, sizeof(line), f)) {
            count++;
            if (is_second_frig == 1 && count == 7) {
                if (line[2] == 'r') {
                    ship_to_be_placed->is_vertical = 1;
                } else {
                    ship_to_be_placed->is_vertical = 0;
                }
                ship_to_be_placed->pos_col = line[4] - 97;
                ship_to_be_placed->pos_row = line[5] - 49;
            }

            if (line[0] != '#' && line[0] == ship_to_be_placed->ship_type && is_second_frig == 0) {
                if (line[2] == 'r') { // spawns vertically
                    ship_to_be_placed->is_vertical = 1;
                } 
                
                if (line[2] == 'c') { // spawns horizontally
                    ship_to_be_placed->is_vertical = 0;
                }

                ship_to_be_placed->pos_col = line[4] - 97;
                // printf("Col: %d\n", ship_to_be_placed->pos_col);
                ship_to_be_placed->pos_row = line[5] - 49;
                // printf("Row: %d\n", ship_to_be_placed->pos_row);

                break;
            }
        }
    } else {
        ship_to_be_placed->is_vertical = rand() % 2;

        if (ship_to_be_placed->is_vertical == 0) { // not vertical, therefore col changes
            ship_to_be_placed->pos_row = rand() % (board_size);
            ship_to_be_placed->pos_col = rand() % (board_size - ship_to_be_placed->length + 1);
        } else if (ship_to_be_placed->is_vertical == 1) { // vertical, so row changes
            ship_to_be_placed->pos_row = rand() % (board_size - ship_to_be_placed->length + 1);
            ship_to_be_placed->pos_col = rand() % (board_size);
        }
    }
}

int place_ship(char** hidden_board, struct ship *ship_to_be_placed) {
    // printf("PLACE FUNCTION isVert: %d \n", ship_to_be_placed->is_vertical);
    // printf("PLACE FUNCTION row: %d \n", ship_to_be_placed->pos_row);
    // printf("PLACE FUNCTION col: %d \n", ship_to_be_placed->pos_col);
    if (ship_to_be_placed->is_vertical == 1) { // vertical, so row changes
        for (int row = 0; row < ship_to_be_placed->length; row++) {
            if (hidden_board[ship_to_be_placed->pos_row + row][ship_to_be_placed->pos_col] != '-') {
                return 0; //! Ship already exists at that position
            }
        }

        for (int row = 0; row < ship_to_be_placed->length; row++) {
            hidden_board[ship_to_be_placed->pos_row + row][ship_to_be_placed->pos_col] = ship_to_be_placed->ship_type;
        }
    } else if (ship_to_be_placed->is_vertical == 0) { // not vertical, so col changes
        for (int col = 0; col < ship_to_be_placed->length; col++) {
            if (hidden_board[ship_to_be_placed->pos_row][ship_to_be_placed->pos_col + col] != '-') {
                return 0; //! Ship already exists at that position
            }
        }

        for (int col = 0; col < ship_to_be_placed->length; col++) {
            hidden_board[ship_to_be_placed->pos_row][ship_to_be_placed->pos_col + col] = ship_to_be_placed->ship_type;
        }
    }

    return 1; //* Placed Successfuly
}

void place_ships_with_checks(char** hidden_board, struct ship *s, int size, int demo_mode, int is_second_frig) {
    int while_flag = 0;
    
    while (while_flag == 0) {
        generate_position(size, s, demo_mode, is_second_frig);
        // printf("Made it past generate \n");
        int place_ship_flag = place_ship(hidden_board, s);
        // printf("Place_ship_flag value: %d \n", place_ship_flag);
        if (place_ship_flag == 0) {
            // printf("DID NOT PLACE SHIP! \n");
        } else {
            // printf("Placed Ship! \n");
            while_flag = 1;
        }
    }
}


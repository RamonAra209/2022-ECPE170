#ifndef SHIP_H
#define SHIP_H
#include <stdbool.h>
#include <stdlib.h>

// name: Ramon Arambula
// email: r_arambula@u.pacific.edu

struct ship
{
    int length;
    int pos_row, pos_col;
    int is_dead;
    bool is_vertical;
    char ship_type;

    int** ship_segment_locations;
};

struct ship create_ship(char type);

void generate_position(int board_size, struct ship *ship_to_be_placed, int demo_mode, int is_second_frig); // 0 = false, 1 = true

int place_ship(char** hidden_board, struct ship *ship_to_be_placed);

void place_ships_with_checks(char** hidden_board, struct ship *s, int size, int demo_mode, int is_second_frig); // 0 = false, 1 = true 

#endif
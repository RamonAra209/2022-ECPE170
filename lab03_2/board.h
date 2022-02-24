#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "ship.h"

// name: Ramon Arambula
// email: r_arambula@u.pacific.edu


struct board
{
    int size;
    char** board_arr;
    char** ship_locations;
};

//* Board Functions
struct board init_board(int size);

char** create_board_arr(int size);
void print_b(char** b, int b_size);

void delete_board(struct board b);
void delete_hidden_board(struct board b);

//* Game Mechanics Functions
int* get_location(int amount_of_shots, int shots_taken);
void shoot_at_location(struct board b, int row, int col);
int check_boat_destruction(struct board b, struct ship *s);

#endif
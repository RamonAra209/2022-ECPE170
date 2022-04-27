#ifndef BOARD_H
#define BOARD_H

char** create_board_arr();
void print_board(char** board);
int place_token(char player, int col, char** board);
uint32_t get_random();
uint32_t random_in_range(int low, int hight);
#endif
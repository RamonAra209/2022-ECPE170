#ifndef BOARD_H
#define BOARD_H

char** create_board_arr();
void print_board(char** board);
int* place_token(char player, int col, char** board);
int check_direction(char player, int row, int col, int dx, int dy, char** board);
int check_win(char player, int row, int col, char** board);
uint32_t get_random();
uint32_t random_in_range(int low, int hight);
#endif
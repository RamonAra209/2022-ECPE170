#include "board.h"
#include <ctype.h>

// name: Ramon Arambula
// email: r_arambula@u.pacific.edu


struct board init_board(int size) {
    struct board b;
    b.size = size;
    // printf("Size mothercuckler: %d \n", b.size);
    b.board_arr = create_board_arr(b.size);
    b.ship_locations = create_board_arr(b.size);
    return b;
}

char** create_board_arr(int size) {
    char** my_array = calloc(size, sizeof(char *)); // size of had int *

    if (my_array == NULL) {
        printf("FATAL ERROR: out of memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int row = 0; row < size; row++) {
        my_array[row] = calloc(size, sizeof(char)); // size of had int
        for (int col = 0; col < size; col++) {
            my_array[row][col] = '-';
        }
        if (my_array[row] == NULL) {
            printf("FATAL ERROR: out of memoy: %s \n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    return my_array;
}

void print_b(char** b, int b_size) {
    printf("     ");
    for (int header_letter = 0; header_letter < b_size; header_letter++) {
        printf("%c ", (char) 65 + header_letter);
    }
    printf("\n");

    printf("   +");
    for (int header_hyphen = 0; header_hyphen < b_size; header_hyphen++) {
        printf("--");
    }
    printf("\n");


    for (int row = 0; row < b_size; row++) {
        printf("%d  | ", row + 1);
        for (int col = 0; col < b_size; col++) {
            printf("%c ", b[row][col]);
        }
        printf("\n");
    }
}

void delete_board(struct board b) {
    for (int col = 0; col < b.size; col++) {
        free(b.board_arr[col]);
    }
    free(b.board_arr);

    return;
}

void delete_hidden_board(struct board b) {
    for (int col = 0; col < b.size; col++) {
        free(b.ship_locations[col]);
    }
    free(b.ship_locations);

    return;
}

int* get_location(int amount_of_shots, int shots_taken) { 
    int* loc_array = calloc(2, sizeof(int));
    int shot_row = 0;
    int shot_col = 0;

    char* string_input = calloc(5, sizeof(char));
    printf("Enter the coordinate for your shot (%d shots remaining): ", (amount_of_shots - shots_taken));
    scanf("%s", string_input);
    printf("\n");

    int i = 0;
    if (tolower(string_input[i]) >= 97 && tolower(string_input[i]) <= 122) {
        shot_col = tolower(string_input[i]) - 97;

        i++;
    } 
    
    while (string_input[i] >= 48 && string_input[i] <= 57) {
        shot_row *= 10;
        shot_row += string_input[i] - 48;
        i++;
    }

    if (tolower(string_input[i]) >= 97 && tolower(string_input[i]) <= 122) {
        shot_col = tolower(string_input[i]) - 97;
    }

    loc_array[0] = shot_row - 1;
    loc_array[1] = shot_col;

    return loc_array;
}

void shoot_at_location(struct board b, int row, int col) {
    if (b.ship_locations[row][col] == 'f' || b.ship_locations[row][col] == 'b' || b.ship_locations[row][col] == 'c') {
        b.board_arr[row][col] ='h';
        printf("%c%d is a HIT \n", (char) (65 + col), row + 1);
        printf("\n");
    } else {
        b.board_arr[row][col] = 'm';
        printf("%c%d is a MISS \n", (char) (65 + col), row + 1);
        printf("\n");
    }
}

int check_boat_destruction(struct board b, struct ship *s) { 
    /* // TODO
        1. switch s to pointer
        2. Change any variable with pos_row or pos_col to be a regular variable, so you dont 
           change s's row or column value
        3. Change s.is_dead value to 1
        4. only return 1 when is_dead happens the first time, not any other subsequent checks
    */
    int hit_count = 0;
    int index_with_nothing = 0;
    for (int i = 0; i < s->length; i++) {
        if (s->is_vertical == 0) { // col changes
            if (b.board_arr[s->pos_row][s->pos_col + i] == 'h') {
                hit_count++;
            }

            if (b.board_arr[s->pos_row][s->pos_col + i] == '-') {
                index_with_nothing = s->pos_col + i;
            }
        } else { // row changes
            if (b.board_arr[s->pos_row + i][s->pos_col] == 'h') {
                hit_count++;
            }

            if (b.board_arr[s->pos_row + i][s->pos_col] == '-') {
                index_with_nothing = s->pos_row + i;
            }
        }
    }

    float boat_destruction = (float)hit_count / (float)s->length;
    if (s->is_dead != 1) {
        if ((boat_destruction >= 0.70) && s->is_vertical == 0) {
            if (s->ship_type != 'f') {
                b.board_arr[s->pos_row][index_with_nothing] = s->ship_type;
            }
            s->is_dead = 1;
        return 1;
        }

        if ((boat_destruction >= 0.70) && s->is_vertical == 1) {
            if (s->ship_type != 'f') {
                b.board_arr[index_with_nothing][s->pos_col] = s->ship_type;
            }
            s->is_dead = 1;
        return 1;
        }
    }
    return 0;
}

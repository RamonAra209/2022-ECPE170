#include <math.h>
#include <time.h>
#include <ctype.h>
#include "board.h"
#include "ship.h"
#include "demo.h"
// name: Ramon Arambula
// email: r_arambula@u.pacific.edu

int main(int argc, char *argv[]) {
    printf("Doesnt have time included \n");
    srand(time(0));

    int games_played = 0;
    int games_won = 0;
    int ships_sunk = 0;
    
    int is_demo = 0;

    if (argc > 1) {
        printf("Passed through terminal argument \n");
        demo_game();
        return 0;
    } 

    printf("Welcome to Frigate! \n \n");

    char play_again = 'y';
    while (play_again == 'y' || play_again == 'Y') {
        int size = 5;
        games_played += 1;
        int ships_sunk_this_round = 0;

        int amount_of_shots = 0;
        int shots_taken = 0;

        printf("How large should I make the grid?: ");
        scanf("%d", &size);
        if (size < 5) {
            printf("The minimum grid size is 5... I'll create one with that size. \n");
        } else {
            printf("Creating grid with size %d x %d \n", size, size);
        }
        
        amount_of_shots = (size * size) / 2;

        struct board game_state = init_board(size);
        
        //* Ship Generations
        struct ship carrier = create_ship('c');
        struct ship battleship = create_ship('b');
        struct ship frigate_1 = create_ship('f');
        struct ship frigate_2 = create_ship('f');

        place_ships_with_checks(game_state.ship_locations, &carrier, game_state.size, is_demo, 0);
        place_ships_with_checks(game_state.ship_locations, &battleship, game_state.size, is_demo, 0);
        place_ships_with_checks(game_state.ship_locations, &frigate_1, game_state.size, is_demo, 0);
        place_ships_with_checks(game_state.ship_locations, &frigate_2, game_state.size, is_demo, 0);

        printf("Player Board: \n");
        print_b(game_state.board_arr, game_state.size);

        printf("\n");

        printf("Hidden Board\n");
        print_b(game_state.ship_locations, game_state.size);

        while (shots_taken < amount_of_shots) {
            int* player_loc = get_location(amount_of_shots, shots_taken);
            if (player_loc[0] < 0 || player_loc[0] >= game_state.size || player_loc[1] < 0 || player_loc[1] >= game_state.size) {
                printf("Shot not taken! \n");
            } else {
                shoot_at_location(game_state, player_loc[0], player_loc[1]);

                ships_sunk_this_round += check_boat_destruction(game_state, &carrier);
                ships_sunk_this_round += check_boat_destruction(game_state, &battleship);
                ships_sunk_this_round += check_boat_destruction(game_state, &frigate_1);
                ships_sunk_this_round += check_boat_destruction(game_state, &frigate_2);

                shots_taken++;
            }

            printf("Player Board: \n");
            print_b(game_state.board_arr, game_state.size);
            printf("Hidden Board: \n");
            print_b(game_state.ship_locations, game_state.size);

            if (ships_sunk_this_round == 4) {
                break;
            }
        }

        ships_sunk += ships_sunk_this_round;

        if ((amount_of_shots - shots_taken) == 0) {
            printf("You do not have enough shells left to sink the remaining ships. \n");
        }    

        if (ships_sunk_this_round == 4) {
            games_won += 1;
        }

        printf("Here is the original ship locations: \n");
        print_b(game_state.ship_locations, game_state.size);

        printf("\nYou sunk %d ships \n", ships_sunk);

        printf("\nPlay again (y/n): ");
        scanf(" %c", &play_again);
        
        printf("You won %d out of %d games. \n", games_won, games_played);

        delete_board(game_state);
        delete_hidden_board(game_state);
    }

    printf("Thanks for playing! \n"); 

    return 0;
}



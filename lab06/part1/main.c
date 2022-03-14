#include <stdint.h>
#include <stdio.h>

// Author: Ramon Arambula
// email: r_arambula@u.pacific.edu

uint32_t array1[3][5]; // 2D array
uint32_t array2[3][5][7];  // 3D array


//* Function Prototypes
void print_2d();
void print_3d();


int main() {
    print_2d();
    print_3d();
}

void print_2d() {
    //* Filling in array with values so I dont get seg-faulted
    int counter = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            counter++;
            array1[i][j] = counter;
        }
    }


    printf("Printing 2D Array where output is [Val: Address]");
    for (int i = 0; i < 3; i++) {
        printf("\n");
        for (int j = 0; j < 5; j++) {
            printf("\t%d: %x", array1[i][j], &array1[i][j]);
        }
        printf("\n");
    }


    printf("How 2d memory is stored in computer's 1d memory storage\n\t");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", array1[i][j]);
        }
    }
    printf("\n\n\n");
}

void print_3d() {
    //* Filling in array with values
    int counter = 1;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			for(int k = 0; k < 7; k++){
				array2[i][j][k] = counter;
				counter++;
			}
		}
	}


    printf("Printing 3D Array where output is \nDepth #\n\t[Val: Address]\n");
    for (int i = 0; i < 3; i++) {
        printf("Depth %d:\n", i);
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 7; k++) {
                printf("\t%d: %x", array2[i][j][k], &array2[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }



    printf("How 3d memory is stored in computer's 1d memory storage: \n\t" );
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			for(int k = 0; k < 7; k++){
				printf("%d ", array2[i][j][k]);;
			}
		}
	}
	printf("\n");

    printf("\nNOTE: If the output went onto a new line, its because the terminal tried to compensate for lack of terminal space, its all on one line!\n");
}
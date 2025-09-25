#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

void printGame(char** board, int rows, int cols) {
    int i, j;
    
    system("tput cup 0 0");

    for(i=0; i<cols+2; i++) { /* top border */
        printf("*");
    }
    printf("\n");

    for(i=0; i<rows; i++) { /* the actual game board */
        printf("*");
        for(j=0; j<cols; j++) {
            printf("%c", board[i][j]);
        }
        printf("*\n");
    }

    for(i=0; i<cols+2; i++) { /* bottom border */
        printf("*");
    }
    printf("\n");

    printf("Press 'w' to move up\n");
    printf("Press 's' to move down\n");
    printf("Press 'a' to move left\n");
    printf("Press 'd' to move right\n");
    printf("Press 'u' to undo\n");
}

/* Will always return one of 'w', 'a', 's', 'd' or 'u'. */
char getMove() {
    char move = 'e';

    disableBuffer();
    while(move != 'w' && move != 's' && move != 'a' && move != 'd' && move != 'u') {
        scanf(" %c", &move);
    }

    enableBuffer();
    return move;
}
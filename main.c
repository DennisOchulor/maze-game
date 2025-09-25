#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "game.h"
#include "linkedlist.h"
#include "gamestate.h"

/* Entrypoint. Setup the game by reading the mapfile, then pass it over to game.c */
int main(int argc, char** argv) {
    FILE* mapfile;
    int i, j, num, rand;
    char c;
    Position tempPos;
    GameState gameState;

    if (argc != 2) {
        printf("Usage: ./escape <map>\n");
    }
    else {
        mapfile = fopen(argv[1], "rb");
        if(mapfile == NULL) {
            perror("Error opening file");
        }
        else {
            /* get number of rows/cols, then malloc the board */
            fscanf(mapfile, "%d %d\n", &gameState.rows, &gameState.cols);
            gameState.board = malloc(sizeof(char*) * gameState.rows);
            for(i=0; i<gameState.rows; i++) {
                gameState.board[i] = malloc(sizeof(char) * gameState.cols);
            }
            
            /* fill the board and setup GameState */
            initRandom();
            gameState.numOfEnemies = 0;
            for(i=0; i<gameState.rows;i++) {
                for(j=0; j<gameState.cols; j++) {
                    fscanf(mapfile, "%d ", &num);
                    if(num == 0) gameState.board[i][j] = ' ';
                    else if(num == 1) {
                        gameState.board[i][j] = 'P';
                        gameState.playerPos = malloc(sizeof(Position));
                        gameState.playerPos->row = i;
                        gameState.playerPos->col = j;
                    }
                    else if(num == 2) gameState.board[i][j] = 'G';
                    else if(num == 3) gameState.board[i][j] = 'O';
                    else if(num == 4) {
                        gameState.numOfEnemies++;
                        rand = random_UCP(0,3);
                        if(rand == 0) gameState.board[i][j] = '^';
                        else if(rand == 1) gameState.board[i][j] = '>';
                        else if(rand == 2) gameState.board[i][j] = 'v';
                        else if(rand == 3) gameState.board[i][j] = '<';
                    }
                }
            }
            fclose(mapfile);

            gameState.history = createLinkedList();
            gameState.outcome = 0;
            /* Need to iterate through board and find all enemies again because we can't malloc until we know numOfEnemies */
            gameState.enemiesPos = malloc(sizeof(Position) * gameState.numOfEnemies);
            num = 0;
            for(i=0; i<gameState.rows; i++) {
                for(j=0; j<gameState.cols; j++) {
                    c = gameState.board[i][j];
                    if(c == '^' || c == '>' || c == 'v' || c == '<') {
                        tempPos.row = i;
                        tempPos.col = j;
                        gameState.enemiesPos[num] = tempPos;
                        num++;
                    }
                }
            }
        

            /* go to game */
            system("clear");
            play(&gameState);

            /* free everything */
            for(i=0; i<gameState.rows; i++) {
                free(gameState.board[i]);
            }
            free(gameState.board);
            free(gameState.enemiesPos);
            free(gameState.playerPos);
            freeLinkedList(gameState.history);
        }
    }

    return 0;
}
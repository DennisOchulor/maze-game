#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "gamestate.h"
#include "terminalio.h"
#include "linkedlist.h"
#include "newSleep.h"

void play(GameState* gameState) {
    char move;

    while(gameState->outcome == 0) {
        printGame(gameState->board, gameState->rows, gameState->cols);
        move = getMove();
        if(move == 'w' || move == 's' || move == 'a' || move == 'd') {
            insertLast(gameState->history, gameState->playerPos);
            movePlayer(gameState, move);
        }
        else { /* must be 'u' */
            if(gameState->history->count != 0) {
                rotateEnemiesCounterClockwise(gameState);
                gameState->board[gameState->playerPos->row][gameState->playerPos->col] = ' ';
                free(gameState->playerPos); /* free it cause it was malloc'd */
                gameState->playerPos = removeLast(gameState->history);
                gameState->board[gameState->playerPos->row][gameState->playerPos->col] = 'P';
            }
        }
    }

    printGame(gameState->board, gameState->rows, gameState->cols);
    if(gameState->outcome == 1) {
        printf("You win!\n");
    }
    else if(gameState->outcome == 2) {
        printf("You lose!\n");
    }
}

void movePlayer(GameState* gameState, char move) {
    Position* oldPlayerPos = gameState->playerPos;
    Position* newPlayerPos = malloc(sizeof(Position));
    char charAtNewPos;

    rotateEnemiesClockwise(gameState);

    if(move == 'w') {
        newPlayerPos->row = gameState->playerPos->row - 1;
        newPlayerPos->col = gameState->playerPos->col;
    }
    else if(move == 's') {
        newPlayerPos->row = gameState->playerPos->row + 1;
        newPlayerPos->col = gameState->playerPos->col;
    }
    else if(move == 'a') {
        newPlayerPos->row = gameState->playerPos->row;
        newPlayerPos->col = gameState->playerPos->col - 1;
    }
    else if(move == 'd') {
        newPlayerPos->row = gameState->playerPos->row;
        newPlayerPos->col = gameState->playerPos->col + 1;
    }

    /* respect the border and the walls */
    if(newPlayerPos->row == -1 || newPlayerPos->col == -1 || newPlayerPos->row == gameState->rows || newPlayerPos->col == gameState->cols) {
        newPlayerPos->row = gameState->playerPos->row;
        newPlayerPos->col = gameState->playerPos->col;
    }
    else if(gameState->board[newPlayerPos->row][newPlayerPos->col] == 'O') {
        newPlayerPos->row = gameState->playerPos->row;
        newPlayerPos->col = gameState->playerPos->col;
    }

    charAtNewPos = gameState->board[newPlayerPos->row][newPlayerPos->col];
    gameState->playerPos = newPlayerPos;
    gameState->board[oldPlayerPos->row][oldPlayerPos->col] = ' ';

    /* if player walks into enemy, LOSE! */
    if(charAtNewPos == '^' || charAtNewPos == '>' || charAtNewPos == 'v' || charAtNewPos == '<') {
        gameState->outcome = 2;
    }
    else if(charAtNewPos == 'G') { /* If player walks into the goal, WIN! */
        gameState->outcome = 1;
        gameState->board[newPlayerPos->row][newPlayerPos->col] = 'P';
    }
    else {
        gameState->board[newPlayerPos->row][newPlayerPos->col] = 'P';
        checkLineOfSight(gameState);
    }
}

void checkLineOfSight(GameState* gameState) {
    Position pos;
    pos.row = gameState->playerPos->row;
    pos.col = gameState->playerPos->col;

    /* check above player */
    while(pos.row >= 0 && gameState->outcome != 2) {
        if(gameState->board[pos.row][pos.col] == 'v') {
            gameState->outcome = 2;
            playChaseAnimation(gameState, &pos, 'v');
        }
        else if(gameState->board[pos.row][pos.col] == 'O') {
            pos.row = 0;
        }
        pos.row--;
    }

    pos.row = gameState->playerPos->row;
    pos.col = gameState->playerPos->col;

    /* check below player */
    while(pos.row < gameState->rows && gameState->outcome != 2) {
        if(gameState->board[pos.row][pos.col] == '^') {
            gameState->outcome = 2;
            playChaseAnimation(gameState, &pos, '^');
        }
        else if(gameState->board[pos.row][pos.col] == 'O') {
            pos.row = gameState->rows;
        }
        pos.row++;
    }

    pos.row = gameState->playerPos->row;
    pos.col = gameState->playerPos->col;

    /* check left of player */
    while(pos.col >= 0 && gameState->outcome != 2) {
        if(gameState->board[pos.row][pos.col] == '>') {
            gameState->outcome = 2;
            playChaseAnimation(gameState, &pos, '>');
        }
        else if(gameState->board[pos.row][pos.col] == 'O') {
            pos.col = 0;
        }
        pos.col--;
    }

    pos.row = gameState->playerPos->row;
    pos.col = gameState->playerPos->col;

    /* check right of player */
    while(pos.col < gameState->cols && gameState->outcome != 2) {
        if(gameState->board[pos.row][pos.col] == '<') {
            gameState->outcome = 2;
            playChaseAnimation(gameState, &pos, '<');
        }
        else if(gameState->board[pos.row][pos.col] == 'O') {
            pos.col = gameState->cols;
        }
        pos.col++;
    }
}

void playChaseAnimation(GameState* gameState, Position* enemyPos, char direction) {
    int i;

    printGame(gameState->board, gameState->rows, gameState->cols);    

    if(direction == 'v') {
        for(i=enemyPos->row; i<gameState->playerPos->row; i++) {
            gameState->board[i][enemyPos->col] = ' ';
            gameState->board[i+1][enemyPos->col] = direction;
            printGame(gameState->board, gameState->rows, gameState->cols);
            newSleep(0.5);
        }
    }
    else if(direction == '^') {
        for(i=enemyPos->row; i>gameState->playerPos->row; i--) {
            gameState->board[i][enemyPos->col] = ' ';
            gameState->board[i-1][enemyPos->col] = direction;
            printGame(gameState->board, gameState->rows, gameState->cols);
            newSleep(0.5);
        }
    }
    else if(direction == '<') {
        for(i=enemyPos->col; i>gameState->playerPos->col; i--) {
            gameState->board[enemyPos->row][i] = ' ';
            gameState->board[enemyPos->row][i-1] = direction;
            printGame(gameState->board, gameState->rows, gameState->cols);
            newSleep(0.5);
        }
    }
    else { /* direction == '>' */
        for(i=enemyPos->col; i<gameState->playerPos->col; i++) {
            gameState->board[enemyPos->row][i] = ' ';
            gameState->board[enemyPos->row][i+1] = direction;
            printGame(gameState->board, gameState->rows, gameState->cols);
            newSleep(0.5);
        }
    }
}

void rotateEnemiesClockwise(GameState* gameState) {
    int i;
    Position pos;
    char enemy;
    for(i=0; i<gameState->numOfEnemies; i++) {
        pos = gameState->enemiesPos[i];
        enemy = gameState->board[pos.row][pos.col];
        if(enemy == '^') gameState->board[pos.row][pos.col] = '>';
        else if(enemy == '>') gameState->board[pos.row][pos.col] = 'v';
        else if(enemy == 'v') gameState->board[pos.row][pos.col] = '<';
        else if(enemy == '<') gameState->board[pos.row][pos.col] = '^';
    }
}

void rotateEnemiesCounterClockwise(GameState* gameState) {
    int i;
    Position pos;
    char enemy;
    for(i=0; i<gameState->numOfEnemies; i++) {
        pos = gameState->enemiesPos[i];
        enemy = gameState->board[pos.row][pos.col];
        if(enemy == '^') gameState->board[pos.row][pos.col] = '<';
        else if(enemy == '>') gameState->board[pos.row][pos.col] = '^';
        else if(enemy == 'v') gameState->board[pos.row][pos.col] = '>';
        else if(enemy == '<') gameState->board[pos.row][pos.col] = 'v';
    }
}
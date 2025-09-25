#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "linkedlist.h"

typedef struct Position {
    int row;
    int col;
} Position;

typedef struct GameState {
    char** board;
    int rows, cols;
    int outcome; /* 0 - continue playing, 1 - win, 2 - lose */
    Position* playerPos;
    Position* enemiesPos;
    int numOfEnemies;
    LinkedList* history;
} GameState;

#endif
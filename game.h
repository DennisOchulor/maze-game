#ifndef GAME_H
#define GAME_H

#include "gamestate.h"

void play(GameState* gameState);
void movePlayer(GameState* gameState, char move);
void checkLineOfSight(GameState* gameState);
void playChaseAnimation(GameState* gameState, Position* enemyPos, char direction);
void rotateEnemiesClockwise(GameState* gameState);
void rotateEnemiesCounterClockwise(GameState* gameState);

#endif
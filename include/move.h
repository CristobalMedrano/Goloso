#ifndef _MOVE_H
#define _MOVE_H

Move** createListMove(int movements);
Move* createMove();
Move** addMoveToList(Move** currentList, int* movements, Move* currentMove);
Move* setMove(Move* currentMove, int origin, int destiny, int ton, float cost);
Move* getMinMove(Project* currentProject);
float getCurrentCost(Center* originCenter, int subsidy, int destinyDistance);
int moveEqualCenter(Move* move, Center* center);
void showListMove(Move** currentListMove, int movements);
void freeListMove(Move** currentListMove, int movements);
void freeMove(Move* currentMove);

#endif
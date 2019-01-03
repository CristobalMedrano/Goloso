#ifndef _MOVE_H
#define _MOVE_H

Move** createListMove();
Move* createMove();
Move** addMoveToList(Move** currentList, int* large, Move* currentMove);
Move* setMove(Move* currentMove, int origin, int destiny, int ton, float cost);
Move* getMinMove(Project* currentProject);
float getCurrentCost(Center* originCenter, int subsidy, int destinyDistance);
void showListMove(Move** currentListMove, int large);
void freeListMove(Move** currentListMove, int large);
void freeMove(Move* currentMove);

#endif
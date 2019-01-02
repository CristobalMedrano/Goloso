#ifndef _MOVE_H
#define _MOVE_H

Move* createMove(Project* currentProject);
Move* setMove(Move* currentMove, int origin, int destiny, int ton, int cost);

#endif
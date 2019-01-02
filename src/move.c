#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <move.h>

Move* createMove(Project* currentProject)
{
    Move* newMove = (Move*)malloc(sizeof(Move));
    
    if (NULL != newMove)
    {
        newMove->origin     = 0;
        newMove->destiny    = 0;
        newMove->ton        = 0;
        newMove->cost       = 0;
        return newMove;
    }
    return NULL;
}

Move* setMove(Move* currentMove, int origin, int destiny, int ton, int cost)
{
    if (NULL != currentMove)
    {
        currentMove->origin     = origin;
        currentMove->destiny    = destiny;
        currentMove->ton        = ton;
        currentMove->cost       = cost;
        return currentMove;
    }
    return NULL;
}
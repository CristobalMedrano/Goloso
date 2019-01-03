#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <structs.h>
#include <move.h>

Move** createListMove()
{
    Move** newListMove = (Move**)malloc(sizeof(Move*));

    if (NULL != newListMove) 
    {
        newListMove[0] = NULL;
        return newListMove;
    }
    return NULL;
}

Move* createMove()
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

Move** addMoveToList(Move** currentList, int* large, Move* currentMove)
{
    if (NULL != currentList) 
    {
        *large = *large + 1;
        currentList = (Move**)realloc(currentList, sizeof(Move*)*(*large));
        if (NULL != currentList) 
        {
            currentList[*large - 2] = currentMove;
            return currentList;
        }
        return NULL;
    }
    return NULL;
}

Move* setMove(Move* currentMove, int origin, int destiny, int ton, float cost)
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

Move* getMinMove(Project* currentProject)
{
    Center** listCenters    = currentProject->listCenters;
    int subsidy             = currentProject->subsidy;
    int numberCenters       = currentProject->numberCenters;

    Move* newMove = createMove();
    if (NULL != newMove) 
    {
        int i = 0;
        int j = 0;
        
        int origin      = 0;
        int destiny     = 0;
        int ton         = 0;
        float minCost   = (float)INFINITY;

        
        for(i = 0; i < numberCenters; i++)
        {   
            for(j = 0; j < numberCenters; j++)
            {
                if (i != j) 
                {
                    float currentCost = getCurrentCost(listCenters[i], subsidy, listCenters[j]->distance);

                    if (minCost > currentCost) 
                    {
                        origin  = listCenters[i]->distance;
                        destiny = listCenters[j]->distance;
                        ton     = listCenters[i]->ton + listCenters[j]->ton;
                        minCost = currentCost;
                    }   
                }   
            }
        }
        newMove = setMove(newMove, origin, destiny, ton, minCost);
        return newMove;
    } 
/* esto podria ser print current
    printf("min: %.2f", newMove->cost);
    printf("origin: %d", newMove->origin);
    printf("destiny: %d", newMove->destiny);
    printf("ton: %d", newMove->ton);*/
    return NULL;
}

float getCurrentCost(Center* originCenter, int subsidy, int destinyDistance)
{
    if (NULL != originCenter) 
    {
        int originDistance = originCenter->distance;
        int ton            = originCenter->ton;
        float newCost = abs(originDistance-destinyDistance)*(ton - (ton/(float)(subsidy)));
        return newCost;
    }
    return -1;
}

void showListMove(Move** currentListMove, int large)
{
    if (NULL != currentListMove && large >= 0) 
    {
        int i = 0;
        for(i = 0; i < large - 1; i++)
        {
            printf("min: %.2f", currentListMove[i]->cost);
            printf("origin: %d", currentListMove[i]->origin);
            printf("destiny: %d", currentListMove[i]->destiny);
            printf("ton: %d", currentListMove[i]->ton);
        }
        
    }
    
}

void freeListMove(Move** currentListMove, int large)
{
    if (NULL != currentListMove) 
    {
        int i = 0;
        for(i = 0; i < large; i++)
        {
            freeMove(currentListMove[i]);
        }
        free(currentListMove);
    }
}

void freeMove(Move* currentMove)
{
    if (NULL != currentMove) 
    {
        free(currentMove);
    }
}
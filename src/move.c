#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <structs.h>
#include <move.h>

Move** createListMove(int movements)
{
    if (movements > 0) 
    {
        Move** newListMove = (Move**)malloc(sizeof(Move*)*(movements));
        if (NULL != newListMove) 
        {
            int i = 0;
            for(i = 0; i < movements; i++)
            {               
                Move* newMove = createMove();
                
                if (NULL == newMove) 
                {
                    printf("Memoria insuficiente: createListMove()\n");
                    printf("Error: move.c\n");
                    return NULL;
                }
                
                newListMove[i] = newMove;
            }
            return newListMove;
        }
    }
    printf("Memoria insuficiente: createListMove()\n");
    printf("Error: move.c\n");
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

Move** addMoveToList(Move** currentList, int* movements, Move* currentMove)
{
    Move** newList = NULL;
    if (NULL != currentList) 
    {
        *movements = *movements + 1;
        newList = (Move**)realloc(currentList, (*movements)*sizeof(Move*));
        if (NULL != newList)
        {
            newList[*movements - 2] = currentMove;
            return newList;
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
                        ton     = listCenters[i]->ton;
                        minCost = currentCost;
                    }   
                }   
            }
        }
        newMove = setMove(newMove, origin, destiny, ton, minCost);
        return newMove;
    } 
    return NULL;
}

float getCurrentCost(Center* originCenter, int subsidy, int destinyDistance)
{
    if (NULL != originCenter) 
    {
        int originDistance = originCenter->distance;
        int ton            = originCenter->ton;
        int distanceE      = abs(originDistance-destinyDistance);
        float newCost      = (distanceE)*(ton - (ton/(float)(subsidy)));

        /*
            Este calculo obtiene costo, si es que dos centros estan a igual distancia desde el centro.
            int distanceXY     = sqrt(pow(originDistance, 2)+pow(destinyDistance, 2));
            float newCost      = (distanceXY)*(ton - (ton/(float)(subsidy)));
        */

        return newCost;
    }
    return -1;
}

void showListMove(Move** currentListMove, int movements)
{
    if (NULL != currentListMove && movements >= 0) 
    {
        int i = 0;
        for(i = 0; i < movements; i++)
        {
            printf("cost: %.2f\n", currentListMove[i]->cost);
            printf("origin: %d\n", currentListMove[i]->origin);
            printf("destiny: %d\n", currentListMove[i]->destiny);
            printf("ton: %d\n\n", currentListMove[i]->ton);
        }
    }
}

void freeListMove(Move** currentListMove, int movements)
{
    if (NULL != currentListMove) 
    {
        int i = 0;
        for(i = 0; i < movements; i++)
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
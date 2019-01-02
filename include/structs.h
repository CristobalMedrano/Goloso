#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef struct Project
{
    int numberCenters;
    int incinerators;
    int subsidy;
    struct Center** listCenters;

} Project;

typedef struct Center
{
    int distance;
    int ton;

} Center;


#endif
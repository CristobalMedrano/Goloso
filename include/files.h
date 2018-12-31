#ifndef _FILES_H
#define _FILES_H

/*
    Funciones de lectura.
    Read Functions.
*/
#define SUCCESS 0
#define ERROR_CLOSE -1
#define SAVED 1
#define ERROR 2

char* getFileName();
FILE* openFile(const char* fileName);
Centers* readFile(FILE* currentFile);
Centers* createCenters();
int* setGatheringCenters(int* currentList, int pos, int distance, int ton);
Centers* setNewCenters(Centers* currentCenters, int numberOfCenters, int incineratorsAvailable, int subsidy, int* gatheringCenters);
int closeFile(FILE* file, const char* fileName);
Centers* getCenters(const char* inputFile);

void freeCenters(Centers* centers);
//void saveFile(invHistory* solution);

#endif
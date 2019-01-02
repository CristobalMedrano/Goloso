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

FILE* openFile(const char* fileName);
Project* readFile(FILE* currentFile);
Project* createProject();
Center** createListCenters(int numberCenters);
Center* createCenter();
Center* setNewCenter(Center* currentCenter, int distance, int ton, int cost);
void showListCenters(Center** currentListCenters, int numberCenters);
Project* setNewProject(Project* currentProject, int numberCenters, int incinerators, int subsidy, Center** currentListCenters);
int closeFile(FILE* file, const char* fileName);
Project* getProject(const char* inputFile);
void freeProject(Project* project);
//void saveFile(invHistory* solution);

#endif
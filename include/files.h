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
int closeFile(FILE* file, const char* fileName);
Project* getProject(const char* inputFile);
//void saveFile(invHistory* solution);

#endif
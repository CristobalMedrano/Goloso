#ifndef _GOLOSO_H
#define _GOLOSO_H

#define SIN_INGRESO -1
#define GOLOSO 1
#define ABOUT 2
#define EXIT 3
#define START 2
#define YES 1
#define NO 0

void mainMenu(const char* inputFile, const char* outputFile);
void initProgram(const char* inputFile, const char* outputFile);
Move** goloso(Project* currentProject, int movements);
void printCurrent(Move* currentMove);

#endif
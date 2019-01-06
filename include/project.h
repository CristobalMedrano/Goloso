#ifndef _PROJECT_H
#define _PROJECT_H

#define YES 1
#define NO 0

Project* createProject();
Project* setNewProject(Project* currentProject, int numberCenters, int incinerators, int subsidy, Center** currentListCenters);
Center** createListCenters(int numberCenters);
Center* createCenter();
Center* setNewCenter(Center* currentCenter, int distance, int ton);
Project* updateProject(Project* currentProject, Move* currentMove);
Center** updatedListCenter(int numberCenters, Center** listCenters, Move* currentMove);
int moveEqualCenter(Move* move, Center* center);
void showProject(Project* currentProject);
void showListCenters(Center** currentListCenters, int numberCenters);
void freeProject(Project* project);
void freeListCenter(Center** currentListCenter, int numberCenters);
void freeCenter(Center* currentCenter);

#endif
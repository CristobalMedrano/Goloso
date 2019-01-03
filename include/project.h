#ifndef _PROJECT_H
#define _PROJECT_H

Project* createProject();
Project* setNewProject(Project* currentProject, int numberCenters, int incinerators, int subsidy, Center** currentListCenters);
Center** createListCenters(int numberCenters);
Center* createCenter();
Center* setNewCenter(Center* currentCenter, int distance, int ton, int cost);
Project* updateProject(Project* currentProject, Move* currentMove);
void showListCenters(Center** currentListCenters, int numberCenters);
void freeProject(Project* project);

#endif
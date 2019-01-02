#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <structs.h>
#include <goloso.h>
#include <menu.h>
#include <files.h>
#include <project.h>
#include <move.h>
#include <utilities.h>

/*
    Entrada: Nombre del archivo de entrada y nombre del archivo de salida
    Procedimiento: Inicia el menu de la aplicacion.
    Salida: Vacia

*/

void mainMenu(const char* inputFile, const char* outputFile)
{
    int option;
    do
    {
        option = SIN_INGRESO;
        menu(&option, 1, 3);
 
        switch(option)
        {
            case GOLOSO:
                initProgram(inputFile, outputFile);
                pressToContinue();
                break;
  
            case ABOUT:
                about();
                break;
 
            case EXIT:
                printf("Programa finalizado.\n");
                break;
        }

    }while(option != EXIT);
}

/*
    Entrada: Nombre del archivo de entrada y nombre del archivo de salida
    Procedimiento: Comienza la ejecucion del programa, lee los datos del archivo, 
                   utiliza goloso para obtener el menor coste y guarda
                   esos datos en otro archivo.
    Salida: Vacia
*/
void initProgram(const char* inputFile, const char* outputFile)
{
    // Obtiene los datos del archivo de entrada.
    Project* newProject = getProject(inputFile);
    
    if (NULL != newProject) 
    {

        Center* bestMinCostCenter = getMinCostCenterToMove(newProject);
        

        /*float coste1 = getCurrentCost(newProject->listCenters[0], subsidy, newProject->listCenters[1]->distance);
        float coste2 = getCurrentCost(newProject->listCenters[0], subsidy, newProject->listCenters[2]->distance);
        float coste3 = getCurrentCost(newProject->listCenters[0], subsidy, newProject->listCenters[3]->distance);
        printf("coste1: %.2f\n", coste1);
        printf("coste2: %.2f\n", coste2);
        printf("coste3: %.2f\n", coste3);
        float coste4 = getCurrentCost(newProject->listCenters[1], subsidy, newProject->listCenters[0]->distance);
        float coste5 = getCurrentCost(newProject->listCenters[1], subsidy, newProject->listCenters[2]->distance);
        float coste6 = getCurrentCost(newProject->listCenters[1], subsidy, newProject->listCenters[3]->distance);
        printf("coste4: %.2f\n", coste4);
        printf("coste5: %.2f\n", coste5);
        printf("coste6: %.2f\n", coste6);
        float coste7 = getCurrentCost(newProject->listCenters[2], subsidy, newProject->listCenters[0]->distance);
        float coste8 = getCurrentCost(newProject->listCenters[2], subsidy, newProject->listCenters[1]->distance);
        float coste9 = getCurrentCost(newProject->listCenters[2], subsidy, newProject->listCenters[3]->distance);
        printf("coste7: %.2f\n", coste7);
        printf("coste8: %.2f\n", coste8);
        printf("coste9: %.2f\n", coste9);
        float coste10 = getCurrentCost(newProject->listCenters[3], subsidy, newProject->listCenters[0]->distance);
        float coste11 = getCurrentCost(newProject->listCenters[3], subsidy, newProject->listCenters[1]->distance);
        float coste12 = getCurrentCost(newProject->listCenters[3], subsidy, newProject->listCenters[2]->distance);
        printf("coste10: %.2f\n", coste10);
        printf("coste11: %.2f\n", coste11);
        printf("coste12: %.2f\n", coste12);*/
    }    
    freeProject(newProject);
}

Center* getMinCostCenterToMove(Project* currentProject)
{
    int subsidy = currentProject->subsidy;
    int numberCenters = currentProject->numberCenters;
    int i = 0;
    int j = 0;
    Center** listCenters = currentProject->listCenters;
    float minCost = (float)INFINITY;
    for(i = 0; i < numberCenters; i++)
    {   
        for(j = 0; j < numberCenters; j++)
        {
            if (i != j) 
            {
                float currentCost = getCurrentCost(listCenters[i], subsidy, listCenters[j]->distance);

                if (minCost > currentCost) 
                {
                    minCost = currentCost;
                }
                
            }
            
        }
        
    }
    printf("min: %f", minCost);
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


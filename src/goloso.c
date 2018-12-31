#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <goloso.h>
#include <menu.h>
#include <files.h>
#include <utilities.h>

/*
    Entrada: Nombre del archivo de entrada y nombre del archivo de salida
    Procedimiento: Inicia el menu de la aplicacion.
    Salida: Vacia

*/

void mainMenuGoloso(const char* inputFile, const char* outputFile)
{
    int option;
    do
    {
        option = SIN_INGRESO;
        menu(&option, 1, 3);
 
        switch(option)
        {
            case GOLOSO:
                runGoloso(inputFile, outputFile);
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
void runGoloso(const char* inputFile, const char* outputFile)
{
    Centers* newCenters = getCenters(inputFile, outputFile);
    
    if (NULL != newCenters) 
    {
        /*
        printf("nCenters: %d\nInc: %d\nsub: %d\n", newCenters->numberOfCenters, newCenters->incineratorsAvailable, newCenters->subsidy);
    
        for(int i = 0; i < (newCenters->numberOfCenters)*2; i++)
        {
            printf("D: %d - T: %d\n", newCenters->gatheringCenters[i], newCenters->gatheringCenters[i+1]);
            i++;
        }
        */
        // Read file..
    }    
}
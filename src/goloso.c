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
        printf("Iniciando solucion...\n");
        #ifdef DEBUG
            showProject(newProject);
        #endif

        int numberCenters   = newProject->numberCenters;
        int incinerators    = newProject->incinerators;
        int movements       = numberCenters - incinerators;
        
        if (movements > 0) 
        {
            Move** solution = goloso(newProject, movements);
            
            if (NULL != solution) 
            {
                printf("Solucion encontrada.\n");
               
                #ifdef DEBUG
                    showListMove(solution, movements);
                    showProject(newProject);
                #endif
                
                // guardo
                saveFile(solution, movements, newProject, outputFile);
                freeListMove(solution, movements);
            }           
        }
        else
        {
           saveFile(NULL, 0, newProject, outputFile);    
        }
    }    
    freeProject(newProject);
}

/*
    Entrada: Estructura del tipo Project que contiene los datos del mapa de recoleccion, 
            entero con los movimientos a realizar.
    
    Procedimiento: Se selecciona el mejor movimiento segun el menor coste de traslado y
            se anade a la lista de movimientos, luego se quita el centro trasladado del plano de 
            recoleccion actual( currentProject ) y se actualiza el mapa de recoleccion(Project) con
            el nuevo centro actualizado (el centro que recibio la carga).
    
    Salida: Lista que contiene todos los movimientos de minimo coste realizados en la recoleccion.

*/
Move** goloso(Project* currentProject, int movements)
{
    Move** newListMove  = createListMove(movements);
    
    int i = 0;
    while(currentProject->numberCenters > currentProject->incinerators)
    {
        if (NULL != newListMove)
        {
            Move* minMove = getMinMove(currentProject);
            
            if (NULL != minMove) 
            {
                printCurrent(minMove);
                // agrega el movimiento realizado a la lista de movimientos.
                newListMove[i] = setMove(newListMove[i], minMove->origin, minMove->destiny, minMove->ton, minMove->cost);
                freeMove(minMove);
                
                // updateProject quita el centro de inicio y actualiza el centro de llegada
                currentProject = updateProject(currentProject, newListMove[i]);
            }
        }
        i++;
    }
    return newListMove;
}

// A partir del tipo de dato Move (ver en structs.h) muestra los datos de aquel puntero. 
//    - origen de la carga (centro de origen) origin
//    - destino de la carga (centro de destino) destiny
//    - coste de transporte (cost)
//    - toneladas a mover (ton)
void printCurrent(Move* currentMove)
{
    #ifdef DEBUG
        printf("Mover desde %d -> %d\n", currentMove->origin, currentMove->destiny);
        printf("Coste de traslado: %.2f\n", currentMove->cost);
        printf("Toneladas a mover: %d\n", currentMove->ton );
        pressToContinue();
    #endif
}







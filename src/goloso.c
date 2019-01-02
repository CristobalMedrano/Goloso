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
        // Matriz de adyacencia
        
        // Read file..
    }    
    freeProject(newProject);
}
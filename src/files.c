#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <files.h>
#include <project.h>
#include <utilities.h>

// Abre un archivo.
FILE* openFile(const char* fileName)
{
    FILE* currentFile = fopen(fileName, "rb");
    if(NULL != currentFile)
    {
        #ifdef DEBUG
            printf("Archivo '%s' abierto\n", fileName);
        #endif
        return currentFile;
    }
    printf("Error: El archivo '%s' no existe.\n", fileName);
    return NULL;
}

Project* readFile(FILE* currentFile)
{
    if(NULL != currentFile)
    {
        int numberCenters   = 0;
        int incinerators    = 0;
        int subsidy         = 0;

        fscanf(currentFile, "%d", &numberCenters);
        fscanf(currentFile, "%d", &incinerators);
        fscanf(currentFile, "%d", &subsidy);

        Project* newProject     = createProject();
        Center** newListCenters = createListCenters(numberCenters);

        if (NULL != newProject && NULL != newListCenters) 
        {
            int distance    = 0;
            int ton         = 0;
            int pos         = 0;

            while(pos < numberCenters)
            {
                fscanf(currentFile, "%d", &distance);
                fscanf(currentFile, "%d", &ton);
                newListCenters[pos] = setNewCenter(newListCenters[pos], distance, ton);
                pos = pos + 1;
            }
            #ifdef DEBUG
                showListCenters(newListCenters, numberCenters);
            #endif

            newProject = setNewProject(newProject, numberCenters, incinerators, subsidy, newListCenters);
            return newProject;
        }
    }
    return NULL;
}

/*
    Entrada: Puntero de tipo FILE donde esta el archivo, nombre del archivo
    Procedimiento: Cierra el archivo.
    Salida: 0 si fue correcto, 1 si fue incorrecto.
*/
int closeFile(FILE* file, const char* fileName)
{
    if (NULL != file && NULL != fileName) 
    {
        if(0 == fclose(file))
        {
            #ifdef DEBUG
                printf("Archivo '%s' cerrado.\n", fileName);
            #endif
            return SUCCESS;
        }
    }
    printf("Error al cerrar el archivo '%s'.\n", fileName);
    return ERROR_CLOSE;
}
/*
    Entrada: Puntero al nombre del archivo.
    Procedimiento: Inicia la lectura del archivo
    Salida: Estructura que contiene el numero de centros, incineradores, subdidio y lista de centros.
            Nulo si no fue posible leer el archivo.
*/
Project* getProject(const char* inputFile)
{
    if(NULL != inputFile)
    {
        FILE* currentFile = openFile(inputFile);
        if(NULL != currentFile)
        {
            Project* newProject = readFile(currentFile);
            if(NULL != newProject)
            {
                int status = closeFile(currentFile, inputFile);
                if(SUCCESS == status)
                {
                    printf("\nArchivo '%s' cargado correctamente.\n", inputFile);
                    return newProject;
                }
                #ifdef DEBUG
                    printf("No es posible cerrar el archivo '%s'\n", inputFile);
                #endif
                freeProject(newProject);
            }
            #ifdef DEBUG
                printf("No es posible leer un listado de inversiones\n");
            #endif
        }
        #ifdef DEBUG
            printf("No es posible abrir el archivo '%s'\n", inputFile);
        #endif
    }
    return NULL;
}


// Guarda los datos obtenidos previamente en un archivo de salida
void saveFile(Move** solution, int movements, Project* finalProject, const char* outputFile)
{
    if (NULL != solution) 
    {
        FILE* newFile = fopen("Salida.out", "wb");

        if (NULL != newFile) 
        {
            float cost = 0;
            if (movements > 0) 
            {
                int i = 0;
                for(i = 0; i < movements; i++)
                {
                    fprintf(newFile, "%d->%d\n", solution[i]->origin, solution[i]->destiny);
                    cost = solution[i]->cost + cost;
                }
            }
            int j = 0;
            
            for(j = 0; j < finalProject->numberCenters; j++)
            {
                fprintf(newFile, "Centro %d: %d toneladas\n", finalProject->listCenters[j]->distance,
                                                            finalProject->listCenters[j]->ton);
            }
            
            fprintf(newFile, "Costo: %.2f", cost);
            printf("Archivo '%s' creado correctamente.\n", outputFile);      
            closeFile(newFile, outputFile); 
        } 
    }
}
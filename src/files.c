#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <files.h>
#include <utilities.h>

// Obtiene el nombre del archivo ingresado por pantalla.
char* getFileName()
{
    printf("Ingrese el nombre del archivo: ");
    char    file[256];
	char*   filename = (char*)malloc(sizeof(char)*256);
    
    if (NULL != filename) 
    {
        fflush(stdin);
        scanf("%s", file);
        fflush(stdin);
        strcpy(filename, file);
        return filename;
    }    
    printf("Memoria insuficiente: getFileName()\n");
    printf("Error: readfile.c\n");
    return NULL;
}

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

// Lee el archivo de entrada y guarda los datos en la estructura inv.(ver structs.h para mas detalles)
// El formato a leer es: Capital disponible, numero de inversiones y cada inversion con su coste/utilidad.
Centers* readFile(FILE* currentFile)
{
    if(NULL != currentFile)
    {
        int numberOfCenters       = 0;
        int incineratorsAvailable = 0;
        int subsidy               = 0;

        fscanf(currentFile, "%d", &numberOfCenters);
        fscanf(currentFile, "%d", &incineratorsAvailable);
        fscanf(currentFile, "%d", &subsidy);

        Centers* newCenters     = createCenters();
        int* gatheringCenters   = createList(numberOfCenters*2);

        if (NULL != gatheringCenters && NULL != newCenters) 
        {
            int distance    = 0;
            int ton         = 0;
            int count       = 0;

            while(count < numberOfCenters*2)
            {
                fscanf(currentFile, "%d", &distance);
                fscanf(currentFile, "%d", &ton);
                gatheringCenters = setGatheringCenters(gatheringCenters, count, distance, ton);
                count = count + 2;
            }
            #ifdef DEBUG
                showList(gatheringCenters, numberOfCenters*2);
            #endif

            newCenters = setNewCenters(newCenters, numberOfCenters, incineratorsAvailable, subsidy, gatheringCenters);
            return newCenters;
        }
    }
    return NULL;
}

// Inicia un puntero de inversion.
Centers* createCenters()
{
    Centers* newCenters = (Centers*)malloc(sizeof(Centers));
    if(NULL != newCenters)
    {
        newCenters->numberOfCenters         = 0;
        newCenters->incineratorsAvailable   = 0;
        newCenters->subsidy                 = 0;
        newCenters->gatheringCenters        = NULL;
        return newCenters;
    }
    printf("Memoria insuficiente: createCenters()\n");
    printf("Error: files.c\n");
    return NULL;
}

int* setGatheringCenters(int* currentList, int pos, int distance, int ton)
{
    if (NULL != currentList && pos >= 0) 
    {
        currentList[pos]        = distance;
        currentList[pos + 1]    = ton;
        return currentList;
    }
    return currentList;
}

// Guarda los nuevos centros.
Centers* setNewCenters(Centers* currentCenters, int numberOfCenters, int incineratorsAvailable, int subsidy, int* gatheringCenters)
{
    if (NULL != currentCenters) 
    {
        currentCenters->numberOfCenters         = numberOfCenters;
        currentCenters->incineratorsAvailable   = incineratorsAvailable;
        currentCenters->subsidy                 = subsidy;
        currentCenters->gatheringCenters        = gatheringCenters;
        return currentCenters;
    }
    return currentCenters;
}

// Cierra un archivo.
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
    Entrada: Vacia
    Procedimiento: Inicia la lectura del archivo
    Salida: Estructura de datos que contiene el capital inicial,
            el numero de inversiones y la lista de inversiones a
            realizar con sus respectivas utilidades.
*/
Centers* getCenters(const char* inputFile)
{
    if(NULL != inputFile)
    {
        FILE* currentFile = openFile(inputFile);
        if(NULL != currentFile)
        {
            Centers* newCenters = readFile(currentFile);
            if(NULL != newCenters)
            {
                int status = closeFile(currentFile, inputFile);
                if(SUCCESS == status)
                {
                    printf("\nArchivo cargado correctamente.\n");
                    return newCenters;
                }
                #ifdef DEBUG
                    printf("No es posible cerrar el archivo '%s'\n", inputFile);
                #endif
                freeCenters(newCenters);
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

// Libera la memoria usada 
void freeCenters(Centers* centers)
{
    if (NULL != centers) 
    {
        if (NULL != centers->gatheringCenters) 
        {
            free(centers->gatheringCenters);
        }
        free(centers);
    }
}

// Guarda los datos obtenidos previamente por invHistory en un archivo de salida
// El formato es: Capital usado - Utilidad total obtenida y la lista de inversiones que se realizaron.
/*void saveFile(invHistory* solution)
{
    if (NULL != solution) 
    {
        FILE* newFile = fopen("Salida.out", "wb");

        if (NULL != newFile) 
        {
            fprintf(newFile, "%d ", solution->capital);
            fprintf(newFile, "%d\n", solution->utility);
            
            
            if (NULL != solution->details) 
            {
                int i = 0;
                for(i = 0; i < solution->length; i++)
                {
                    fprintf(newFile, "%d\n", solution->details[i]);
                }
            }
            else
            {
                fprintf(newFile, "No es posible invertir.");
            }
            printf("Archivo solucion creado correctamente.\n");      
            closeFile(newFile, "Salida.out"); 
        } 
    }
}*/
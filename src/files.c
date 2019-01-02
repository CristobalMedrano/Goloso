#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <files.h>
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
                newListCenters[pos] = setNewCenter(newListCenters[pos], distance, ton, 0);
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

Project* createProject()
{
    Project* newProject = (Project*)malloc(sizeof(Project));
    if(NULL != newProject)
    {
        newProject->numberCenters   = 0;
        newProject->incinerators    = 0;
        newProject->subsidy         = 0;
        newProject->listCenters     = NULL;
        return newProject;
    }
    printf("Memoria insuficiente: createProject()\n");
    printf("Error: files.c\n");
    return NULL;
}

/*
    Entrada: cantidad de centros de acopio.
    Procedimiento: crea una lista vacia de centros de acopio.
    Salida: lista preparada para recibir datos de los centros de acopio.
*/
Center** createListCenters(int numberCenters)
{
    Center** newListCenters = (Center**)malloc(sizeof(Center*)*(numberCenters));
    
    if (NULL != newListCenters) 
    {
        int i = 0;
        for(i = 0; i < numberCenters; i++)
        {               
            Center* newCenter = createCenter();
            
            if (NULL == newCenter) 
            {
                printf("Memoria insuficiente: createListCenters()\n");
                printf("Error: files.c\n");
                return NULL;
            }
            
            newListCenters[i] = newCenter;
        }
        return newListCenters;
    }
    printf("Memoria insuficiente: createListCenters()\n");
    printf("Error: files.c\n");
    return NULL;
}

/*
    Entrada: vacia
    Procedimiento: Crea un nuevo centro
    Salida: El centro ya creado.
*/
Center* createCenter()
{
    Center* newCenter = (Center*)malloc(sizeof(Center));
    if (NULL != newCenter) 
    {
        newCenter->distance = 0;
        newCenter->ton      = 0;
        newCenter->cost     = 0;
        return newCenter;
    }
    printf("Memoria insuficiente: createCenter()\n");
    printf("Error: files.c\n");
    return NULL;
}

/*
    Entrada: centro actual, distancia y toneladas
    Procedimiento: guarda los datos en el centro actual
    Salida: el centro actualizado, nulo si no fue posible actualizar.
*/
Center* setNewCenter(Center* currentCenter, int distance, int ton, int cost)
{   
    if (NULL != currentCenter) 
    {
        currentCenter->distance = distance;
        currentCenter->ton      = ton;
        currentCenter->cost     = cost;
        return currentCenter;    
    }
    return NULL;   
}

/*
    Entrada: lista de centros, cantidad de centros.
    Procedimiento: Muestra los datos almacenados de cada centro.
*/
void showListCenters(Center** currentListCenters, int numberCenters)
{
    if (NULL != currentListCenters) 
    {
        int i = 0;
        for(i = 0; i < numberCenters; i++)
        {
            printf("Center: %d, Distance: %d, Ton: %d\n",
                i, currentListCenters[i]->distance, currentListCenters[i]->ton);
        }
        
    }
    
}

/*
    Entrada: puntero al proyecto actual, numero de centros, incineradores disponibles, subsidio, lista de centros
    Procedimiento: guarda los datos en la estructura Project.
    Salida: puntero a la estructura Project con los datos del proyecto en curso. Nulo si no fue posible guardar.
*/
Project* setNewProject(Project* currentProject, int numberCenters, int incinerators, int subsidy, Center** currentListCenters)
{
    if (NULL != currentProject) 
    {
        currentProject->numberCenters   = numberCenters;
        currentProject->incinerators    = incinerators;
        currentProject->subsidy         = subsidy;
        currentProject->listCenters     = currentListCenters;
        return currentProject;
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
                    printf("\nArchivo cargado correctamente.\n");
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

// Libera la memoria usada 
void freeProject(Project* project)
{
    if (NULL != project) 
    {
        if (NULL != project->listCenters) 
        {
            int i = 0;
            for(i = 0; i < project->numberCenters; i++)
            {
                free(project->listCenters[i]);
            }
            free(project->listCenters);
        }
        free(project);
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
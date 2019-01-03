#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <project.h>

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

Project* updateProject(Project* currentProject, Move* currentMove)
{
    if (NULL != currentProject && NULL != currentMove) 
    {
        // Debe quitar el movimiento realizado.
        // Debe añadir el nuevo movimiento.
        return currentProject;
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
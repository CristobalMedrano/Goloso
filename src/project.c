#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <project.h>

/*
    Crea un tipo de dato project.
*/
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
                printf("Error: project.c\n");
                return NULL;
            }
            
            newListCenters[i] = newCenter;
        }
        return newListCenters;
    }
    printf("Memoria insuficiente: createListCenters()\n");
    printf("Error: project.c\n");
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
Center* setNewCenter(Center* currentCenter, int distance, int ton)
{   
    if (NULL != currentCenter) 
    {
        currentCenter->distance = distance;
        currentCenter->ton      = ton;
        return currentCenter;    
    }
    return NULL;   
}

/*
    Entrada: tipo de dato project que contiene los datos actuales del plan de limpieza(ver en structs.h)
             Movimiento actual realizado.
    Procedimiento: Quita el centro que fue trasladado, actualiza la cantidad de centros disponibles en project y anade
                   o actualiza el centro de llegada.
    Salida: tipo de dato project con los nuevos centros y datos actualizados.  
*/
Project* updateProject(Project* currentProject, Move* currentMove)
{
    if (NULL != currentProject && NULL != currentMove) 
    {
        Center** newListCenter = updatedListCenter(currentProject->numberCenters, currentProject->listCenters, currentMove);

        if (NULL != newListCenter) 
        {
            freeListCenter(currentProject->listCenters, currentProject->numberCenters);
            currentProject->numberCenters = currentProject->numberCenters - 1;  
            currentProject->listCenters = newListCenter;
            return currentProject;
        }
    }   
    return NULL; 
}

// Funcion encargada de quitar el centro de inicio y actualizar el centro de llegada.
// devuelve la lista de centros actualizada.
Center** updatedListCenter(int numberCenters, Center** listCenters, Move* currentMove)
{
    Center** newListCenter = createListCenters(numberCenters - 1);
    if (NULL != listCenters && NULL != newListCenter) 
    {
        int i = 0;
        int j = 0;
        for(i = 0; i < numberCenters; i++)
        {
            if (moveEqualCenter(currentMove, listCenters[i]) == NO) 
            {
                newListCenter[j] = setNewCenter(newListCenter[j], listCenters[i]->distance, listCenters[i]->ton);
                if (newListCenter[j]->distance == currentMove->destiny) 
                {
                    newListCenter[j]->ton = newListCenter[j]->ton + currentMove->ton;
                }
                j++;
            }
        }
        return newListCenter;
    }
    return NULL;
}

// Funcion que verifica si un centro es igual a un movimiento. (sirve para eliminar el centro trasladado)
int moveEqualCenter(Move* move, Center* center)
{
    if (NULL != move && NULL != center) 
    {
        if ((move->origin == center->distance) && (move->ton == center->ton)) 
        {
            return YES;
        }   
    }
    return NO;
}

void showProject(Project* currentProject)
{
    if (NULL != currentProject) 
    {
        printf("Numero de centros: %d\n", currentProject->numberCenters);
        printf("Incineradores: %d\n", currentProject->incinerators);
        printf("Subsidio: %d\n", currentProject->subsidy);
        showListCenters(currentProject->listCenters, currentProject->numberCenters);
    }
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
        freeListCenter(project->listCenters, project->numberCenters);
        free(project);
    }
}

void freeListCenter(Center** currentListCenter, int numberCenters)
{
    if (NULL != currentListCenter) 
    {
        int i = 0;
        for(i = 0; i < numberCenters; i++)
        {
            freeCenter(currentListCenter[i]);
        }
        free(currentListCenter);
    }
}

void freeCenter(Center* currentCenter)
{
    if (NULL != currentCenter) 
    {
        free(currentCenter);
    }
}
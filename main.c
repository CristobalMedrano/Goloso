#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <goloso.h>

// Funcion principal.
int main(int argc, char const *argv[])
{
    if (3 == argc) 
    {
        mainMenu(argv[1], argv[2]);
    }
    else
    {
        errorMessage();
    }
    return 0;
}

void errorMessage()
{
    printf("\n-- ERROR --\nDebe ingresar el nombre del archivo de entrada y archivo de salida cumpliendo el siguiente formato.\n");

    #ifdef DEBUG
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            printf("Ejemplo: './debug_goloso.out archivo_entrada archivo_salida'");
        #endif

        #if defined(_WIN32) || defined(_WIN64)
            printf("Ejemplo: debug_goloso.exe archivo_entrada archivo_salida");
        #endif
    #endif
    
    #ifndef DEBUG
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            printf("Ejemplo: './goloso.out archivo_entrada archivo_salida'");
        #endif

        #if defined(_WIN32) || defined(_WIN64)
            printf("Ejemplo: goloso.exe archivo_entrada archivo_salida");
        #endif
    #endif
    printf("\n\n");
}

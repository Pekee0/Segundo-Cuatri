#include <stdio.h>
#include <stdlib.h>
#include "Persona.h"
 #include <string.h>
 #include "string.h"
persona cargarPersona()
{
    persona dato;

    printf("Ingrese el legajo de la persona:\n");
    fflush(stdin);
    scanf("%d",&dato.legajo);

    printf("Ingrese el nombre de la persona: \n");
    fflush(stdin);
    gets(dato.nombre);

    printf("Ingrese la edad de la persona:\n");
    fflush(stdin);
    scanf("%d",&dato.edad);

    return dato;
}

void mostrarPersona(persona dato)
{
    printf("---------------------------------\n");
    printf("Legajo: %d\n",dato.legajo);
    printf("Nombre: %s\n",dato.nombre);
    printf("Edad: %d\n",dato.edad);
    printf("---------------------------------\n");
}



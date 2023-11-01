#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define test printf("hola\n");


typedef struct {
   int nota;
   int legajo;
   char nombreApe[40];
   char materia[40];
   int idMateria;
} registroArchivo;

typedef struct {  /// struct que con el que trabaja la lista
   int nota;
   int legajo;
   char nombreApe[40];
} notaAlumno;

typedef struct _nodo { /// struct de la lista
   notaAlumno dato;
   struct _nodo *siguiente;
} nodo;

typedef struct { /// struct del arreglo que contiene el primer nodo de la lista
    int idMateria;
    char materia[40];
    nodo * listaDeNotas;
} celda;


int main()
{
    printf("Hello world!\n");
    return 0;
}


int cargarNotas (celda adl[], int dimension)
{
    int nota = 0;
    char alumno [20];
    char materia[30];
    char seguir = 's';

    int validos = 0;


    while (seguir == 's' && validos < dimension)
    {
        printf("Ingrese El nombre del alumno:\n");
        fflush(stdin);
        gets(alumno);

        printf("Ingrese el nombre de la materia: \n");
        fflush(stdin);
        gets(materia);

        printf("Ingresee la nota del alumno\n");
        scanf("%d",&nota);

        validos = alta(adl,materia,alumno,nota,validos);
    }
}

int alta(celda adl[], char materia[],char alumno[],int nota,int validos)
{

}

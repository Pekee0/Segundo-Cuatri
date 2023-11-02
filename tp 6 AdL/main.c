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

notaAlumno cargarAlumno (notaAlumno alumno);

int main()
{

    notaAlumno alu;

    alu = cargarAlumno(alu);

    return 0;
}

notaAlumno cargarAlumno (notaAlumno alumno)
{

    printf("Ingrese el legajo: \n");
    scanf("%d",&alumno.legajo);

    printf("Ingrese el nombre del alumno; \n");
    fflush(stdin);
    gets(alumno.nombreApe);

    printf("Ingrese la nota del alumno.\n");
    scanf ("%d",&alumno.nota);

    return alumno;
}


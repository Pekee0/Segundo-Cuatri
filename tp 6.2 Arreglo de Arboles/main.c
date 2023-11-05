#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define test printf("hola.\n");

typedef struct {
   char animal[30];
   int cant;
   int habitat;
   int idEspecie;
   char especie[20];
} registroArchivo;

typedef struct
{
   animal dato;
   struct nodoArbol * izq;
   struct nodoArbol * der;
} nodoArbol;

typedef struct {
      char nombreAnimal [30];
	int cantidad;
	int habitat;
// 1 - selva, 2- savana, 3-bosque, 4-mar
} animal;
typedef struct
{
   int idEspecie;
   char especie [20];
 	 // "Mamiferos", "Aves"
       // "Reptiles", "Peces",”Anfibios”
   nodoArbol * arbolDeAnimales;
} celdaEspecie;





int main()
{


    return 0;
}

/// FUNCIONES DEL ARREGLO

/// FUNCIONES DEL ARBOL


/// FUNCIONES DEL ARCHIVO
int pasarArchivoToAdA (celdaEspecie AdA[], int validos, int dimension, char nombreArchivo[])
{
    FILE * archivo = fopen(nombreArchivo, "rb");
    registroArchivo aux;

    if(archivo)
    {
      while (fread(&aux,sizeof(registroArchivo),1,archivo) > 0)
      {

      }
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}



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
    char nombreArchivo[] = {"animales.dat"};


    return 0;
}

/// FUNCIONES DEL ARREGLO
int alta(celdaEspecie ADA[], animal ani,celdaEspecie especie, int validos)
{
    nodoArbol * aux = crearNodo(ani);

    int pos= BuscarPosEspecie(ADA,especie.idEspecie, validos);

    if(pos == -1)
    {
        validos = agregarEspecie(ADA[],especie,validos);
        pos = validos -1;
    }

    ADA[pos].arbolDeAnimales = insertar(ADA[pos].arbolDeAnimales,aux);

    return validos;
}

int BuscarPosEspecie(celdaEspecie ADA[],int idEspecie,validos)
{
    int rta = -1;
    int i = 0;

    while(i<validos && rta == -1)
    {
        if(ADA[i].idEspecie == idEspecie)
        {
            rta = i;
        }
        i++;
    }

    return rta;
}

int agregarEspecie(celdaEspecie ADA[], celdaEspecie Especie, int validos)
{
    strcpy(ADA[validos].especie,Especie.especie);
    ADA[validos].idEspecie = Especie.idEspecie;

    ADA[validos].arbolDeAnimales = inicArbol();

    validos++;

    return validos;
}

/// FUNCIONES DEL ARBOL
nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * crearNodo (animal dato)
{
    nodoArbol * aux = (nodoArbol*)malloc(sizeof(nodoArbol));

    aux->dato = dato;
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

nodoArbol * insertar(nodoArbol * raiz, nodoArbol * nuevo)
{
    if(raiz == NULL)
    {
        raiz = crearNodo(nuevo->dato);
    }
    else
    {
        if(raiz->dato.habitat <= nuevo->dato.habitat)
        {
            raiz->der = insertar(raiz->der,nuevo);
        }
        else
        {
            raiz->izq = insertar(raiz->izq,nuevo);
        }
    }

    return raiz;
}

/// FUNCIONES DEL ARCHIVO
int pasarArchivoToAdA (celdaEspecie AdA[], int validos, char nombreArchivo[])
{
    FILE * archivo = fopen(nombreArchivo, "rb");
    registroArchivo aux;
    animal aniAux;
    celdaEspecie AdAUx;

    if(archivo)
    {
      while (fread(&aux,sizeof(registroArchivo),1,archivo) > 0)
      {
        aniAux = copiarDeArchivoAnimal(aux);
        AdAUx = CopiarDeArchivoCelda(aux);

        validos = alta(AdA,aniAux,AdAUx,validos);
      }

      fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

    return validos;
}

animal copiarDeArchivoAnimal(registroArchivo dato)
{
    animal aux;

    strcpy(aux.nombreAnimal,dato.animal);
    aux.cantidad = dato.cant;
    aux.habitat = dato.habitat;

    return aux;
}

celdaEspecie CopiarDeArchivoCelda(registroArchivo dato)
{
    celdaEspecie aux;

    strcpy(aux.especie,dato.especie);
    aux.idEspecie = dato.idEspecie;

    return aux;
}





#include <stdio.h>
#include <stdlib.h>
#include "arboles.h"
#include <string.h>
#include "arboles.h"
#include "Persona.h"
nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * crearNodoArbol (persona dato)
{
    nodoArbol * aux = (nodoArbol*)malloc(sizeof(nodoArbol));

    aux->dato = dato;

    /*->dato.legajo = dato.legajo;
    aux->dato.edad = dato.edad;
    strcpy(aux->dato.nombre,dato.nombre);*/

    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

nodoArbol * buscarLegajo (nodoArbol * Arbol, int legajo)
{
    nodoArbol * rta;

    if(Arbol != NULL)
    {
      if(Arbol->dato.legajo == legajo)
      {
        rta = Arbol;
      }
      else
      {
          if (legajo > Arbol->dato.legajo)
          {
              rta = buscarLegajo(Arbol->der,legajo);
          }
          else
          {
             rta = buscarLegajo(Arbol->izq,legajo);
          }
      }
    }

    return rta;
}

nodoArbol * insertarLegajo (nodoArbol * arbol, nodoArbol * nuevo)
{
    if(arbol == NULL)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->dato.legajo >= arbol->dato.legajo)
        {
            arbol->der = insertarLegajo(arbol->der,nuevo);
        }
        else
        {
            arbol->izq = insertarLegajo(arbol->izq,nuevo);
        }
    }

    return arbol;
}

void mostrarPreOrder(nodoArbol * arbol)
{
    if(arbol!=NULL)
    {
        mostrarPersona(arbol->dato);
        mostrarPreOrder(arbol->izq);
        mostrarPreOrder(arbol->der);

    }
}

void mostrarInOrder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        mostrarInOrder(arbol->izq);
        mostrarPersona(arbol->dato);
        mostrarInOrder(arbol->der);

    }
}

void mostrarPosOrder(nodoArbol * arbol)
{
    if(arbol!=NULL)
    {
        mostrarPosOrder(arbol->izq);
        mostrarPosOrder(arbol->der);
        mostrarPersona(arbol->dato);
    }
}

int CalcularAltura (nodoArbol * arbol)
{
    int total = 0;

    if (arbol != NULL)
    {
        total = CalcularAltura(arbol->izq) + 1;
        total = CalcularAltura(arbol->der) +1 ;
    }

    return total;
}



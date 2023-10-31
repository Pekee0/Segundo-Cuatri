#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include "Persona.h"

typedef struct nodoArbol {
     persona dato;
     struct nodoArbol * izq;
     struct nodoArbol * der;
} nodoArbol;

nodoArbol * inicArbol();
nodoArbol * crearNodoArbol (persona dato);
nodoArbol * buscarLegajo (nodoArbol * Arbol, int legajo);
nodoArbol * insertarLegajo (nodoArbol * arbol, nodoArbol * nuevo);
void mostrarPreOrder(nodoArbol * arbol);
void mostrarInOrder(nodoArbol * arbol);
void mostrarPosOrder(nodoArbol * arbol);
int CalcularAltura (nodoArbol * arbol);
#endif // ARBOLES_H_INCLUDED

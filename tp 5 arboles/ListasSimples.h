#ifndef LISTASSIMPLES_H_INCLUDED
#define LISTASSIMPLES_H_INCLUDED
#include "Persona.h"



typedef struct nodo
{
    persona dato;
    struct nodo * sig;
}nodo;


nodo * iniclista();
nodo * crearNodo (persona dato);
nodo * agregarPpio (nodo * lista, nodo * nuevoNodo);
int buscarElementoEnLista (nodo * lista, char dato[]);
void mostrarLista(nodo * lista);
void FusionarListas (nodo * lista1, nodo * lista2, nodo ** listaFinal);
void invertirLista(nodo ** lista);
nodo * buscarUltimo(nodo * lista);
nodo * agregarEnOrden (nodo * lista, nodo * nuevo);
nodo * borrarNodo(nodo * lista, char nombre[20]);
persona retornarPrimerDato (nodo * lista);
#endif // LISTASSIMPLES_H_INCLUDED

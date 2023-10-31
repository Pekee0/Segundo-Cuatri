#include "ListasSimples.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Persona.h"
nodo * iniclista()
{
    return NULL;
}

nodo * crearNodo (persona dato)
{
    nodo * aux = (nodo*) malloc(sizeof(nodo));
    aux->dato.edad = dato.edad;
    aux->dato.legajo = dato.legajo;
    strcpy(aux->dato.nombre,dato.nombre);

    aux->sig = NULL;

    return aux;
}

nodo * agregarPpio (nodo * lista, nodo * nuevoNodo) {
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
return lista;
}



nodo * agregarEnOrden (nodo * lista, nodo * nuevo)
{
    if (lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        if(strcmp(nuevo->dato.nombre,lista->dato.nombre) <0)
        {
            lista = agregarPpio(lista,nuevo);
        }
        else
        {
            nodo * ante = lista;
            nodo * seg = lista->sig;

            while(seg != NULL && strcmp(nuevo->dato.nombre,seg->dato.nombre)>0)
            {
                ante = seg;
                seg = seg->sig;
            }

            nuevo->sig = seg;
            ante->sig = nuevo;
        }
    }
    return lista;
}

void mostrarLista(nodo * lista)
{
     nodo * seg = lista;

    while(seg != NULL)
    {
        mostrarPersona(seg->dato);
        seg = seg->sig;
    }
}

int buscarElementoEnLista (nodo * lista, char dato[])
{
    int flag = 0;
    if(lista != NULL){
        nodo * seg = lista;
        while (seg->sig != NULL && flag == 0)
        {
            if(strcmp(seg->dato.nombre,dato) == 0)
            {
                flag = 1;
            }
            else
            {
                seg  = seg->sig;
            }

        }
    }
    return flag ;
}

void FusionarListas (nodo * lista1, nodo * lista2, nodo ** listaFinal)
{

    if (lista1 !=NULL && lista2 != NULL)
    {
        if(strcmp (lista1->dato.nombre,lista2->dato.nombre)>0)
        {
            *listaFinal = agregarEnOrden(*listaFinal,lista1);
        }
        else
        {
            *listaFinal = agregarEnOrden(*listaFinal,lista2);
        }
    }

}

void invertirLista(nodo ** lista)
{
    nodo * prev = NULL;
    nodo * curr = *lista;

    while (curr != NULL)
    {
        nodo * next = curr->sig;

        curr->sig = prev;

        prev = curr;
        curr = next;
    }

    *lista = prev;
}


nodo * buscarUltimo(nodo * lista)
 {
   nodo * seg = lista;

   if(seg != NULL)
   {
       while(seg->sig != NULL)
        {
         seg = seg->sig;
        }
   }

    return seg;
 }

 nodo * borrarNodo(nodo * lista, char nombre[20]) {
   nodo * seg;
   nodo * ante; //apunta al nodo anterior que seg.
   if((lista != NULL) && (strcmp(nombre, lista->dato.nombre)==0 )) {

      nodo * aux = lista;
      lista = lista->sig; //salteo el primer nodo.
      free(aux);                //elimino el primer nodo.
   }else {
      seg = lista;
      while((seg != NULL) && (strcmp(nombre, seg->dato.nombre)!=0 )) {
         ante = seg;           //adelanto una posición la variable ante.
         seg = seg->sig; //avanzo al siguiente nodo.
      }
      //en este punto tengo en la variable ante la dirección de
      //memoria del nodo anterior al buscado, y en la variable seg,
      //la dirección de memoria del nodo que quiero borrar.
      if(seg!=NULL) {
         ante->sig = seg->sig;
         //salteo el nodo que quiero eliminar.
         free(seg);
         //elimino el nodo.
      }
   }
   return lista;
}

persona retornarPrimerDato (nodo * lista)
{
    if (lista)
    return lista->dato;
}



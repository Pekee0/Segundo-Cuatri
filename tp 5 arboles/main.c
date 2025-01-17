#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arboles.h"
#include "ListasSimples.h"

#define test printf("hola\n");
nodoArbol * cargarArbol(nodoArbol * arbol);
nodo * arbolToLista(nodoArbol * arbol, nodo * lista);
nodoArbol * buscarPorNombre (nodoArbol * arbol, char nombre[]);
int main()
{
    /// EJERCICIO 1
    nodoArbol * arbol;
    arbol = inicArbol();
    arbol = cargarArbol(arbol);

    /// EJERCICO 2
    mostrarInOrder(arbol);

    /// EJERCICIO 3
    nodo * lista;
    lista = iniclista();

    lista = arbolToLista(arbol,lista);

    printf("la lista:\n");
    mostrarLista(lista);
    /// EJERCICIO 4
    int legajo = 0;

    printf("Ingrese el legajo que desea buscar.\n");
    scanf("%d",&legajo);

    nodoArbol * aux;

    aux = buscarLegajo(arbol,legajo);

    if(aux->dato.legajo == legajo)
    {
        printf("Aqui esta su informacion.\n");
        mostrarPersona(aux->dato);
    }
    else
        printf("No existe.\n");


    /// EJERCICIO 5
     nodoArbol * buscado;
    char nombre[10];

    printf("Ingrese el nombre de la persona a buscar: \n");
    fflush(stdin);
    gets(nombre);

    buscado = buscarPorNombre(arbol,nombre);

    printf("La persona:\n");
    mostrarPersona(buscado->dato);

    /// EJERCICIO 6
    int alturaTotal = 0;

    alturaTotal = CalcularAltura(arbol);

    printf("La altura total del arbol es de: %d\n", alturaTotal);

    /// EJERCICIO 7 (funca raro)
    int totalNodos = 0;

    totalNodos = contarNodos(arbol);

    printf("La cantidad total de nodos es de: %d\n", totalNodos);

    /// EJERCICIO 8

    int totalHojas = 0;

    totalHojas = contarHojas(arbol);

    printf("El total de nodos hoja en el arbol es de: %d \n",totalHojas);

    /// EJERCICIO 9
    int legajoABorrar = 0;

    printf("Ingrese el legajojo que desea borrar: \n");
    scanf("%d",&legajoABorrar);



    return 0;
}


nodoArbol * cargarArbol(nodoArbol * arbol)
{
    char seguir = 's';

    while (seguir == 's')
    {
        persona aux = cargarPersona();
        nodoArbol * nuevo = crearNodoArbol(aux);
        arbol = insertarLegajo(arbol,nuevo);

        printf("desea seguir ingresando datos? (S/N) \n");
        fflush(stdin);
        scanf("%c",&seguir);
    }


    return arbol;
}

nodo * arbolToLista(nodoArbol * arbol, nodo * lista)
{
    if(arbol != NULL)
    {
        lista = agregarPpio(lista,crearNodo(arbol->dato));
        lista = arbolToLista(arbol->izq,lista);
        lista = arbolToLista(arbol->der,lista);
    }

    return lista;
}

nodoArbol * buscarPorNombre (nodoArbol * arbol, char nombre[])
{
    nodoArbol * rta = NULL;

    if(arbol != NULL)
    {
        if(strcmp(arbol->dato.nombre,nombre) != 0)
        {
            rta = buscarPorNombre(arbol->izq,nombre);

            if(rta == NULL)
            {
                rta = buscarPorNombre(arbol->der,nombre);
            }

        }
        else
        {
            rta = arbol;
        }
    }

    return rta;
}

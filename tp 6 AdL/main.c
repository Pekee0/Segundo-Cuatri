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
int alta (celda adl[], char materia[], int idMateria, notaAlumno alu, int validos);
int cargarArray(celda ald[], int dimension);
nodo * crearNodo (notaAlumno alu);
int BuscarPosMateria (celda adl[], int idMateria, int validos);
int agregarMateria (celda adl[],int idMateria, char materia[], int validos);
nodo * agregarPpio (nodo * lista, nodo * nuevo);
nodo * iniclista();
void MostrarNotasDeMateria(nodo * lista);
void cargarArchivo (char nombreArchivo[], celda adl[], int validos);
void mostrarArchivo(char nombreArchivo[]);


int main()
{
        celda adl[30];
        int validos = cargarArray(adl,30);

        int idBuscado = 0;

        printf("Ingrese el ID de la materia que desea ver.\n");
        scanf("%d",&idBuscado);

        int pos = BuscarPosMateria(adl,idBuscado,validos);
        if(pos !=-1)
        {
            MostrarNotasDeMateria(adl[pos].listaDeNotas);
        }
        else
        {
            printf("No se encontro la materia\n");
        }

        char nombreArchivo[] = {"alumnos.bin"};

        cargarArchivo(nombreArchivo,adl,validos);
        printf("EL archivo:\n");
        mostrarArchivo(nombreArchivo);

    return 0;
}

/// FUBNCIONES DEL ARREGLO DE LISTAS

int cargarArray(celda adl[], int dimension)
{
    notaAlumno alumno;
    int idMateria = 0;
    char materia[30];
    char seguir ='s';
    int validos = 0;


    while (seguir == 's' && validos < dimension)
    {
        printf("Ingrese el ID de la materia: \n");
        scanf("%d",&idMateria);

        printf("Ingrese el nombre de la materia: \n");
        fflush(stdin);
        gets(materia);

        system ("cls");

        alumno = cargarAlumno(alumno);

        validos= alta(adl,materia,idMateria,alumno,validos);

        printf("para continuar presione S. \n");
        fflush(stdin);
        scanf("%c",&seguir);
    }

    return validos;
}

int alta (celda adl[], char materia[], int idMateria, notaAlumno alu, int validos)
{
        nodo * aux = crearNodo(alu);
        int pos = BuscarPosMateria(adl,idMateria,validos);

        if(pos == -1)
        {
            printf("\nLa materia no se encontro en el arreglo, se creara en un instante.\n");
            validos = agregarMateria(adl,idMateria, materia,validos);
            pos = validos-1;
        }
        adl[pos].listaDeNotas = agregarPpio(adl[pos].listaDeNotas,aux);

            return validos;
}

int BuscarPosMateria (celda adl[], int idMateria, int validos)
{
    int rta = -1;
    int i = 0;

    while (i<validos && rta == -1)
    {
        if(adl[i].idMateria == idMateria)
        {
            rta = i;
        }
        else
        {
            i++;
        }
    }

    return rta;
}

int agregarMateria (celda adl[],int idMateria, char materia[], int validos)
{
    strcpy(adl[validos].materia,materia);
    adl[validos].idMateria = idMateria;
    adl[validos].listaDeNotas = iniclista();

    validos ++;

    printf("\nMateria Creada Correctamente.\n");

    return validos;
}

int ArchivoToADL(celda adl[],int validos, char nombreArchivo[], int dimension)
{
    FILE  * Archivo = fopen(nombreArchivo,"rb");
    registroArchivo aux;
    int idMateria = 0;
    char Materia[20];
    notaAlumno alu;

    if(Archivo)
    {
        while(fread(&aux,sizeof(registroArchivo),1,Archivo) > 0)
        {
            alu = cargarAlumno(alu);
            validos = cargarArray(adl,dimension);


        }
    }
    else
    {
        printf("error en el archivo.\n");
    }
}
/// FUNCIONES DE LA LISTA

notaAlumno cargarAlumno (notaAlumno alumno)
{

    printf("Ingrese el legajo del alumno: \n");
    scanf("%d",&alumno.legajo);

    printf("Ingrese el nombre del alumno; \n");
    fflush(stdin);
    gets(alumno.nombreApe);

    printf("Ingrese la nota del alumno.\n");
    scanf ("%d",&alumno.nota);

    return alumno;
}

nodo * crearNodo (notaAlumno alu)
{
    nodo * aux = (nodo*)malloc(sizeof(nodo));

    aux->dato = alu;
    aux->siguiente = NULL;

    return aux;
}

nodo * agregarPpio (nodo * lista, nodo * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }


    return lista;
}

nodo * iniclista()
{
    return NULL;
}

void MostrarNotasDeMateria(nodo * lista)
{

    while(lista != NULL)
    {

        printf("-------------------------------------\n");
        printf("Legajo: %d\n",lista->dato.legajo);
        printf("Nombre: %s\n",lista->dato.nombreApe);
        printf("Nota: %d\n",lista->dato.nota);
        printf("-------------------------------------\n");

        lista = lista->siguiente;
    }
}


/// FUNCIONES DEL ARCHIVO

void cargarArchivo (char nombreArchivo[], celda adl[], int validos)
{
    FILE * archivo = fopen(nombreArchivo,"wb");

    registroArchivo aux;
    int i = 0;

    if(archivo)
    {
        while(i < validos)
        {

            aux.idMateria = adl[i].idMateria;
            strcpy (aux.materia,adl[i].materia);

            while(adl[i].listaDeNotas != NULL)
            {
                aux.legajo = adl[i].listaDeNotas->dato.legajo;
                strcpy(aux.nombreApe,adl[i].listaDeNotas->dato.nombreApe);
                aux.nota = adl[i].listaDeNotas->dato.nota;

                fwrite(&aux,sizeof(registroArchivo),1,archivo);

                adl[i].listaDeNotas = adl[i].listaDeNotas->siguiente;

            }

            i++;

        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

}

void mostrarArchivo(char nombreArchivo[])
{
    FILE * archivo = fopen(nombreArchivo,"rb");
    registroArchivo aux;

    if(archivo)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archivo) > 0)
        {
            printf("------------------------------\n");
            printf("ID Materia:  %d \n",aux.idMateria);
            printf("Materia: %s\n",aux.materia);
            printf("Legajo: %d\n",aux.legajo);
            printf("Nombre: %s\n",aux.nombreApe);
            printf("Nota: %d\n",aux.nota);
            printf("------------------------------\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("error al abrir el archivo.\n");
    }


}

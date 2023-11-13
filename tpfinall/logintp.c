#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idLogro;
    char NombreLogro[20];
    char Descripcion[60];
    int obtenido; /// funciona como un bool

}logros;

typedef struct
{
    char Nombre[20];
    int puntaje;
    int dinero;
    logros logros[20];

}player;

typedef struct nodoPlayer
{
    player dato;
    struct nodoPlayer * sig;

}nodoPlayer;

void IniciarSesionORegistrarse( char nombreArchivo[]);
player crearPerfil(char nombreArchivo[]);



int main()
{
    char nombreArchivo[] ={"jugadores.bin "};

    IniciarSesionORegistrarse(nombreArchivo);

    return 0;
 }

void IniciarSesionORegistrarse( char nombreArchivo[])
{
    char opc;

        printf("Nueva Partida\n");
        printf("CargarPartida\n");
        printf("Puntajes\n");

        fflush(stdin);

        scanf("%c",&opc);

        while(opc != 'n' && opc != 'c' && opc != 'p')
        {
            printf("Ingrese una opcion valida\n");

             printf("Nueva Partida\n");

             printf("CargarPartida\n");

              printf("Puntajes\n");
              fflush(stdin);

             scanf("%c",&opc);
        }

        if(opc == 'n')
        {
             printf("Perfiles Disponibles.\n");
            mostrarPlayers(nombreArchivo);
            printf("Crear nuevo perfil.\n");
            player nuevo = crearPerfil(nombreArchivo);

            //agregarPlayerToArchivo(nombreArchivo,nuevo);
        }
        else if(opc == 'c')
        {
            printf("Perfiles Disponibles.\n");
            mostrarPlayers(nombreArchivo);
        }
        else if(opc == 'p')
        {
            /// mostrarPuntajes
        }

 }


void mostrarPlayers(char nombreArchivo[])
{
    FILE * archivo = fopen(nombreArchivo,"rb");
    player aux;

    if(archivo)
    {
        while(fread(&aux,sizeof(player),1,archivo) > 0)
        {
            mostrarDataPlayer(aux);
        }

        fclose(archivo);
    }
    else
    {
        printf("Error en el archivo.\n");
    }
}

void  mostrarDataPlayer(player aux)
{
    printf("--------------------------------------\n");
    printf("Nombre: %s",aux.Nombre);
    printf("Puntaje: %d", aux.puntaje);
    printf("Dinero: %d",aux.dinero);
    printf("--------------------------------------\n");
}
player crearPerfil(char nombreArchivo[])
{
    player aux;
    int flag = 0;

    printf("Ingrese su nombre de usuario: \n");
    scanf("%s",&aux.Nombre);

    flag = buscarPlayerArchivo(nombreArchivo,aux.Nombre);

    while (flag == 1)
    {
        printf("Ese nombre ya esta en uso.\n");

        printf("Ingrese un nombre de usuario: \n");
        scanf("%s",&aux.Nombre);

        flag = buscarPlayerArchivo(nombreArchivo,aux.Nombre);
    }
    /// se debe ver que el nombre no exista en el archivo.

    aux.dinero = 20000;
    //aux.logros[] = NULL; ver como hacer esto
    aux.puntaje = 0;

    printf("Usuario creado con exito.\n");
    return aux;

}

logros CrearLogros(logros Logros[])
{

    Logros[0].idLogro = 1;
    strcpy(Logros[0].NombreLogro,"Seamos libres que lo demas no importa nada");
    strcpy(Logros[0].Descripcion,"salva la vida del General San Martin");
    Logros[0].obtenido = 0;

}

void agregarPlayerToArchivo(char nombreArchivo[], player nuevo)
{
    FILE * archivo = fopen(nombreArchivo,"ab");

    if(archivo)
    {
        fwrite(&nuevo,sizeof(player),1,archivo);
    }
    else
    {
        printf("Error.\n");
    }
}

int buscarPlayerArchivo(char nombreArchivo[], char nombreBuscado[])
{
    FILE * archivo = fopen(nombreArchivo,"rb");
    char nombre[20];
    int flag =0;
    if (archivo)
    {
        while(fread(&nombre,sizeof(char),1,archivo) > 0 && flag == 0)
        {
            if(strcmp(nombreBuscado,nombre)==0)
            {
                flag =1;
            }
        }

        fclose(archivo);
    }
    else
    {
        printf("EL archivo no existe.\n");
        flag = -1;
    }

    return flag;
}

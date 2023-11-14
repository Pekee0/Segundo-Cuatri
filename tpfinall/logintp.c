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
    int activo;
    char Nombre[20];
    int puntaje;
    int dinero;
    logros logros[20];
    int UltimoNodo;
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

            agregarPlayerToArchivo(nombreArchivo,nuevo);
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

void mostrarPuntajes(NodoPuntajes * Puntajes)
{
    seg = Puntajes;

    while(seg != NULL)
    {

        seg = seg->sig;
    }
}

void  mostrarDataPlayer(player aux)
{
    printf("--------------------------------------\n");
    printf("Nombre: %s\n",aux.Nombre);
    printf("Puntaje: %d\n", aux.puntaje);
    printf("Dinero: %d\n",aux.dinero);
    printf("--------------------------------------\n");
}
player crearPerfil(char nombreArchivo[])
{
    player aux;
    int flag = 0;

    printf("Ingrese su nombre de usuario,recuerde que este no podra modificarse: \n");
    fflush(stdin);
    gets(aux.Nombre);

    flag = buscarPlayerArchivo(nombreArchivo,aux.Nombre);

    while (flag == 1)
    {
        printf("Ese nombre ya esta en uso.\n");

        printf("Ingrese un nombre de usuario,recuerde que este no podra modificarse: \n");
        fflush(stdin);
        gets(aux.Nombre);

        flag = buscarPlayerArchivo(nombreArchivo,aux.Nombre);
    }
    /// se debe ver que el nombre no exista en el archivo.

    aux.dinero = 20000;
    CrearLogros(aux.logros);
    aux.puntaje = 0;
    aux.UltimoNodo = 0;
    aux.activo = 1;
    printf("Usuario creado con exito.\n");

    return aux;
}

void CrearLogros(logros Logros[])
{

    Logros[0].idLogro = 1;
    strcpy(Logros[0].NombreLogro,"Goto(Canada)\n");
    strcpy(Logros[0].Descripcion,"Caiste Preso\n");
    Logros[0].obtenido = 0;

    Logros[1].idLogro = 2;
    strcpy(Logros[1].NombreLogro,"Make Argentina Great Again\n");
    strcpy(Logros[1].Descripcion," 'Evita' la crisis del 2001, convirtiendo al pais en potencia\n");
    Logros[1].obtenido = 0;

    Logros[2].idLogro = 3;
    strcpy(Logros[2].NombreLogro,"Me llamaron LOCO!\n");
    strcpy(Logros[2].Descripcion,"Convence a Bielsa de convocar al ultimo 10, ganado la tercera en 2002\n");
    Logros[2].obtenido = 0;

    Logros[3].idLogro = 4;
    strcpy(Logros[3].NombreLogro,"VIVA LA... libertad?\n");
    strcpy(Logros[3].Descripcion,"Causa la decadencia del pais, condenandolo al autoritarismo Liberal\n");
    Logros[3].obtenido = 0;

    Logros[4].idLogro = 5;
    strcpy(Logros[4].NombreLogro,"Soy historia\n");
    strcpy(Logros[4].Descripcion,"Crea el dulce de leche\n");
    Logros[4].obtenido = 0;

    Logros[5].idLogro = 6;
    strcpy(Logros[5].NombreLogro,"Anya Taylor Who?\n");
    strcpy(Logros[5].Descripcion,"No existe el dulce de leche y el mundo no conocio a la gran Ana taylor Joy\n");
    Logros[5].obtenido = 0;

    Logros[6].idLogro = 7;
    strcpy(Logros[6].NombreLogro,"Seamos libres que lo demas no importa nada");
    strcpy(Logros[6].Descripcion,"salva la vida del General San Martin");
    Logros[6].obtenido = 0;

    Logros[7].idLogro = 8;
    strcpy(Logros[7].NombreLogro,"Porteñolandia\n");
    strcpy(Logros[7].Descripcion,"San Martin muere en la batalla de san lorenzo, america nunca fue liberada y ahora somos todos porteñoos\n");
    Logros[7].obtenido = 0;

    Logros[8].idLogro = 9;
    strcpy(Logros[8].NombreLogro,"Que gil que soy, siempre me la mando\n");
    strcpy(Logros[8].Descripcion,"Se el culpable de desatar una guerra mundial\n");
    Logros[8].obtenido = 0;

    Logros[9].idLogro = 10;
    strcpy(Logros[9].NombreLogro,"Adolf Van Gogh\n");
    strcpy(Logros[9].Descripcion,"Ahora existe la paz mundial\n");
    Logros[9].obtenido = 0;

    Logros[10].idLogro = 11;
    strcpy(Logros[10].NombreLogro,"U can`t see me\n");
    strcpy(Logros[10].Descripcion,"EL TODO LO VE.\n");
    Logros[10].obtenido = 0;

    Logros[11].idLogro = 12;
    strcpy(Logros[11].NombreLogro,"GoodBye Mr.Frog\n");
    strcpy(Logros[11].Descripcion,"Sapardo y Ranaglia\n");
    Logros[11].obtenido = 0;

    Logros[12].idLogro = 13;
    strcpy(Logros[12].NombreLogro,"Mezasa\n");
    strcpy(Logros[12].Descripcion,"Como te ven, Te tratan\n");
    Logros[12].obtenido = 0;

    Logros[13].idLogro = 14;
    strcpy(Logros[13].NombreLogro,"MUUUCHAAACHOOS\n");
    strcpy(Logros[13].Descripcion,"Diego Gana la tercera y cambia el rumbo de su vida\n");
    Logros[13].obtenido = 0;

    Logros[14].idLogro = 15;
    strcpy(Logros[14].NombreLogro,"!D10S\n");
    strcpy(Logros[14].Descripcion,"PA QUE TOCAS,NO TOQUES NADA\n");
    Logros[14].obtenido = 0;

    Logros[15].idLogro = 16;
    strcpy(Logros[15].NombreLogro,"Coronados De Gloria\n");
    strcpy(Logros[15].Descripcion,"Logra que argentina sea quintuple campeona mundial\n");
    Logros[15].obtenido = 0;

    Logros[16].idLogro = 17;
    strcpy(Logros[16].NombreLogro,"Cuanto Tiempo al Pedo\n");
    strcpy(Logros[16].Descripcion,"Anda a agarrar la pala, ya conseguiste el platino\n");
    Logros[16].obtenido = 0;

    Logros[17].idLogro = 18;
    strcpy(Logros[17].NombreLogro,"Haciendo historia\n");
    strcpy(Logros[17].Descripcion,"Viaja por primera vez en el tiempo\n");
    Logros[17].obtenido = 0;

    Logros[18].idLogro = 19;
    strcpy(Logros[18].NombreLogro,"TOP 1\n");
    strcpy(Logros[18].Descripcion,"Conseguir ser el primero en la lista de puntajes\n");
    Logros[18].obtenido = 0;

    Logros[19].idLogro = 20;
    strcpy(Logros[19].NombreLogro,"MataReyes\n");
    strcpy(Logros[19].Descripcion,"Asesina a grondona\n");
    Logros[19].obtenido = 0;

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
    player aux;
    int flag =0;
    if (archivo)
    {
        while(fread(&aux,sizeof(player),1,archivo) > 0 && flag == 0)
        {
            if(strcmp(nombreBuscado,aux.Nombre)==0)
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

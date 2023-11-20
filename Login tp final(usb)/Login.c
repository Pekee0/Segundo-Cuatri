#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cFront.h"
#include "Login.h"

int IniciarSesionORegistrarse(char nombreArchivo[]) /// funcion que invoca el menu principal, se la llama con el nombre del archivo de jugadores como parametro
{

    int  * alto;
    int * ancho;
    char op0[] = {"Nueva Partida"};
    char op1[] = {"Cargar Partida"};
    char op2[] = {"Puntajes"};
    char op3[] = {"Mi Perfil"};
    char op4[] = {"Salir"};

    int opc = 0;
    obtenerDimensionesConsola(&ancho,&alto);


    while(opc >=0 && opc< 4)
    {

        menu:
        system("cls");
        Color(BLACK,WHITE);
        printearLogo();

        opc = pruebaElegirFecha(op0,op1,op2,op3,op4,ancho,alto);

        if(opc == 0) /// ambas funciones deben devolver el ultimo nodo
        {
            NuevaPartida(nombreArchivo,ancho,alto);
            return;
        }
        else if (opc == 1)
        {
            CargarPartida(nombreArchivo,ancho,alto);
            return;
        }
        else if(opc == 2)
        {
            system("cls");

            nodoPuntajes * lista;
            lista = iniclista();
            lista = pasarArchivoToListaPuntajes(nombreArchivo,lista);
            mostrarPuntajes(lista);

            printf("\n");
            system("pause");
            goto menu;
        }
        else if (opc == 3)
        {
            system("cls");

            MiPerfil(nombreArchivo,alto,ancho);

            printf("\n");
            system("pause");
            goto menu;
        }
        else if (opc == 4)
        {
            system("cls");
            char adios[] = {"Gracias por jugar :D"};
            simulacroDeCentrarUnaOpc(adios,ancho,alto);
            break;

        }

        return 0;
    }
}



 nodoPuntajes * iniclista()
 {
    return NULL ;
 }

 nodoPuntajes * crearNodoPuntaje(int puntaje,char nombre[])
 {
    nodoPuntajes * aux  = (nodoPuntajes*)malloc(sizeof(nodoPuntajes));

    strcpy(aux->nombre,nombre);
    aux->puntaje = puntaje;

    aux->ante = NULL;
    aux->sig = NULL;

    return aux;
 }

nodoPuntajes * AgregarPpioPuntaje (nodoPuntajes * lista, nodoPuntajes * nuevo)
 {
    nuevo->sig = lista;

    if(lista != NULL)
    {
        lista->ante=nuevo;
    }

    return nuevo;
}

nodoPuntajes * agregarEnOrdenPuntajes(nodoPuntajes  * lista, nodoPuntajes * nuevo) {

   if(lista == NULL)
    {
      lista = nuevo;
   }
   else
    {
        if(nuevo->puntaje > lista->puntaje)
        {
            lista = AgregarPpioPuntaje(lista, nuevo);
        }
        else
        {
         nodoPuntajes * ante = lista;
         nodoPuntajes * seg = lista->sig;

         while((seg != NULL) && nuevo->puntaje < seg->puntaje)
            {
                ante = seg;
                seg = seg->sig;
            }
         ante->sig = nuevo;
         nuevo->ante = ante;
         nuevo->sig = seg;

         if (seg!=NULL)
            seg->ante=nuevo;
        }
   }
   return lista;
}


nodoPuntajes * pasarArchivoToListaPuntajes(char nombreArchivo[], nodoPuntajes * lista)
 {
    FILE * archivo = fopen(nombreArchivo,"rb");

    player aux;
    nodoPuntajes * nuevo;
    if(archivo)
    {
        while(fread(&aux,sizeof(player),1,archivo) > 0)
        {
            if(aux.activo == 1)
            {
                nuevo = crearNodoPuntaje(aux.puntaje,aux.Nombre);
                lista = agregarEnOrdenPuntajes(lista,nuevo);
            }

        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

    return lista;
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

void mostrarPuntajes(nodoPuntajes * lista)
{
    nodoPuntajes * seg = lista;
    int i = 1;
    int * x;
    int * y;
    obtenerDimensionesConsola(&x,&y);
    int j=x;
    int l= 7;
    int k=y;
gotoxy(j/2-10, 1);
 printf("-----------------------------\n");
 gotoxy((j-strlen("TOP TEN"))/2, 3);
 printf("TOP TEN");
    while((seg != NULL) && i < 10)
    {
        gotoxy(j/2-10, l);
        printf("TOP %d: %s ---- %d\n",i,seg->nombre,seg->puntaje);
        seg = seg->sig;
        i++;
        l++;
    }
gotoxy(j/2-10, l+3 );
printf("-----------------------------\n");

}

void  mostrarDataPlayer(player aux)
{
        printf("--------------------------------------\n");
        printf("Nombre: %s\n",aux.Nombre);
        printf("Puntaje: %d\n", aux.puntaje);
        printf("Dinero: %d\n",aux.dinero);
        if(aux.activo == 1)
        printf("Estado de cuenta: Activa\n");
        else
        printf("Estado de cuenta: Inactiva\n");
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

    aux.dinero = 46000;
    CrearLogros(aux.logros);
    aux.puntaje = 0;
    aux.UltimoNodo = 0;
    aux.activo = 1;
    inicObjetos(aux.objetos);
    aux.comprado = 0;

    printf("Usuario creado con exito.\n");

    return aux;
}

void inicObjetos(stInventario dato[])
{
    strcpy(dato[0].nombre,"Billetes");
    dato[0].costo = 20000;
    dato[0].comprado = 0;

    strcpy(dato[1].nombre,"Pocion de sapo");
    dato[1].costo = 15000;
    dato[1].comprado = 0;

    strcpy(dato[2].nombre,"uniforme de granadero");
    dato[2].costo = 25000;
    dato[2].comprado = 0;

    strcpy(dato[3].nombre,"Agua");
    dato[3].costo = 1000;
    dato[3].comprado = 0;

    strcpy(dato[4].nombre,"traductor universal");
    dato[4].costo = 15000;
    dato[4].comprado = 0;
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
            if(strcmpi(nombreBuscado,aux.Nombre)==0)
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

player buscaryRetornarPlayerArchivo(char nombreArchivo[], char nombreBuscado[])
{
    FILE * archivo = fopen(nombreArchivo,"rb");
    player aux;
    player encontrado;
    int flag =0;

    if (archivo)
    {
        while((fread(&aux,sizeof(player),1,archivo) > 0) && (flag == 0))
        {
            if(strcmpi(nombreBuscado,aux.Nombre) ==0)
            {
                flag = 1;
                encontrado = aux;
            }
        }

        fclose(archivo);
    }
    else
    {
        printf("EL archivo no existe.\n");
        flag = -1;
    }

    return encontrado;
}

void printearLogo()
{

    char c;

    FILE * archivo = fopen ("ascii final.txt", "r");

    while(!feof(archivo))
    {
        c = getc(archivo);
        printf("%c",c);
    }

    fclose(archivo);
}

player CargarPartida(char nombreArchivo[], int ancho, int alto)
{
    system("cls");
    char nombreUsuario[20];
    int rta;
    int i = 0;
    char si[]= {"si"};
    char no[] = {"no"};
    player buscado;
    do{
        printf("Ingrese su nombre de usuario:\n");
        gets(nombreUsuario);
        buscado = buscaryRetornarPlayerArchivo(nombreArchivo,nombreUsuario);

        if(buscado.activo != 1)
        {
            printf("El usuario no se encontro\n");
            sleep(1);
        }
        else
        {
            printf("Es este tu perfil? \n");
            mostrarDataPlayer(buscado);
            rta = simulacroDeElegirOpc(si,no,ancho,alto);
        }

            i++;
            system ("cls");

        }while(rta != 1 && i< 3); /// esto retorna buscado.UltimoNodo

return buscado;
}

player NuevaPartida(char nombreArchivo[], int ancho, int alto)
{
    system("cls");
    printearLogo();

    char Cargar[] = {"Ver perfiles"};
    char crear[] = {"crear nuevo perfil"};
       player buscado;
    int elegir = simulacroDeElegirOpc(Cargar,crear,ancho,alto);

    if(elegir == 1)
    {
        system("cls");

        char nombreUsuario[20];
        int rta;
        int i = 0;
        char si[]= {"si"};
        char no[] = {"no"};


        do{
            printf("Ingrese su nombre de usuario:\n");
            gets(nombreUsuario);

            buscado = buscaryRetornarPlayerArchivo(nombreArchivo,nombreUsuario);

            if(buscado.activo != 1)
            {
                printf("El usuario no se encontro\n");
                sleep(1);
            }
            else
            {
                printf("Es este tu perfil? \n");
                mostrarDataPlayer(buscado);
                rta = simulacroDeElegirOpc(si,no,ancho,alto);

                if(rta == 1)
                {
                    break;
                }
            }
                i++;
            system ("cls");

            }while(rta != 1 && i< 3); /// esto retorna buscado.UltimoNodo
    }
    else if(elegir == 2)
        {
            system("cls");
            printf("Crear nuevo perfil\n");
            player nuevo = crearPerfil(nombreArchivo);
            agregarPlayerToArchivo(nombreArchivo,nuevo);
        }

    return buscado;
}

void MiPerfil(char nombreArchivo[], int alto, int ancho)
{
     char nombreUsuario[20];
        int rta;
        int i = 0;
        char si[]= {"si"};
        char no[] = {"no"};
    player buscado;

        do
        {
            printf("Ingrese su nombre de usuario:\n");
            gets(nombreUsuario);
            int filtro = 0;
            buscado = buscaryRetornarPlayerArchivo(nombreArchivo,nombreUsuario);
            filtro = strlen(buscado.Nombre);

            while(filtro == 0)
            {
                printf("No se encontro tu usuario\n");

                printf("Ingrese su nombre de usuario:\n");
                fflush(stdin);
                scanf("%s",&nombreUsuario);

                buscado = buscaryRetornarPlayerArchivo(nombreArchivo,nombreUsuario);
                filtro = strlen(buscado.Nombre);

            }

                printf("Es este tu perfil? \n");
                mostrarDataPlayer(buscado);
                rta = simulacroDeElegirOpc(si,no,ancho,alto);

                if(rta == 1)
                {
                    system("cls");
                    mostrarDataPlayer(buscado);
                    mostrarLogros(buscado);

                    printf("\n");

                    char op1[] = {"Activar Cuenta"};
                    char op2[] = {"Desactivar Cuenta"};

                    int opc =simulacroDeElegirOpc(op1,op2,ancho,alto);

                    if(opc == 1)
                    {
                        system("cls");
                        buscado = ActivarDesactivarcuenta(nombreArchivo,buscado,1);
                        printf("Cuenta activada Correctamente\n");
                        sleep(1);
                        break;
                    }
                    else
                    {
                        system("cls");
                       buscado = ActivarDesactivarcuenta(nombreArchivo,buscado,0);
                        printf("Cuenta desactivada Correctamente\n");
                        sleep(1);
                        break;
                    }

                }
                else
                {
                 i++;
                }

            system ("cls");
        }while(rta != 1 && i< 3);

            if(i == 3)
            {
               printf("vaya parece que su usuario no existe, porfavor cree un usuario en el menu.\n");
               return 0;
            }

}

void mostrarLogros(player dato)
{
    int i = 0;
    int j = 0;

    printf("Tus Logros: \n");
    while (i < 20)
    {
        if(dato.logros[i].obtenido == 1)
        {
            printf("---------------------------------\n");
            printf("%s\n",dato.logros[i].NombreLogro);
            printf("%s\n",dato.logros[i].Descripcion);
            printf("---------------------------------\n");
            j++;
        }

        i++;
    }

    printf("Logros obtenidos: %d/20",j);
}

long buscarPosPLayer(char nombreArchivo[], char nombreBuscado[])
{
    FILE * archivo = fopen(nombreArchivo,"rb");
    player aux;
    long pos = -1;
    int flag = 0;
    if(archivo)
    {

        while(fread(&aux,sizeof(player),1,archivo) > 0 && flag == 0)
        {
            if(strcmpi(aux.Nombre,nombreBuscado) == 0)
            {

                pos = ftell(archivo) - sizeof(player);
                flag = 1;
            }
        }

        fclose(archivo);
    }
    else
    {
        printf("Error\n");
    }

    return pos;
}

player guardarPartida(char nombreArchivo[], player dato)
{

    FILE * archivo = fopen(nombreArchivo,"rb+");
    player aux;

    if(archivo)
    {
        long pos = buscarPosPLayer(nombreArchivo,dato.Nombre);

        if (pos != -1)
        {


            aux.dinero = dato.dinero;
            aux.puntaje = dato.puntaje;
            aux.UltimoNodo = dato.UltimoNodo;
            aux.activo = dato.activo;
            aux = actualizarLogros(aux,dato);
            aux = actualizarObjetos(aux,dato);

            fseek(archivo, pos, SEEK_SET);

            fwrite(&aux, sizeof(player), 1, archivo);



        }
        fclose(archivo);

    }
    else
    {
        printf("error\n");
    }

    return aux;
}

player ActivarDesactivarcuenta(char nombreArchivo[],player dato, int opc)
{
    FILE * archivo = fopen(nombreArchivo,"rb+");

    if(archivo)
    {
        long pos = buscarPosPLayer(nombreArchivo,dato.Nombre);

        if (pos != -1)
        {
            dato.activo = opc;

            fseek(archivo, pos, SEEK_SET);

            fwrite(&dato, sizeof(player), 1, archivo);

        }
        fclose(archivo);
    }
    else
    {
        printf("Error\n");
    }

    return dato ;
}

player actualizarLogros(player a, player b)
{
    for (int i = 0; i< 21; i++)
    {
        a.logros[i].obtenido = b.logros[i].obtenido;
    }

    return a;
}

player actualizarObjetos(player a, player b)
{
    for (int i = 0; i< 5; i++)
    {
        a.objetos[i].comprado = b.objetos[i].comprado;
    }

    return a;
}




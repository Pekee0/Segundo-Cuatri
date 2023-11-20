#include "cFront.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#define teclEnter 13
#define teclIzquierda 75
#define teclDerecha 77

void  maximizarPantalla()//AGRANDA LA CONSOLA AL MAXIMO
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

void deshabilitarMouse()//DESAHBILITA LA OPCION DE CLICKEAR LA CONSOLA
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwMode;

    GetConsoleMode(hInput, &dwMode);
    SetConsoleMode(hInput, dwMode & ~(ENABLE_MOUSE_INPUT | ENABLE_QUICK_EDIT_MODE));
}


void borrarLinea(int y)//BORRA LA LINEA DEL EJE Y QUE SE RECIBE Y DEJA LA POSICION EN ESA COORDENADA
{
    ocultarCursor();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coord;
    coord.X = 0;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
    DWORD escritos;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, coord, &escritos);
    SetConsoleCursorPosition(hConsole, coord);
}

int contarOracionesParrafo(char *parrafo[])//CUENTA LAS ORACIONES DE UN PARRAFO
{
    int cont=0;
    while(parrafo[cont])//MIENTRAS QUE PARRAFO TENGA CADENAS DE STRINGS
    {
        cont++;//ME MUEVO, HASTA ENCONTRAR NULL
    }
    return cont;
}

void centrarParrafo(char *parrafo[], int anchoConsola, int altoConsola)//CENTRA UN PARRAFO, CANTIDAD DE ORACIONES ES contarOracionesParrafo(char *parrafo[])
{
    ocultarCursor();
    int cantidadDeOraciones=contarOracionesParrafo(parrafo);
    for(int i=0;i<cantidadDeOraciones;i++)
    {
        centrarOracion(parrafo[i], (anchoConsola-strlen(parrafo[i]))/2, ((altoConsola/2)-cantidadDeOraciones+i));
    }
    Color(BLACK, WHITE);
}

void centrarOracion(char oracion[], int anchoConsola, int altoConsola)//CENTRA LA ORACION, INVOCADA EN centrarParrafo.
{
    for(int j=0; j<strlen(oracion); j++)
    {
        Color(BLACK, LGREEN);
        gotoxy(anchoConsola+1, altoConsola);
        printf("|");
        gotoxy(anchoConsola,altoConsola);
       if(oracion[j]=='~')
       {
        printf("%c", 164);
       }
        else
        {
         printf("%c", oracion[j]);
        }
        anchoConsola++;
        usleep(32000);
    }
    gotoxy(anchoConsola,altoConsola);
    printf("  ");
}

int simulacroDeElegirOpc(char opc1[], char opc2[], int anchoConsola, int altoConsola)//MUESTRA COMO SELECCIONAS UNA OPCION O LA OTRA, RETORNA 1 o 2
{
    altoConsola=(altoConsola/2)+5;
    int espaciado=10;
    int opc=1;
    bool repite=true;
    do{
        centrarDosOpc(opc1, opc2, anchoConsola, altoConsola, opc, espaciado);
        ocultarCursor();
        char tecla=getch();
        if(tecla==teclDerecha||tecla==teclIzquierda)
        {
             opc = (opc == 1) ? 2 : 1;
        }
        else if(tecla==teclEnter)
        {
            opc==1 ? opcionTitileraOpc1(opc1, opc2, anchoConsola, altoConsola, espaciado) : opcionTitileraOpc2(opc1, opc2, anchoConsola, altoConsola, espaciado);
            repite=false;
        }

    }while(repite);
    return opc;
}

void centrarDosOpc(char opc1[], char opc2[], int anchoConsola, int altoConsola, int opcionSeleccionada, int espaciado)//PRINTEA LAS DOS OPCIONES CORTAS DE FORMA CENTRADA INVOCADA EN simulacroDeElegirOpc
{
    ocultarCursor();
    Color(BLACK, opcionSeleccionada == 1 ? LGREEN : WHITE);
    imprimirOpcionALaIzquierda(opc1, opc2, anchoConsola, altoConsola, espaciado);
    Color(BLACK, opcionSeleccionada == 2 ? LGREEN : WHITE);
    imprimirOpcionALaDerecha(opc1, opc2, anchoConsola, altoConsola, espaciado);
}

void imprimirOpcionALaIzquierda(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//IMPRIME UNA OPCION CORTA A LA IZQUIERDA INVOCADA EN centrarDosOpc
{
    ocultarCursor();
    gotoxy(anchoConsola/2-strlen(opc1)-espaciado, altoConsola);
    for(int i=0; i<=strlen(opc1)+1;i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2-strlen(opc1)-espaciado, altoConsola+1);
    printf("|%s|", opc1);
    gotoxy(anchoConsola/2-strlen(opc1)-espaciado, altoConsola+2);
    for(int i=0; i<=strlen(opc1)+1;i++)
    {
        printf("=");
    }
}

void imprimirOpcionALaDerecha(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//IMPRIME UNA OPCION LARGA A LA IZQUIERDA INVOCADA EN centrarDosOpc
{
    ocultarCursor();
    gotoxy(anchoConsola/2+espaciado, altoConsola);
    for(int i=0; i<=strlen(opc2)+1;i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2+espaciado, altoConsola+2);
    for(int i=0; i<=strlen(opc2)+1;i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2+espaciado, altoConsola+1);
    printf("|%s|", opc2);
}

void opcionTitileraOpc1(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//HACE TITILEAR LA OPCION CORTA DE LA IZQUIERDA INVOCADA EN simulacroDeElegirOpc
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        imprimirOpcionALaIzquierda(opc1, opc2, anchoConsola, altoConsola, espaciado);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

void opcionTitileraOpc2(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//HACE TITILEAR LA OPCION CORTA DE LA DERECHA INVOCADA EN simulacroDeElegirOpc
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        imprimirOpcionALaDerecha(opc1, opc2, anchoConsola, altoConsola, espaciado);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

int simulacroDeCentrarUnaOpc(char opc1[], int anchoConsola, int altoConsola)//IMPRIME UNA OPCION EN EL CENTRO DE LA PANTALLA DEBAJO DEL TEXTO RETORNA SIEMPRE 1
{
    int opc=1;
    altoConsola=(altoConsola/2)+5;
    bool repite=true;
    do{
        ocultarCursor();
        Color(BLACK, LGREEN);
        imprimirUnaOpcionCentrada(opc1, anchoConsola, altoConsola);
        char tecla=getch();
        if(tecla==teclEnter)
        {
            opcionTitileraUnaOpcion(opc1, anchoConsola, altoConsola);
            Color(BLACK, WHITE);
            repite=false;
        }
    }while(repite);
    return opc;
}

void imprimirUnaOpcionCentrada(char opc1[], int anchoConsola, int altoConsola)//IMPRIME LA OPCION, INVOCADA EN simulacroDeCentrarUnaOpc
{
    ocultarCursor();
    gotoxy((anchoConsola-strlen(opc1))/2, altoConsola);
    for(int i=0; i<=strlen(opc1)+1;i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(opc1))/2, altoConsola+2);
    for(int i=0; i<=strlen(opc1)+1; i++)
    {
        printf("=");
    }
    gotoxy(((anchoConsola-strlen(opc1))/2), altoConsola+1);
    printf("|%s|", opc1);
}

void opcionTitileraUnaOpcion(char opc1[], int anchoConsola, int altoConsola)//HACE QUE TITILEA LA OPCION SELECCIONADA, INVOCADA EN simulacroDeCentrarUnaOpc
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        imprimirUnaOpcionCentrada(opc1, anchoConsola, altoConsola);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

int pruebaElegirFecha(char opc0[], char opc1[], char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola)//FUNCION PARA MOSTRAR Y SELECCIONAR FECHA DE VIAJE
{
    altoConsola=(altoConsola/2)+5;
    int espaciado=10;
    int opc=0;
    bool repite=true;
    do{
        centrarLasFechas(opc0, opc1, opc2, opc3, opc4, anchoConsola, altoConsola, opc, espaciado);
        ocultarCursor();
        char tecla=getch();
        switch(tecla)
        {
        case teclDerecha:
            if(opc==4)
            {
                opc=0;
            }
            else
            {
                opc++;
            }
            break;
        case teclIzquierda:
            if(opc==0)
            {
                opc=4;
            }
            else
            {
                opc--;
            }
            break;
        case teclEnter:
            switch(opc)
            {
            case 0:
                opcionTitileraPrimerFecha(opc0, opc1, opc2, anchoConsola, altoConsola, espaciado);
                break;
            case 1:
                opcionTitileraSegundaFecha(opc1, opc2, anchoConsola, altoConsola, espaciado);
                break;
            case 2:
                opcionTitileraTercerFecha(opc2, anchoConsola, altoConsola);
                break;
            case 3:
                opcionTitileraCuartaFecha(opc2, opc3, anchoConsola, altoConsola, espaciado);
                break;
            case 4:
                opcionTitileraQuintaFecha(opc2, opc3, opc4, anchoConsola, altoConsola, espaciado);
                break;
            }
            repite=false;
            break;
        }
    }while(repite);
    return opc;
}

void centrarLasFechas(char opc0[], char opc1[], char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola, int opc, int espaciado)//FUNCION QUE MUESTRA LAS FECHAS INVOCADA EN pruebaElegirFecha
{
    ocultarCursor();
    Color(BLACK, opc == 0 ? LGREEN : WHITE);
    primeraFecha(opc0, opc1, opc2, anchoConsola, altoConsola, espaciado);
    Color(BLACK, opc == 1 ? LGREEN : WHITE);
    segundaFecha(opc1, opc2, anchoConsola, altoConsola, espaciado);
    Color(BLACK, opc == 2 ? LGREEN : WHITE);
    tercerFecha(opc2, anchoConsola, altoConsola);
    Color(BLACK, opc == 3 ? LGREEN : WHITE);
    cuartaFecha(opc2, opc3, anchoConsola, altoConsola, espaciado);
    Color(BLACK, opc == 4 ? LGREEN : WHITE);
    quintaFecha(opc2, opc3, opc4, anchoConsola, altoConsola, espaciado);
}

void primeraFecha(char opc0[], char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//IMPRIME LA PRIMER FECHA
{
    ocultarCursor();
    gotoxy(anchoConsola/2-strlen(opc0)-strlen(opc1)-(strlen(opc2)/2)-(espaciado*2), altoConsola);
    for(int i=0; i<=strlen(opc0)+1; i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2-strlen(opc0)-strlen(opc1)-(strlen(opc2)/2)-(espaciado*2), altoConsola+1);
    printf("|%s|", opc0);
    gotoxy(anchoConsola/2-strlen(opc0)-strlen(opc1)-(strlen(opc2)/2)-(espaciado*2), altoConsola+2);
    for(int i=0; i<=strlen(opc0)+1; i++)
    {
        printf("=");
    }
}

void segundaFecha(char opc1[], char opc2[],int anchoConsola, int altoConsola, int espaciado)//IMPRIME LA SEGUNDA FECHA
{
    ocultarCursor();
    gotoxy(anchoConsola/2-strlen(opc1)-(strlen(opc2)/2)-espaciado, altoConsola);
    for(int i=0; i<=strlen(opc1)+1; i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2-strlen(opc1)-(strlen(opc2)/2)-espaciado, altoConsola+1);
    printf("|%s|", opc1);
    gotoxy(anchoConsola/2-strlen(opc1)-(strlen(opc2)/2)-espaciado, altoConsola+2);
    for(int i=0; i<=strlen(opc1)+1; i++)
    {
        printf("=");
    }
}

void tercerFecha(char opc2[], int anchoConsola, int altoConsola)//IMPRIME LA TERCER FECHA
{
    ocultarCursor();
    gotoxy((anchoConsola-strlen(opc2))/2, altoConsola);
    for(int i=0; i<=strlen(opc2)+1; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(opc2))/2, altoConsola+1);
    printf("|%s|", opc2);
    gotoxy((anchoConsola-strlen(opc2))/2, altoConsola+2);
    for(int i=0; i<=strlen(opc2)+1; i++)
    {
        printf("=");
    }
}

void cuartaFecha(char opc2[], char opc3[], int anchoConsola, int altoConsola, int espaciado)//IMPRIME LA CUARTA FECHA
{
    ocultarCursor();
    gotoxy(anchoConsola/2+(strlen(opc2)/2)+espaciado, altoConsola);
    for(int i=0; i<=strlen(opc3)+1; i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2+(strlen(opc2)/2)+espaciado, altoConsola+1);
    printf("|%s|", opc3);
    gotoxy(anchoConsola/2+(strlen(opc2)/2)+espaciado, altoConsola+2);
    for(int i=0; i<=strlen(opc3)+1; i++)
    {
        printf("=");
    }
}

void quintaFecha(char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola, int espaciado)//IMPRIME LA QUINTA FECHA
{
    ocultarCursor();
    gotoxy(anchoConsola/2+strlen(opc3)+(strlen(opc2)/2)+(espaciado*2), altoConsola);
    for(int i=0; i<=strlen(opc4)+1; i++)
    {
        printf("=");
    }
    gotoxy(anchoConsola/2+strlen(opc3)+(strlen(opc2)/2)+(espaciado*2), altoConsola+1);
    printf("|%s|", opc4);
    gotoxy(anchoConsola/2+strlen(opc3)+(strlen(opc2)/2)+(espaciado*2), altoConsola+2);
    for(int i=0; i<=strlen(opc4)+1; i++)
    {
        printf("=");
    }
}

void opcionTitileraPrimerFecha(char opc0[], char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//HACE QUE TITILE LA PRIMER FECHA
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        primeraFecha(opc0, opc1, opc2, anchoConsola, altoConsola, espaciado);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

void opcionTitileraSegundaFecha(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado)//HACE QUE TITILE LA SEGUNDA FECHA
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        segundaFecha(opc1, opc2, anchoConsola, altoConsola, espaciado);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

void opcionTitileraTercerFecha(char opc2[], int anchoConsola, int altoConsola)//HACE QUE TITILE LA TERCERA FECHA
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        tercerFecha(opc2, anchoConsola, altoConsola);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

void opcionTitileraCuartaFecha(char opc2[], char opc3[], int anchoConsola, int altoConsola, int espaciado)//HACE QUE TITILE LA CUARTA FECHA
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        cuartaFecha(opc2, opc3, anchoConsola, altoConsola, espaciado);
        usleep(150000);
    }
    Color(BLACK, LGREEN);
}

void opcionTitileraQuintaFecha(char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola, int espaciado)//HACE QUE TITILE LA QUINTA FECHA
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        quintaFecha(opc2,opc3, opc4, anchoConsola, altoConsola, espaciado);
        usleep(150000);
    }

    Color(BLACK, LGREEN);
}

void obtenerDimensionesConsola(int* anchoConsola, int* altoConsola)//MODIFICA LOS PARAMETROS CON LA INFORMACION DE LOS LIMITES DE LA PANTALLA
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *anchoConsola = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *altoConsola = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void gotoxy(int x, int y)//LLEVA EL CURSOR A LAS COORDENADAS
{
    HANDLE hCon;
    hCon= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X= x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hCon,dwPos);
}

void ocultarCursor()//OCULTA EL CURSOR
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void mostrarCursor()//MUESTRA EL CURSOR
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;  // Mostrar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void abrirBold()//AUMENTA LA INTENSIDAD DE LA LETRA
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    csbi.wAttributes |= FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

void cerrarBold()//VUELVE LA INTENSIDAD DE LA LETRA A LA NORMALIDAD
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    csbi.wAttributes &= ~FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

void Color(int Background, int Text)//CAMBIA LOS COLORES DE LA LINEA ACTUAL DE LA CONSOLA
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    int New_Color= Text + (Background * 16);
    SetConsoleTextAttribute(Console, New_Color);
}

void niBlancoNiNegro()
{
    int fondo=BLACK;
    int texto;
    do  {
            texto = (rand() % 14) + 1;
        } while (texto == WHITE || texto == BLACK || texto == LGREY);

    Color(fondo, texto);
}

void pruebaCuadro(int x, int y, int boxWidth, int boxHeight)//CREA UN RECUADRO AL REDEDOR DE LA PANTALLA X & BOXWIDTH DEBEN SER ANCHOCONSOLA, Y & BOXHEIGHT DEBEN SER ALTOCONSOLA
{
    ocultarCursor();
    boxWidth=boxWidth-20;
    boxHeight=boxHeight-10;
    x=(x-boxWidth)/2;
    y=(y-boxHeight)/2-1;
    Color(BLACK, GREEN);
    abrirBold();
    int topLeft = 201;
    int topRight = 187;
    int bottomLeft= 200;
    int bottomRight= 188;
    int horizontal = 205;
    int vertical = 186;
    for (int i = 0; i <= boxWidth; i++)
        {
        gotoxy(x+i, y);
        printf("%c", horizontal);
        gotoxy(x+i, y+boxHeight);
        printf("%c", horizontal);
        }
    for (int i = 0; i <= boxHeight; i++)
        {
        gotoxy(x, y+i);
        printf("%c", vertical);
        gotoxy(x+boxWidth, y+i);
        printf("%c", vertical);
        }
    gotoxy(x, y);
    printf("%c", topLeft);
    gotoxy(x + boxWidth, y);
    printf("%c", topRight);
    gotoxy(x, y + boxHeight);
    printf("%c", bottomLeft);
    gotoxy(x + boxWidth, y + boxHeight);
    printf("%c", bottomRight);
    cerrarBold();
    Color(BLACK, WHITE);
}

void mostrarLineaCreditos(char* parrafo[],int i, int anchoConsola, int altoConsola)//MUESTRA LAS LINEAS ASCENDENTES DE LOS CREDITOS, INVOCADA EN mostrarCreditos
{
    ocultarCursor();
    int y;
    int x;
    obtenerDimensionesConsola(&x, &y);
    for(int j=0; j<=i; j++)
    {
        if(altoConsola>=0&&altoConsola+1<y)
       {
            gotoxy((anchoConsola-strlen(parrafo[j]))/2, altoConsola);
            printf("%s", parrafo[j]);
            altoConsola++;
            if(i==contarOracionesParrafo(parrafo)-1)
            {
                borrarLinea(altoConsola);
            }
        }

    }
}

void mostrarCreditos(char *parrafo[], int anchoConsola, int altoConsola)//MUESTRA TODA LA ANIMACION DE LOS CREDITOS
{
    ocultarCursor();
    abrirBold();
    int cant=contarOracionesParrafo(parrafo);
    while(altoConsola>=0)
    {
        for(int i=0; i<cant; i++)
        {
            mostrarLineaCreditos(parrafo, i, anchoConsola, altoConsola);
        }
        altoConsola--;
        usleep(600000);
    }

        for(int i=0; i<cant; i++)
        {
            fletarPrimerElementoArray(parrafo);
            system("cls");
            centrarParrafoEjeX(parrafo, anchoConsola, 0);
            usleep(600000);
        }
    cerrarBold();
}


void fletarPrimerElementoArray(char *A[])//ELIMINA EL PRIMER ELEMENTO DE UN ARRAY, INOVACADA EN mostrarCreditos
{
    if (A[0])
    {
        int i;
        for (i = 0; A[i + 1] != NULL; i++)
            {
                A[i] = A[i + 1];
            }
        A[i] = NULL;
    }
}


void centrarParrafoEjeX(char *p[], int anchoConsola, int y)//CENTRA UN PARRAFO EN EL EJE X, INVOCADA EN mostrarCreditos
{
    ocultarCursor();
    for(int i=0; i<contarOracionesParrafo(p); i++)
    {
        centrarOracionEjeX(p[i], anchoConsola, y+i);
    }

}

void centrarOracionEjeX(char o[], int anchoConsola, int y)//CENTRA UNA ORACION EN EL EJE X, INVOCADA EN centrarParrafoEjeX
{
    ocultarCursor();
        gotoxy((anchoConsola-strlen(o))/2, y);
        printf("%s", o);

}

void pruebaNuevLogroDesbloqueado(char logro[], int anchoConsola, int altoConsola, int y)//PRINTEA ANIMACION DE NUEVO LOGRO
{
    ocultarCursor();
    int x=y;
    abrirBold();
    Color(BLACK, YELLOW);
    while(y>=0)
    {
        gotoxy((anchoConsola-strlen(logro))/2, y);
        printf("%s", logro);
        if(x==y)
        {
            usleep(1500000);
        }
        usleep(500000);
        borrarLinea(y);
        y--;
    }
    cerrarBold();
}


void pruebaMostrarLogros(char logro[], int anchoConsola, int altoConsola)//MOSTRAR LOGRO DE FORMA ANIMADA HARDCODEADA
{
    abrirBold();
    Color(BLACK, RED);
    ocultarCursor();
    gotoxy((anchoConsola-strlen(logro))/2-3, 0);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    usleep(500000);


    borrarLinea(0);
    gotoxy((anchoConsola-strlen(logro))/2-4, 1);
    for(int i=0; i<=strlen(logro)+6; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-4, 0);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 0);
    printf("=");
    usleep(500000);


    Color(BLACK, RED);
    borrarLinea(0);
    borrarLinea(1);
    gotoxy((anchoConsola-strlen(logro))/2-3, 2);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-3, 1);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 1);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2-3, 0);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 0);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2, 0);
    Color(BLACK, CYAN);
    printf("%s", logro);
    usleep(500000);


    Color(BLACK, RED);
    borrarLinea(0);
    borrarLinea(1);
    borrarLinea(2);
    gotoxy((anchoConsola-strlen(logro))/2-3, 3);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-3, 2);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 2);
    printf("=");
     gotoxy((anchoConsola-strlen(logro))/2-3, 0);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 0);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2-3, 1);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 1);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2, 1);
    Color(BLACK, CYAN);
    printf("%s", logro);
    usleep(500000);


    Color(BLACK, RED);
    borrarLinea(0);
    borrarLinea(1);
    borrarLinea(2);
    borrarLinea(3);
    gotoxy((anchoConsola-strlen(logro))/2-3, 4);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-3, 0);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-3, 3);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 3);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2-3, 1);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 1);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2-3, 2);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 2);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2, 2);
    Color(BLACK, CYAN);
    printf("%s", logro);


    Color(BLACK, RED);
    borrarLinea(0);
    borrarLinea(1);
    borrarLinea(2);
    borrarLinea(3);
    borrarLinea(4);
    gotoxy((anchoConsola-strlen(logro))/2-3, 5);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-3, 1);
    for(int i=0; i<=strlen(logro)+5; i++)
    {
        printf("=");
    }
    gotoxy((anchoConsola-strlen(logro))/2-3, 4);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 4);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2-3, 2);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 2);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2-3, 3);
    printf("=");
    gotoxy((anchoConsola+strlen(logro))/2+2, 3);
    printf("=");
    gotoxy((anchoConsola-strlen(logro))/2, 3);
    Color(BLACK, CYAN);
    printf("%s", logro);
    cerrarBold();

}

void borrarDeAbajoParaArriba(int y)//DESDE EL EJE Y PROPORCIONADO, TODO LO QUE ESTE ARRIBA SE BORRA
{
    ocultarCursor();
    while(y>=0)
    {
        borrarLinea(y);
        y--;
    }
}

void reproducirWav(char soundFX[])//REPRODUCE UN WAV UNA VEZ
{
    PlaySound(soundFX, NULL, SND_FILENAME | SND_ASYNC);
}

void reproducirWavBucle(char soundFX[])//REPRODUCIR UN EN BUCLE
{
   PlaySound(soundFX, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void detenerReproducionWav()//FRENAR WAV
{
    PlaySound(NULL, NULL, 0);
}


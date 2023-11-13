#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#define teclEnter 13
#define teclIzquierda 75
#define teclDerecha 77
 #include <time.h>

enum Colors   // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LGREY = 7,
    DGREY = 8,
    LBLUE = 9,
    LGREEN = 10,
    LCYAN = 11,
    LRED = 12,
    LMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};
void Color(int Background, int Text)  // Función para cambiar el color del fondo y/o pantalla
{

    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

    // Para cambiar el color, se utilizan números desde el 0 hasta el 255.
    // Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
    int    New_Color= Text + (Background * 16);

    SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.

}
void obtenerDimensionesConsola(int* ancho, int* alto)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    *ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void gotoxy(int x, int y)
{

    HANDLE hCon;
    hCon= GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X= x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hCon,dwPos);
}


int main() {

    int *cAlto;
    int *cAncho;
    char *p[]={"tus pecados te condenaron", "pero te cruzas con un angel a la vuelta de almacen","tenes la oportunidad de decirle lo que quieras:", NULL};
    char opc1[]={"hola quien sos"};
    char opc2[]={"mirtha legrand????"};
    obtenerDimensionesConsola(&cAncho, &cAlto);

    //centrarParrafo(cAncho, cAlto, p, contarOracionesParrafo(p));
    //centrarDosOpc(opc1, opc2, cAncho, (cAlto+contarOracionesParrafo(p)/2)+1);

    simulacroDeElegirOpc(p, opc1, opc2, cAncho, cAlto, contarOracionesParrafo(p));
    gotoxy(0, 0);
    getch();



    return 0;
}

void centrarDosOpc(char opc1[], char opc2[], int cAncho, int cAlto, int opcionSeleccionada)
{
    ocultarCursor();
    Color(BLACK, opcionSeleccionada == 1 ? LGREEN : WHITE);
    //OPCION 1
    gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)-1), cAlto/2+1);
    for(int i=0; i<=strlen(opc1)+1;i++)
    {
        printf("=");
    }

    gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)-1), cAlto/2+2);
    printf("|");

    gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)-1), cAlto/2+3);
    for(int i=0; i<=strlen(opc1)+1;i++)
    {
        printf("=");
    }
    gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)), cAlto/2+2);
    printf("%s", opc1);
    printf("|");
    //OPCION 2
    Color(BLACK, opcionSeleccionada == 2 ? LGREEN : WHITE);
    gotoxy(((cAncho+strlen(opc2))/2)-1, cAlto/2+1);
    for(int i=0; i<=strlen(opc2)+1;i++)
    {
        printf("=");
    }

    gotoxy(((cAncho+strlen(opc2))/2)-1, cAlto/2+3);
    for(int i=0; i<=strlen(opc2)+1;i++)
    {
        printf("=");
    }
    gotoxy(((cAncho+strlen(opc2))/2-1), cAlto/2+2);
    printf("|");
    gotoxy(((cAncho+strlen(opc2))/2), cAlto/2+2);
    printf("%s", opc2);
    printf("|");
    mostrarCursor();
}
int simulacroDeElegirOpc(char *parrafo[], char opc1[], char opc2[], int cAncho, int cAlto, int cantidaDeOraciones)
{

    int opc=1;
    bool repite=true;
    centrarParrafo(cAncho, cAlto, parrafo, cantidaDeOraciones);
    do{
        centrarDosOpc(opc1, opc2, cAncho, (cAlto+cantidaDeOraciones/2), opc);
        ocultarCursor();
        char tecla=getch();
        if(tecla==teclDerecha||tecla==teclIzquierda)
        {
             opc = (opc == 1) ? 2 : 1;
        }
        else if(tecla==teclEnter)
        {

            opc==1 ? opcionTitileraOpc1(opc1, opc2, cAncho, (cAlto+cantidaDeOraciones/2)) : opcionTitileraOpc2(opc1, opc2, cAncho,(cAlto+cantidaDeOraciones/2));
            repite=false;
        }

    }while(repite);
    mostrarCursor();
    return opc;
}

void opcionTitileraOpc1(char opc1[], char opc2[], int cAncho, int cAlto)
{
    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);

        gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)-1), cAlto/2+1);
        for(int i=0; i<=strlen(opc1)+1;i++)
        {
            printf("=");
        }

        gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)-1), cAlto/2+2);
        printf("|");

        gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)-1), cAlto/2+3);
        for(int i=0; i<=strlen(opc1)+1;i++)
        {
            printf("=");
        }
        gotoxy((cAncho/2-strlen(opc1)-(strlen(opc2)/2)), cAlto/2+2);
        printf("%s", opc1);
        printf("|");
        usleep(150000);
    }
    mostrarCursor();
    Color(BLACK, LGREEN);
}
void opcionTitileraOpc2(char opc1[], char opc2[], int cAncho, int cAlto)
{

    ocultarCursor();
    for(int i=0; i<6; i++)
    {
        Color(BLACK, i%2==0 ? WHITE:LGREEN);
        gotoxy(((cAncho+strlen(opc2))/2)-1, cAlto/2+1);
        for(int i=0; i<=strlen(opc2)+1;i++)
        {
            printf("=");
        }

        gotoxy(((cAncho+strlen(opc2))/2)-1, cAlto/2+3);
        for(int i=0; i<=strlen(opc2)+1;i++)
        {
            printf("=");
        }
        gotoxy(((cAncho+strlen(opc2))/2-1), cAlto/2+2);
        printf("|");
        gotoxy(((cAncho+strlen(opc2))/2), cAlto/2+2);
        printf("%s", opc2);
        printf("|");
        usleep(150000);
    }
    mostrarCursor();
    Color(BLACK, LGREEN);
}
int contarOracionesParrafo(char *parrafo[])
{
    int cont=0;
    while(parrafo[cont])//MIENTRAS QUE PARRAFO TENGA CADENAS DE STRINGS
    {
        cont++;//ME MUEVO, HASTA ENCONTRAR NULL
    }
    return cont;
}

void centrarParrafo(int cAncho, int cAlto, char *parrafo[], int cantidadDeOraciones)
{

    for(int i=0;i<cantidadDeOraciones;i++)
    {
        centrarOracion(parrafo[i], (cAncho-strlen(parrafo[i]))/2, (cAlto-cantidadDeOraciones)/2-2+i);
    }
    Color(BLACK, WHITE);
}

void centrarOracion(char oracion[], int cAncho, int cAlto)
{
    ocultarCursor();
    for(int j=0; j<strlen(oracion); j++)
    {
        Color(BLACK, LGREEN);
        gotoxy(cAncho+1, cAlto);
       // abrirBold();
        printf("|");
       // cerrarBold();
        gotoxy(cAncho,cAlto);
        printf("%c", oracion[j]);
        cAncho++;
        usleep(80000);
    }

    gotoxy(cAncho,cAlto);
    printf("  ");
    mostrarCursor();
}

void ocultarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Oculta el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void mostrarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;  // Mostrar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void abrirBold()
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

//     Obtener el atributo actual de la consola
    GetConsoleScreenBufferInfo(hConsole, &csbi);

// Establecer el bit de intensidad en 1 (negrita)
    csbi.wAttributes |= FOREGROUND_INTENSITY;

    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

void cerrarBold()
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

//     Obtener el atributo actual de la consola
    GetConsoleScreenBufferInfo(hConsole, &csbi);

// Establecer el bit de intensidad en 1 (negrita)
    csbi.wAttributes &= ~FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);

}

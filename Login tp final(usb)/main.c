#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cFront.h"
#include "Login.h"



int main()
{
    HWND hwnd = GetConsoleWindow();     ShowWindow(hwnd, SW_MAXIMIZE); /// abre la consola en pantalla completa
    char nombreArchivo[] ={"jugadores.bin"};
    printf("\n");


    IniciarSesionORegistrarse(nombreArchivo);



return 0;

}








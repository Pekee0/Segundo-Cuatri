#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#define teclEnter 13
#define teclIzquierda 75
#define teclDerecha 77
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

void  maximizarPantalla();//AGRANDA LA CONSOLA AL MAXIMO
void deshabilitarMouse();//DESAHBILITA LA OPCION DE CLICKEAR LA CONSOLA
void borrarLinea(int y);//BORRA LA LINEA DEL EJE Y QUE SE RECIBE Y DEJA LA POSICION EN ESA COORDENADA
int contarOracionesParrafo(char *parrafo[]);//CUENTA LAS ORACIONES DE UN PARRAFO
void centrarParrafo(char *parrafo[], int anchoConsola, int altoConsola);//CENTRA UN PARRAFO, CANTIDAD DE ORACIONES ES contarOracionesParrafo
void centrarOracion(char oracion[], int anchoConsola, int altoConsola);//CENTRA LA ORACION, INVOCADA EN centrarParrafo
void obtenerDimensionesConsola(int* anchoConsola, int* altoConsola);//MODIFICA LOS PARAMETROS CON LA INFORMACION DE LOS LIMITES DE LA PANTALLA
void gotoxy(int x, int y);//LLEVA EL CURSOR A LAS COORDENADAS
void ocultarCursor();//OCULTA EL CURSOR
void mostrarCursor();//MUESTRA EL CURSOR
void abrirBold();//AUMENTA LA INTENSIDAD DE LA LETRA
void cerrarBold();//VUELVE LA INTENSIDAD DE LA LETRA A LA NORMALIDAD
void Color(int Background, int Text);//CAMBIA LOS COLORES DE LA LINEA ACTUAL DE LA CONSOLA
void niBlancoNiNegro();//EL COLOR DE LA LINEA ACTUAL DE LA CONSOLA NO SERA NI BLANCO NI NEGRO NI LGREY
int simulacroDeElegirOpc(char opc1[], char opc2[], int anchoConsola, int altoConsola);//MUESTRA COMO SELECCIONAS UNA OPCION O LA OTRA, RETORNA 1 o 2
void centrarDosOpc(char opc1[], char opc2[], int anchoConsola, int altoConsola, int opcionSeleccionada, int espaciado);//PRINTEA LAS DOS OPCIONES DE FORMA CENTRADA INVOCADA EN simulacroDeElegirOpc
void imprimirOpcionALaIzquierda(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//IMPRIME UNA OPCION CORTA A LA IZQUIERDA INVOCADA EN centrarDosOpc
void imprimirOpcionALaDerecha(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//IMPRIME UNA OPCION LARGA A LA IZQUIERDA INVOCADA EN centrarDosOpc
void opcionTitileraOpc1(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//HACE TITILEAR LA OPCION CORTA DE LA IZQUIERDA INVOCADA EN simulacroDeElegirOpc
void opcionTitileraOpc2(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//HACE TITILEAR LA OPCION CORTA DE LA DERECHA INVOCADA EN simulacroDeElegirOpc
int simulacroDeCentrarUnaOpc(char opc1[], int anchoConsola, int altoConsola);//IMPRIME UNA OPCION EN EL CENTRO DE LA PANTALLA DEBAJO DEL TEXTO RETORNA SIEMPRE 1
void imprimirUnaOpcionCentrada(char opc1[], int anchoConsola, int altoConsola);//IMPRIME LA OPCION, INVOCADA EN simulacroDeCentrarUnaOpc
void opcionTitileraUnaOpcion(char opc1[], int anchoConsola, int altoConsola);//HACE QUE TITILEA LA OPCION SELECCIONADA, INVOCADA EN simulacroDeCentrarUnaOpc
int pruebaElegirFecha(char opc0[], char opc1[], char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola);//FUNCION PARA MOSTRAR Y SELECCIONAR FECHA DE VIAJE
void centrarLasFechas(char opc0[], char opc1[], char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola, int opc, int espaciado);//FUNCION QUE MUESTRA LAS FECHAS INVOCADA EN pruebaElegirFecha
void primeraFecha(char opc0[], char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//IMPRIME LA PRIMER FECHA
void segundaFecha(char opc1[], char opc2[],int anchoConsola, int altoConsola, int espaciado);//IMPRIME LA SEGUNDA FECHA
void tercerFecha(char opc2[], int anchoConsola, int altoConsola);//IMPRIME LA TERCER FECHA
void cuartaFecha(char opc2[], char opc3[], int anchoConsola, int altoConsola, int espaciado);//IMPRIME LA CUARTA FECHA
void quintaFecha(char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola, int espaciado);//IMPRIME LA QUINTA FECHA
void opcionTitileraPrimerFecha(char opc0[], char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//HACE QUE TITILE LA PRIMER FECHA
void opcionTitileraSegundaFecha(char opc1[], char opc2[], int anchoConsola, int altoConsola, int espaciado);//HACE QUE TITILE LA SEGUNDA FECHA
void opcionTitileraTercerFecha(char opc2[], int anchoConsola, int altoConsola);//HACE QUE TITILE LA TERCERA FECHA
void opcionTitileraCuartaFecha(char opc2[], char opc3[], int anchoConsola, int altoConsola, int espaciado);//HACE QUE TITILE LA CUARTA FECHA
void opcionTitileraQuintaFecha(char opc2[], char opc3[], char opc4[], int anchoConsola, int altoConsola, int espaciado);//HACE QUE TITILE LA QUINTA FECHA
void pruebaCuadro(int x, int y, int boxWidth, int boxHeight);//CREA UN RECUADRO AL REDEDOR DE LA PANTALLA X & BOXWIDTH DEBEN SER ANCHOCONSOLA, Y & BOXHEIGHT DEBEN SER ALTOCONSOLA
void mostrarLineaCreditos(char* parrafo[],int i, int anchoConsola, int altoConsola);//MUESTRA LAS LINEAS ASCENDENTES DE LOS CREDITOS, INVOCADA EN mostrarCreditos
void mostrarCreditos(char *parrafo[], int anchoConsola, int altoConsola);//MUESTRA TODA LA ANIMACION DE LOS CREDITOS
void fletarPrimerElementoArray(char *A[]);//ELIMINA EL PRIMER ELEMENTO DE UN ARRAY, INOVACADA EN mostrarCreditos
void centrarParrafoEjeX(char *p[], int anchoConsola, int y);//CENTRA UN PARRAFO EN EL EJE X, INVOCADA EN mostrarCreditos
void centrarOracionEjeX(char o[], int anchoConsola, int y);//CENTRA UNA ORACION EN EL EJE X, INVOCADA EN centrarParrafoEjeX
void borrarDeAbajoParaArriba(int y);//DESDE EL EJE Y PROPORCIONADO, TODO LO QUE ESTE ARRIBA SE BORRA
void pruebaMostrarLogros(char logro[], int anchoConsola, int altoConsola);//MOSTRAR LOGRO DE FORMA ANIMADA HARDCODEADA
void pruebaNuevLogroDesbloqueado(char logro[], int anchoConsola, int altoConsola, int y);//PRINTEA ANIMACION DE NUEVO LOGRO
void reproducirWav(char soundFX[]);//REPRODUCE UN WAV UNA VEZ
void reproducirWavBucle(char soundFX[]);//REPRODUCIR UN EN BUCLE
void detenerReproducionWav();//FRENAR WAV

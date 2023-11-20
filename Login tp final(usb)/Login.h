#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

typedef struct
{
    int idLogro;
    char NombreLogro[50];
    char Descripcion[100];
    int obtenido; /// funciona como un bool

}logros;

typedef struct /// posible que se trate como un arreglo
{
    char nombre[50];
    int costo;
    int comprado; /// funciona como un bool

}stInventario;

typedef struct
{
    int activo;
    char Nombre[20];
    int puntaje;
    int dinero;
    logros logros[20];
    int UltimoNodo;
    stInventario objetos[5];
    int comprado;

}player;

typedef struct nodoPuntajes
{
    int puntaje;
    char nombre[20];
    struct nodoPuntajes * sig;
    struct nodoPuntajes * ante;

}nodoPuntajes;

/// FUNCION PRINCIPAL

int IniciarSesionORegistrarse( char nombreArchivo[]);

/// FUNCIONES DEL PERFIL
player crearPerfil(char nombreArchivo[]);
void CrearLogros(logros Logros[]);
void agregarPlayerToArchivo(char nombreArchivo[], player nuevo);
int buscarPlayerArchivo(char nombreArchivo[], char nombreBuscado[]);
void inicObjetos(stInventario dato[]);
player buscaryRetornarPlayerArchivo(char nombreArchivo[], char nombreBuscado[]);
player NuevaPartida(char nombreArchivo[], int ancho, int alto);
player CargarPartida(char nombreArchivo[], int ancho, int alto);
void MiPerfil(char nombreArchivo[],int alto,int ancho);
player ActivarDesactivarcuenta(char nombreArchivo[],player dato, int opc);
player guardarPartida(char nombreArchivo[], player dato);
player actualizarLogros(player a, player b);
player actualizarObjetos(player a, player b);
/// FUNCIONES DEL PUNTAJE
nodoPuntajes * iniclista();
nodoPuntajes * crearNodoPuntaje(int puntaje,char nombre[]);
nodoPuntajes * AgregarPpioPuntaje(nodoPuntajes * lista, nodoPuntajes * nuevo);
nodoPuntajes * agregarEnOrdenPuntajes(nodoPuntajes * lista,nodoPuntajes * nuevo);
nodoPuntajes * pasarArchivoToListaPuntajes(char nombreArchivo[], nodoPuntajes * lista);

/// FUNCIONES DE MUESTRA
void printearLogo();
void mostrarPlayers(char nombreArchivo[]);
void  mostrarDataPlayer(player aux);
void mostrarPuntajes(nodoPuntajes * lista);
void mostrarLogros(player dato);


#endif // LOGIN_H_INCLUDED

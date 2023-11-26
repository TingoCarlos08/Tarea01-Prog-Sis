#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 50
#define MAX_USUARIOS 10
#define MAX_VENTAS 100

typedef struct Producto {
  float precioCompra;
  int cantidad;
  char nombre[50];
  char categoria[50];
  char marca[50];
  char codigo[50];
  char bodega[50];
} Producto;

typedef struct Usuario {
  int tipo; // 0: Administrador, 1: Bodeguero, 2: Vendedor
  char nombre[50];
  char clave[50];
} Usuario;

typedef struct {
  float precioVenta;
  int cantidad;
  char local[50];
  char vendedor[50];
  char fechaVenta[50];
} RegistroVenta;

void leerUsuariosDesdeArchivo(Usuario usuarios[MAX_USUARIOS],
                              int *cantidad_usuarios);
void escribirUsuariosEnArchivo(Usuario usuarios[MAX_USUARIOS],
                               int cantidad_usuarios);
void crearUsuario(Usuario usuarios[MAX_USUARIOS], int *cantidad_usuarios);
void actualizarUsuario(Usuario usuarios[MAX_USUARIOS]);

void leerProductosDesdeArchivo(Producto productos[MAX_PRODUCTOS],
                               int *cantidad_productos);
void escribirProductosEnArchivo(Producto productos[MAX_PRODUCTOS],
                                int cantidad_productos);
void crearProducto(Producto productos[MAX_PRODUCTOS]);
void actualizarProducto(Producto productos[MAX_PRODUCTOS]);

void leerVentasDesdeArchivo(RegistroVenta ventas[], int *totalVentas);
void escribirVentasEnArchivo(RegistroVenta ventas[], int totalVentas);
void venderProducto(Producto productos[MAX_PRODUCTOS], RegistroVenta ventas[],
                    int *totalVentas, Usuario usuarios[MAX_USUARIOS]);

void registrarUsuario(Usuario usuarios[MAX_USUARIOS], int *cantidad_usuarios);
int iniciarSesion(Usuario usuarios[MAX_USUARIOS], int cantidad_usuarios);

#endif
#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 50
#define MAX_USUARIOS 10

typedef struct Producto{
  char nombre[50];
  char categoria[50];
  char marca[50];
  char codigo[50];
  float precioCompra;
  char bodega[50];
int cantidad;
} Producto;

typedef struct Usuario{
  char nombre[50];
  int tipo; // 0: Administrador, 1: Bodeguero, 2: Vendedor
} 

Usuario;

typedef struct {
  char local[50];
  char vendedor[50];
  char fechaVenta[50];
  float precioVenta;
  int cantidad;
} 

RegistroVenta;

void crearUsuario(Usuario usuarios[MAX_USUARIOS], int *cantidad_usuarios);


void actualizarUsuario(Usuario usuarios[MAX_USUARIOS]);


void crearProducto(Producto productos[MAX_PRODUCTOS]);


void actualizarProducto(Producto productos[MAX_PRODUCTOS]);


void venderProducto(Producto productos[MAX_PRODUCTOS], RegistroVenta ventas[], int *totalVentas);

#endif
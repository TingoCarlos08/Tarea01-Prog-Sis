#include <stdio.h>
#include <string.h>
#include "funciones.h"

int cantidad_productos = 0;
int cantidad_usuarios = 0;
int totalVentas = 0;
RegistroVenta ventas[MAX_PRODUCTOS];

void crearUsuario(struct Usuario usuarios[MAX_USUARIOS], int *cantidad_usuarios){
  // Lógica para crear un nuevo usuario
  printf("Ingrese el nombre del usuario: ");
  scanf("%s", usuarios[*cantidad_usuarios].nombre);
struct Producto productos[MAX_PRODUCTOS];
  printf("Ingrese el tipo de usuario (0: Administrador, 1: Bodeguero, 2: Vendedor): ");
  scanf("%d", &usuarios[*cantidad_usuarios].tipo);
  cantidad_usuarios++; // Incrementamos la cantidad de usuarios
}
void actualizarUsuario(struct Usuario usuarios[MAX_USUARIOS]){
  // Lógica para actualizar un usuario existente
  char nombre[50];
  int encontrado = 0;
  printf("Ingrese el nombre del usuario a actualizar: ");
  scanf("%s", nombre);
  for (int i = 0; i < cantidad_usuarios; i++) {
    if (strcmp(usuarios[i].nombre, nombre) == 0) {
      printf("Ingrese el nuevo tipo de usuario (0: Administrador, 1: Bodeguero, 2: Vendedor): ");
      scanf("%d", &usuarios[i].tipo);
      encontrado = 1;
      break;
    }
  }
  if (!encontrado) {
    printf("No se encontró el usuario.\n");
  }
}
void crearProducto(Producto productos[MAX_PRODUCTOS]){
  // Lógica para crear un nuevo producto
  printf("Ingrese el nombre del producto: ");
  scanf("%s", productos[cantidad_productos].nombre);
  printf("Ingrese la categoría del producto: ");
  scanf("%s", productos[cantidad_productos].categoria);
  printf("Ingrese la marca del producto: ");
  scanf("%s", productos[cantidad_productos].marca);
  printf("Ingrese el código del producto: ");
  scanf("%s", productos[cantidad_productos].codigo);
  printf("Ingrese el precio de compra del producto: ");
  scanf("%f", &productos[cantidad_productos].precioCompra);
  printf("Ingrese la bodega del producto: ");
  scanf("%s", productos[cantidad_productos].bodega);
  cantidad_productos++; // Incrementamos la cantidad de productos
}
void actualizarProducto(Producto productos[MAX_PRODUCTOS]){
  // Lógica para actualizar un producto existente
  char codigo[50];
  int encontrado = 0;
  printf("Ingrese el código del producto a actualizar: ");
  scanf("%s", codigo);
  for (int i = 0; i < cantidad_productos; i++) {
    if (strcmp(productos[i].codigo, codigo) == 0) {
      printf("Ingrese el nuevo precio de compra del producto: ");
      scanf("%f", &productos[i].precioCompra);
      encontrado = 1;
      break;
    }
  }
  if (!encontrado) {
    printf("No se encontró el producto.\n");
  }
}
void venderProducto(struct Producto productos[MAX_PRODUCTOS], RegistroVenta ventas[], int *totalVentas){
  // Lógica para vender un producto y registrar la venta
  char codigo[50];
  int encontrado = 0;
  int cantidad;
  printf("Ingrese el código del producto a vender: ");
  scanf("%s", codigo);
  for (int i = 0; i < cantidad_productos; i++) {
    if (strcmp(productos[i].codigo, codigo) == 0) {
      printf("Ingrese la cantidad del producto a vender: ");
      scanf("%d", &cantidad);
      // Verificamos si la cantidad ingresada es menor o igual a la cantidad en bodega
      if (cantidad <= productos[i].cantidad) {
        // Actualizamos la cantidad en bodega
        productos[i].cantidad -= cantidad;
        // Registramos la venta
        strcpy(ventas[*totalVentas].local, "Local");
        strcpy(ventas[*totalVentas].vendedor, "Vendedor");
        strcpy(ventas[*totalVentas].fechaVenta, "Fecha");
        ventas[*totalVentas].precioVenta = productos[i].precioCompra * cantidad;
        ventas[*totalVentas].cantidad = cantidad;
        (*totalVentas)++; // Incrementamos el total de ventas
        encontrado = 1;
        break;
      } else {
        printf("No hay suficiente cantidad del producto en bodega.\n");
        encontrado = 1;
        break;
      }
    }
  }
  if (!encontrado) {
    printf("No se encontró el producto.\n");
  }
}
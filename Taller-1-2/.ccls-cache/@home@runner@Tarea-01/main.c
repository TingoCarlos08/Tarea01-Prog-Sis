#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int opcion;
  int op;
  int tipoUsuario;
  int totalVentas = 0;
  struct Producto productos[MAX_PRODUCTOS];
  struct Usuario usuarios[MAX_USUARIOS];
  RegistroVenta ventas[MAX_VENTAS];
  int cantidad_usuarios = 0;
  int cantidad_productos = 0;

  leerUsuariosDesdeArchivo(usuarios, &cantidad_usuarios);
  leerVentasDesdeArchivo(ventas, &totalVentas);
  printf("Registro de Usuario\n");
  registrarUsuario(usuarios, &cantidad_usuarios);
  escribirUsuariosEnArchivo(usuarios, cantidad_usuarios);
  printf("Inicio de Sesión\n");
  tipoUsuario = iniciarSesion(usuarios, cantidad_usuarios);

  if (tipoUsuario == -1) {
    printf("Fallo al inicio de sesión\n");
    return 0;
  }

  do {
    switch (tipoUsuario) {
    case 0: //Menú Administrador
      printf("Menú de Administrador\n");
      printf("1. Crear o actualizar usuarios\n");
      printf("2. Crear o actualizar productos\n");
      printf("3. Vender productos\n");
      printf("0. Salir\n");
      break;

    case 1: //Menú Bodeguero
      printf("Menú Bodeguero\n");
      printf("1. Crear o actualizar productos\n");
      printf("2. Vender producto\n");
      printf("0. Salir\n");
      break;

    case 2: 
      printf("Menú vendedor\n");
      printf("1. Vender producto\n");
      printf("0. Regrear\n");
      printf("Ingrese una opción por favor: ");
      scanf("%d", &op);
      switch (op) {
      case 1:
        venderProducto(productos, ventas, &totalVentas, usuarios);
        escribirVentasEnArchivo(ventas, totalVentas);
        break;
      case 0:
        break;
      default:
        printf("Opción no válida.\n");
        break;
      }
      break;
    default:
      printf("Tipo de usuario no válido.\n");
      return 0;
    }
    printf("Ingrese una opción por vaor: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      if (tipoUsuario == 0) {
        printf("Crear o actualizar usuarios.\n");
        printf("1. Crear usuario\n");
        printf("2. Actualizar usuario\n");
        printf("0. Regresar\n");

        printf("Ingrese opción: ");
        scanf("%d", &op);
        switch (op) {
        case 1:
          crearUsuario(usuarios, &cantidad_usuarios);
          escribirUsuariosEnArchivo(usuarios, cantidad_usuarios);
          break;
        case 2:
          actualizarUsuario(usuarios);
          break;
        case 0:
          break;
        default:
          printf("Opción no válida.\n");
          break;
        }
      } else if (tipoUsuario == 1) {
        printf("Crear o actualizar productos:\n");
        printf("1. Crear Producto\n");
        printf("2. Actualizar Producto\n");
        printf("0. Volver\n");
        printf("Ingrese una opción por favor:");
        scanf("%d", &op);
        switch (op) {
        case 1:
          crearProducto(productos);
          break;
        case 2:
          actualizarProducto(productos);
          break;
        case 0:
          break;
        default:
          printf("Opción no válida\n");
          break;
        }
      } else {
        printf("Su tipo de usuario no permite realizar esta acción\n");
      }
      break;

    case 2:
      if (tipoUsuario == 2) {
        printf("------------- Vender Producto -----------\n");
        printf("1. Vender Producto\n");
        printf("0. Volver\n");
        printf("Ingrese opción: ");
        scanf("%d", &op);
        switch (op) {
        case 1:
          venderProducto(productos, ventas, &totalVentas, usuarios);
          escribirVentasEnArchivo(ventas, totalVentas);
          break;
        case 0:
          break;
        default:
          printf("Opción no válida\n");
          break;
        }
      } else {
        printf("Su tipo de usuario no permite realizar esta acción\n");
      }
      break;

    case 0:
      break;
    default:
      printf("Opción no válida\n");
      break;
    }
    printf("¿Desea continuar? (1 (Si) o 0  (No))\n");
    scanf("%d", &opcion);

  } while (opcion != 0);

  return 0;
}
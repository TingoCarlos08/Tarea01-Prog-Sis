#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int opcion;
  int sn;
  int tipoUsuario; // Variable para almacenar el tipo de usuario actual

  int totalVentas = 0;
  
  struct Producto productos[MAX_PRODUCTOS];
  struct Usuario usuarios[MAX_USUARIOS];
  RegistroVenta ventas[MAX_VENTAS];

  int cantidad_usuarios = 0;
  int cantidad_productos = 0;

  leerUsuariosDesdeArchivo(usuarios, &cantidad_usuarios);
  leerVentasDesdeArchivo(ventas, &totalVentas);

  // Menú de registro de usuario
  printf("------------- Registro de Usuario -----------\n");
  registrarUsuario(usuarios, &cantidad_usuarios);
  escribirUsuariosEnArchivo(usuarios, cantidad_usuarios);

  // Menú de inicio de sesión
  printf("------------- Inicio de Sesión -----------\n");
  tipoUsuario = iniciarSesion(usuarios, cantidad_usuarios);

  if (tipoUsuario == -1) {
    // Cierre del programa si el inicio de sesión falla
    printf("Cierre del programa debido a inicio de sesión fallido.\n");
    return 0;
  }

  do {
    // Mostrar menú según el tipo de usuario
    switch (tipoUsuario) {
    case 0: // Administrador
      printf("------------- Menú Administrador -----------\n");
      printf("1. Crear/Actualizar Usuarios\n");
      printf("2. Crear/Actualizar Productos\n");
      printf("3. Vender Producto\n");
      printf("0. Salir\n");
      break;

    case 1: // Bodeguero
      printf("------------- Menú Bodeguero -----------\n");
      printf("1. Crear/Actualizar Productos\n");
      printf("2. Vender Producto\n");
      printf("0. Salir\n");
      break;

    case 2: // Vendedor
      printf("------------- Menú Vendedor -----------\n");
      printf("1. Vender Producto\n");
      printf("0. Volver\n");

      // Input opción del usuario
      printf("Ingrese opción: ");
      scanf("%d", &sn);

      switch (sn) {
      case 1:
        venderProducto(productos, ventas, &totalVentas, usuarios);
        escribirVentasEnArchivo(ventas, totalVentas);
        break;
      case 0:
        // Volver al menú principal
        break;
      default:
        printf("Opción no válida.\n");
        break;
      }
      break;

    default:
      printf("Tipo de usuario no válido. Cierre del programa.\n");
      return 0;
    }

    // Input opción del usuario
    printf("Ingrese opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      if (tipoUsuario == 0) {
        // Administrador: Solo tiene permisos para crear o actualizar Usuarios
        printf("------------- Crear/Actualizar Usuarios -----------\n");
        printf("1. Crear Usuario\n");
        printf("2. Actualizar Usuario\n");
        printf("0. Volver\n");

        // Input opción del usuario
        printf("Ingrese opción: ");
        scanf("%d", &sn);

        switch (sn) {
        case 1:
          crearUsuario(usuarios, &cantidad_usuarios);
          escribirUsuariosEnArchivo(usuarios, cantidad_usuarios);
          break;
        case 2:
          actualizarUsuario(usuarios);
          break;
        case 0:
          // Volver al menú principal
          break;
        default:
          printf("Opción no válida.\n");
          break;
        }
      } else if (tipoUsuario == 1) {
        // Bodeguero: Solo tiene permisos para crear o actualizar Productos
        printf("------------- Crear/Actualizar Productos -----------\n");
        printf("1. Crear Producto\n");
        printf("2. Actualizar Producto\n");
        printf("0. Volver\n");

        // Input opción del usuario
        printf("Ingrese opción:");
        scanf("%d", &sn);

        switch (sn) {
        case 1:
          crearProducto(productos);
          break;
        case 2:
          actualizarProducto(productos);
          break;
        case 0:
          // Volver al menú principal
          break;
        default:
          printf("Opción no válida.\n");
          break;
        }
      } else {
        printf("Opción no válida para este tipo de usuario.\n");
      }
      break;

    case 2:
      if (tipoUsuario == 2) {
        // Solo Vendedor: Solo tiene permisos para vender productos
        printf("------------- Vender Producto -----------\n");
        printf("1. Vender Producto\n");
        printf("0. Volver\n");

        // Input opción del usuario
        printf("Ingrese opción: ");
        scanf("%d", &sn);

        switch (sn) {
        case 1:
          venderProducto(productos, ventas, &totalVentas, usuarios);
          escribirVentasEnArchivo(ventas, totalVentas);
          break;
        case 0:
          // Volver al menú principal
          break;
        default:
          printf("Opción no válida.\n");
          break;
        }
      } else {
        printf("Opción no válida para este tipo de usuario.\n");
      }
      break;

    case 0:
      // Salir del programa
      break;

    default:
      printf("Opción no válida.\n");
      break;
    }

    // Volver al menú principal
    printf("¿Desea continuar? (1 - Si, 0 - No)\n");
    scanf("%d", &opcion);

  } while (opcion != 0);

  return 0;
}
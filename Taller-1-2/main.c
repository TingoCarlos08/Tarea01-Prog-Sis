#include <stdio.h>
#include "funciones.h"

int main() {
  int opcion;

  // Se inicializan las variables
  int cantidad_productos = 0;
  int cantidad_usuarios = 0;
  int totalVentas = 0;
  RegistroVenta ventas[MAX_PRODUCTOS];

  // Se inicializan las estructuras
  struct Producto productos[MAX_PRODUCTOS];
  struct Usuario usuarios[10];


  // Mostrar menú
  do {
    printf("------------- Menú principal -----------\n");
    printf("1. Registrar usuario\n");
    // usuarios Administrador, Bodeguero, Vendedor 

    
    printf("2. Registrar producto\n");
    printf("3. Vender producto\n");
    printf("4. Salir\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
      case 1:
        crearUsuario(usuarios, &cantidad_usuarios);
        break;
      case 2:
          crearProducto(productos);
        break;
      case 3:
        crearProducto(productos);
        venderProducto(productos, ventas, &totalVentas);
        break;
      case 4:
        // Salir del programa
        printf("¡Hasta luego!\n");
        break;
      default:
        printf("Opción no válida.\n");
        break;
    }
  } while (opcion != 6);

  return 0;
}

#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int cantidad_productos = 0;
int cantidad_usuarios = 0;

void crearUsuario(Usuario usuarios[MAX_USUARIOS], int *cantidad_usuarios) {
  // Creación de un usuario nuevo
  printf("Ingrese el nombre del usuario: ");
  scanf("%s", usuarios[*cantidad_usuarios].nombre);
  printf("Ingrese la clave del usuario: ");
  scanf("%s", usuarios[*cantidad_usuarios].clave);
  printf("Ingrese el tipo de usuario (0: Administrador, 1: Bodeguero, 2: "
         "Vendedor): ");
  scanf("%d", &usuarios[*cantidad_usuarios].tipo);
  if (*cantidad_usuarios != 10) {
    (*cantidad_usuarios)++; // Se incrementa la cantidad de usuarios
  } else {
    printf("Máximo de usuarios alcanzado!\n");
  }
}

void actualizarUsuario(Usuario usuarios[MAX_USUARIOS]) {
  // Actualización de un usuario existente
  char nombre[50];
  int encontrado = 0;
  printf("Ingrese el nombre del usuario a actualizar: ");
  scanf("%s", nombre);
  for (int i = 0; i < cantidad_usuarios; i++) {
    if (strcmp(usuarios[i].nombre, nombre) == 0) {
      printf("Ingrese el nuevo tipo de usuario (0: Administrador, 1: "
             "Bodeguero, 2: Vendedor): ");
      scanf("%d", &usuarios[i].tipo);
      encontrado = 1;
      break;
    }
  }
  if (!encontrado) {
    printf("No se encontró el usuario.\n");
  }
}

void registrarUsuario(Usuario usuarios[MAX_USUARIOS], int *cantidad_usuarios) {
  // Registro de un nuevo usuario
  if (*cantidad_usuarios < MAX_USUARIOS) {
    printf("Ingrese el tipo de usuario (0: Administrador, 1: Bodeguero, 2: "
           "Vendedor): ");
    scanf("%d", &usuarios[*cantidad_usuarios].tipo);
    printf("Ingrese el nombre del usuario: ");
    scanf("%s", usuarios[*cantidad_usuarios].nombre);
    printf("Ingrese la clave del usuario: ");
    scanf("%s", usuarios[*cantidad_usuarios].clave);
    (*cantidad_usuarios)++; // Se incrementa la cantidad de usuarios
    printf("Usuario registrado exitosamente.\n");
  } else {
    printf("No se pueden registrar más usuarios. Límite alcanzado.\n");
  }
}
int iniciarSesion(Usuario usuarios[MAX_USUARIOS], int cantidad_usuarios) {
  char nombreUsuario[50];
  char clave[50];
  int tipoUsuario = -1;
  printf("Ingrese su nombre de usuario: ");
  scanf("%s", nombreUsuario);
  printf("Ingrese su clave: ");
  scanf("%s", clave);
  for (int i = 0; i < cantidad_usuarios; i++) {
    if (strcmp(usuarios[i].nombre, nombreUsuario) == 0 &&
        strcmp(usuarios[i].clave, clave) == 0) {
      tipoUsuario = usuarios[i].tipo;
      break;
    }
  }
  if (tipoUsuario == -1) {
    printf("Nombre de usuario o clave incorrectos.\n");
  }
  return tipoUsuario;
}

void crearProducto(Producto productos[MAX_PRODUCTOS]) {
  // Creación de un nuevo producto
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
  printf("Ingrese la cantidad del producto: ");
  scanf("%d", &productos[cantidad_productos].cantidad);
  cantidad_productos++; // Se incrementa la cantidad de productos
  escribirProductosEnArchivo(productos, cantidad_productos);
}

void actualizarProducto(Producto productos[MAX_PRODUCTOS]) {
  // Actualización de un producto existente
  char codigo[50];
  int encontrado = 0;
  printf("Ingrese el código del producto a actualizar: ");
  scanf("%s", codigo);
  for (int i = 0; i < cantidad_productos; i++) {
    if (strcmp(productos[i].codigo, codigo) == 0) {
      printf("Ingrese el nuevo precio de compra del producto: ");
      scanf("%f", &productos[i].precioCompra);
      encontrado = 1;
      escribirProductosEnArchivo(productos, cantidad_productos);
      break;
    }
  }
  if (!encontrado) {
    printf("No se encontró el producto.\n");
  }
}

void venderProducto(Producto productos[MAX_PRODUCTOS], RegistroVenta ventas[],
                    int *totalVentas, Usuario usuarios[MAX_USUARIOS]) {
  char codigo[50];
  int encontrado = 0;
  int cantidad;

  leerProductosDesdeArchivo(productos, &cantidad_productos);

  printf("Ingrese el código del producto a vender: ");
  scanf("%s", codigo);

  for (int i = 0; i < cantidad_productos; i++) {
    if (strcmp(productos[i].codigo, codigo) == 0) {
      printf("Ingrese la cantidad del producto a vender: ");
      scanf("%d", &cantidad);

      // Verificamos si la cantidad ingresada es menor o igual a la cantidad en
      // bodega
      if (cantidad <= productos[i].cantidad) {
        // Actualizamos la cantidad en bodega
        productos[i].cantidad -= cantidad;

        // Registramos la venta
        time_t now;
        time(&now);
        struct tm *local = localtime(&now);
        strcpy(ventas[*totalVentas].local, "Local");
        strcpy(ventas[*totalVentas].vendedor, usuarios[0].nombre);
        strftime(ventas[*totalVentas].fechaVenta, 50, "%Y-%m-%d %H:%M:%S",
                 local);
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

void leerUsuariosDesdeArchivo(Usuario usuarios[MAX_USUARIOS],
                              int *cantidad_usuarios) {
  FILE *archivo = fopen("usuarios.txt", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo de usuarios");
    exit(EXIT_FAILURE);
  }
  while (fscanf(archivo, "%d %s %s", &usuarios[*cantidad_usuarios].tipo,
                usuarios[*cantidad_usuarios].nombre,
                usuarios[*cantidad_usuarios].clave) == 3) {
    (*cantidad_usuarios)++;
    if (*cantidad_usuarios == MAX_USUARIOS) {
      break;
    }
  }
  fclose(archivo);
}
void escribirUsuariosEnArchivo(Usuario usuarios[MAX_USUARIOS],
                               int cantidad_usuarios) {
  FILE *archivo = fopen("usuarios.txt", "w");
  if (archivo == NULL) {
    perror("Error al abrir el archivo de usuarios");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < cantidad_usuarios; i++) {
    fprintf(archivo, "%d %s %s\n", usuarios[i].tipo, usuarios[i].nombre,
            usuarios[i].clave);
  }
  fclose(archivo);
}

void leerProductosDesdeArchivo(Producto productos[MAX_PRODUCTOS],
                               int *cantidad_productos) {
  FILE *archivo = fopen("productos.txt", "r");
  if (archivo == NULL) {
    // Si existe un error se imprime el mensaje y se cierra el programa.
    perror("Error al abrir el archivo de productos");
    exit(EXIT_FAILURE);
  }

  // Leemos los productos desde el archivo
  while (fscanf(archivo, "%s %s %s %s %f %s %d",
                productos[*cantidad_productos].nombre,
                productos[*cantidad_productos].categoria,
                productos[*cantidad_productos].marca,
                productos[*cantidad_productos].codigo,
                &productos[*cantidad_productos].precioCompra,
                productos[*cantidad_productos].bodega,
                &productos[*cantidad_productos].cantidad) == 7) {
    (*cantidad_productos)++;
    if (*cantidad_productos == MAX_PRODUCTOS) {
      printf("No caben mas productos");
      break;
    }
  }

  fclose(archivo);
}

void escribirProductosEnArchivo(Producto productos[MAX_PRODUCTOS],
                                int cantidad_productos) {
  FILE *archivo = fopen("productos.txt", "w");
  if (archivo == NULL) {
    // Si existe un error se imprime el mensaje y se cierra el programa.
    perror("Error al abrir el archivo de productos");
    exit(EXIT_FAILURE);
  }

  // Escribimos los productos en el archivo
  for (int i = 0; i < cantidad_productos; i++) {
    fprintf(archivo, "%s %s %s %s %.2f %s %d\n", productos[i].nombre,
            productos[i].categoria, productos[i].marca, productos[i].codigo,
            productos[i].precioCompra, productos[i].bodega,
            productos[i].cantidad);
  }

  fclose(archivo);
}

void leerVentasDesdeArchivo(RegistroVenta ventas[MAX_VENTAS],
                            int *totalVentas) {
  FILE *archivo = fopen("ventas.txt", "r");
  if (archivo == NULL) {
    // Si existe un error se imprime el mensaje y se cierra el programa.
    perror("Error al abrir el archivo de ventas");
    exit(EXIT_FAILURE);
  }

  // Leemos las ventas desde el archivo
  while (fscanf(archivo, "%s %s %s %f %d", ventas[*totalVentas].local,
                ventas[*totalVentas].vendedor, ventas[*totalVentas].fechaVenta,
                &ventas[*totalVentas].precioVenta,
                &ventas[*totalVentas].cantidad) == 5) {
    (*totalVentas)++;
    if (*totalVentas == MAX_VENTAS) {
      printf("No se puede realizar más ventas!");
      break;
    }
  }

  fclose(archivo);
}

void escribirVentasEnArchivo(RegistroVenta ventas[MAX_VENTAS],
                             int totalVentas) {
  FILE *archivo = fopen("ventas.txt", "w");
  if (archivo == NULL) {
    // Si existe un error se imprime el mensaje y se cierra el programa.
    perror("Error al abrir el archivo de ventas");
    exit(EXIT_FAILURE);
  }

  // Escribimos las ventas en el archivo
  for (int i = 0; i < totalVentas; i++) {
    fprintf(archivo, "%s %s %s %.2f %d\n", ventas[i].local, ventas[i].vendedor,
            ventas[i].fechaVenta, ventas[i].precioVenta, ventas[i].cantidad);
  }

  fclose(archivo);
}
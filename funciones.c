#include <stdio.h>
#include <string.h>
#include "funciones.h"

const int MAX_USUARIOS = 10;
Usuario usuarios[MAX_USUARIOS];
int cantidadUsuarios;

const int MAX_PRODUCTOS = 100;
Producto productos[MAX_PRODUCTOS];
int cantidadProductos;

const int MAX_VENTAS = 10;
Venta ventas[MAX_VENTAS];
int cantidadVentas;

///USUARIOS

void cargarUsuariosDesdeArchivo(const char *nombreArchivo, Usuario *usuarios, int *cantidadUsuarios) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    *cantidadUsuarios = 0;

    while (fscanf(archivo, "%s %d", usuarios[*cantidadUsuarios].nombre, (int*)&usuarios[*cantidadUsuarios].tipo) == 2) {
        (*cantidadUsuarios)++;
    }

    fclose(archivo);
}

void guardarUsuarioEnArchivo(const char *nombreArchivo, const Usuario *usuario, int cantidadUsuarios) {
    FILE *archivo = fopen(nombreArchivo, "a");  // Abrir en modo de adición (append)
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

  fprintf(archivo, "%s %d\n", usuario->nombre, (int)usuario->tipo);

    fclose(archivo);
}


void guardarUsuariosEnArchivo(const char *nombreArchivo, const Usuario *usuarios, int cantidadUsuarios) {
    FILE *archivo = fopen(nombreArchivo, "w");  // Abrir en modo de escritura (truncar el archivo)
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {
        fprintf(archivo, "%s %d\n", usuarios[i].nombre, (int)usuarios[i].tipo);
    }

    fclose(archivo);
}

// PRODUCTOS

void cargarProductosDesdeArchivo(const char *nombreArchivo, Producto *productos, int *cantidadProductos) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    *cantidadProductos = 0;

    while (fscanf(archivo, "%s %s %s %d %f %d",
                  productos[*cantidadProductos].nombre,
                  productos[*cantidadProductos].categoria,
                  productos[*cantidadProductos].marca,
                  &productos[*cantidadProductos].codigo,
                  &productos[*cantidadProductos].precioCompra,
                  &productos[*cantidadProductos].cantidadBodega) == 6) {
        (*cantidadProductos)++;
    }

    fclose(archivo);
}

void guardarProductosEnArchivo(const char *nombreArchivo, const Producto *productos, int cantidadProductos) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    for (int i = 0; i < cantidadProductos; i++) {
        fprintf(archivo, "%s %s %s %d %.2f %d\n",
                productos[i].nombre,
                productos[i].categoria,
                productos[i].marca,
                productos[i].codigo,
                productos[i].precioCompra,
                productos[i].cantidadBodega);
    }

    fclose(archivo);
}

// VENTAS
void cargarVentasDesdeArchivo(const char *nombreArchivo, Venta *ventas, int *cantidadVentas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    *cantidadVentas = 0;

    while (fscanf(archivo, "%s %s %s %f %d %d",
                  ventas[*cantidadVentas].local,
                  ventas[*cantidadVentas].vendedor,
                  ventas[*cantidadVentas].fechaVenta,
                  &ventas[*cantidadVentas].precioVenta,
                  &ventas[*cantidadVentas].codigoProducto,
                  &ventas[*cantidadVentas].cantidadVendida) == 6) {
        (*cantidadVentas)++;
    }

    fclose(archivo);
}

void guardarVentasEnArchivo(const char *nombreArchivo, const Venta *ventas, int cantidadVentas) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    for (int i = 0; i < cantidadVentas; i++) {
        fprintf(archivo, "%s %s %s %.2f %d %d\n",
                ventas[i].local,
                ventas[i].vendedor,
                ventas[i].fechaVenta,
                ventas[i].precioVenta,
                ventas[i].codigoProducto,
                ventas[i].cantidadVendida);
    }

    fclose(archivo);
}

void InicioSesion() {

    cargarUsuariosDesdeArchivo("usuarios.txt", usuarios, &cantidadUsuarios);

    printf("¡Bienvenido!\n");

    char nombreUsuario[50];
    printf("Ingrese su nombre de usuario: ");
    scanf("%s", nombreUsuario);

    int encontrado = 0;
    TipoUsuario tipoUsuario;

    for (int i = 0; i < cantidadUsuarios; i++) {
        if (strcmp(usuarios[i].nombre, nombreUsuario) == 0) {
            encontrado = 1;
            tipoUsuario = usuarios[i].tipo;
            break;
        }
    }

    if (encontrado) {
        switch (tipoUsuario) {
            case ADMINISTRADOR:
                printf("Hola %s, eres un administrador.\n", nombreUsuario);
              printf("-------------------------------------------------\n"); char opcion;
              printf("¿Quieres añadir un nuevo usuario? (y/n): ");
              scanf(" %c", &opcion);
              if (opcion == 'y' || opcion == 'Y') {
                  CrearUsuario(); // Llama a la función para crear usuario
                  printf("-------------------------------------------------\n");
              }
              printf("¿Quieres actualizar un usuario existente? (y/n): ");
              scanf(" %c", &opcion);

              if (opcion == 'y' || opcion == 'Y') {
                  ActualizarUsuario(); // Llama a la función para actualizar usuario
                  printf("-------------------------------------------------\n");
              }
                break;
            case BODEGUERO:
                printf("Hola %s, eres un bodeguero.\n", nombreUsuario);
              printf("-------------------------------------------------\n");       char opcion2;
              printf("¿Quieres añadir un nuevo producto? (y/n): ");
              scanf(" %c", &opcion2);
              if (opcion2 == 'y' || opcion2 == 'Y') {
                  CrearProducto(); // Llama a la función para crear usuario
                  printf("-------------------------------------------------\n");
              }
              printf("¿Quieres actualizar un producto existente? (y/n): ");
              scanf(" %c", &opcion2);

              if (opcion2 == 'y' || opcion2 == 'Y') {
                  ActualizarProducto(); // Llama a la función para actualizar usuario
                  printf("-------------------------------------------------\n");
              }
                break;
            case VENDEDOR:
                printf("Hola %s, eres un vendedor.\n", nombreUsuario);
             // printf("-------------------------------------------------\n");
             RegistrarVenta(); // Llama a la función para registrar venta
                break;
            default:
                printf("Tipo de usuario desconocido.\n");
        }
    } else {
        printf("Usuario no encontrado.\n");
    }
}

///USUARIOS

void CrearUsuario() {

    cargarUsuariosDesdeArchivo("usuarios.txt", usuarios, &cantidadUsuarios);

    Usuario nuevoUsuario;

    printf("Ingrese el nombre del nuevo usuario: ");
    scanf("%s", nuevoUsuario.nombre);

    printf("Seleccione el tipo de usuario (0: Administrador, 1: Bodeguero, 2: Vendedor): ");
    scanf("%d", (int*)&nuevoUsuario.tipo);

    // Validar que el tipo de usuario sea válido
    if (nuevoUsuario.tipo < ADMINISTRADOR || nuevoUsuario.tipo > VENDEDOR) {
        printf("Tipo de usuario no válido.\n");
        return;
    }

    // Añadir el nuevo usuario al arreglo y al archivo
    usuarios[cantidadUsuarios] = nuevoUsuario;
    cantidadUsuarios++;

    guardarUsuarioEnArchivo("usuarios.txt", &nuevoUsuario, cantidadUsuarios);

    printf("Usuario creado exitosamente.\n");
}

void ActualizarUsuario() {

    cargarUsuariosDesdeArchivo("usuarios.txt", usuarios, &cantidadUsuarios);

    char nombreUsuario[50];
    printf("Ingrese el nombre de usuario que desea actualizar: ");
    scanf("%s", nombreUsuario);

    int indiceUsuario = -1;

    // Buscar el índice del usuario en el arreglo
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (strcmp(usuarios[i].nombre, nombreUsuario) == 0) {
            indiceUsuario = i;
            break;
        }
    }

    if (indiceUsuario != -1) {
        printf("Usuario encontrado.\n");

        // Solicitar nuevo nombre y tipo
        printf("Ingrese el nuevo nombre del usuario: ");
        scanf("%s", usuarios[indiceUsuario].nombre);

        printf("Seleccione el nuevo tipo de usuario (0: Administrador, 1: Bodeguero, 2: Vendedor): ");
        scanf("%d", (int*)&usuarios[indiceUsuario].tipo);

        // Validar que el nuevo tipo de usuario sea válido
        if (usuarios[indiceUsuario].tipo < ADMINISTRADOR || usuarios[indiceUsuario].tipo > VENDEDOR) {
            printf("Tipo de usuario no válido. No se ha actualizado.\n");
            return;
        }

        // Guardar el arreglo actualizado en el archivo
        guardarUsuariosEnArchivo("usuarios.txt", usuarios, cantidadUsuarios);
        printf("Usuario actualizado exitosamente.\n");
    } else {
        printf("Usuario no encontrado. No se ha actualizado.\n");
    }
}

///PRODUCTOS

void CrearProducto() {

    cargarProductosDesdeArchivo("productos.txt", productos, &cantidadProductos);

    // Ingresar información del nuevo producto
    printf("Ingrese el nombre del nuevo producto: ");
    scanf("%s", productos[cantidadProductos].nombre);

    printf("Ingrese la categoría del nuevo producto: ");
    scanf("%s", productos[cantidadProductos].categoria);

    printf("Ingrese la marca del nuevo producto: ");
    scanf("%s", productos[cantidadProductos].marca);

    printf("Ingrese el código del nuevo producto: ");
    scanf("%d", &productos[cantidadProductos].codigo);

    printf("Ingrese el precio de compra del nuevo producto: ");
    scanf("%f", &productos[cantidadProductos].precioCompra);

    printf("Ingrese la cantidad en bodega del nuevo producto: ");
    scanf("%d", &productos[cantidadProductos].cantidadBodega);

    // Incrementar la cantidad total de productos
    cantidadProductos++;

    // Guardar el nuevo producto en el archivo
    guardarProductosEnArchivo("productos.txt", productos, cantidadProductos);

    printf("Producto creado exitosamente.\n");
}

void ActualizarProducto() {
    const int MAX_PRODUCTOS = 100;
    Producto productos[MAX_PRODUCTOS];
    int cantidadProductos;

    cargarProductosDesdeArchivo("productos.txt", productos, &cantidadProductos);

    int codigoBuscar;
    printf("Ingrese el número de código del producto que desea actualizar: ");
    scanf("%d", &codigoBuscar);

    int indiceProducto = -1;

    // Buscar el índice del producto en el arreglo
    for (int i = 0; i < cantidadProductos; i++) {
        if (productos[i].codigo == codigoBuscar) {
            indiceProducto = i;
            break;
        }
    }

    if (indiceProducto != -1) {
        printf("Producto encontrado.\n");

        // Solicitar nueva información para el producto
        printf("Ingrese el nuevo nombre del producto: ");
        scanf("%s", productos[indiceProducto].nombre);

        printf("Ingrese la nueva categoría del producto: ");
        scanf("%s", productos[indiceProducto].categoria);

        printf("Ingrese la nueva marca del producto: ");
        scanf("%s", productos[indiceProducto].marca);

        // No permitir cambiar el código del producto
        printf("Ingrese el nuevo precio de compra del producto: ");
        scanf("%f", &productos[indiceProducto].precioCompra);

        printf("Ingrese la nueva cantidad en bodega del producto: ");
        scanf("%d", &productos[indiceProducto].cantidadBodega);

        // Guardar el arreglo actualizado en el archivo
        guardarProductosEnArchivo("productos.txt", productos, cantidadProductos);
        printf("Producto actualizado exitosamente.\n");
    } else {
        printf("Producto no encontrado. No se ha actualizado.\n");
    }
}

// VENTAS
void RegistrarVenta() {

    cargarVentasDesdeArchivo("ventas.txt", ventas, &cantidadVentas);

    // Ingresar información de la nueva venta
    printf("Ingrese el local de la nueva venta: ");
    scanf("%s", ventas[cantidadVentas].local);

    printf("Ingrese el vendedor de la nueva venta: ");
    scanf("%s", ventas[cantidadVentas].vendedor);

    printf("Ingrese la fecha de la nueva venta (YYYY-MM-DD): ");
    scanf("%s", ventas[cantidadVentas].fechaVenta);

    printf("Ingrese el precio de venta de la nueva venta: ");
    scanf("%f", &ventas[cantidadVentas].precioVenta);

    printf("Ingrese el código del producto de la nueva venta: ");
    scanf("%d", &ventas[cantidadVentas].codigoProducto);

    printf("Ingrese la cantidad vendida de la nueva venta: ");
    scanf("%d", &ventas[cantidadVentas].cantidadVendida);

    // Incrementar la cantidad total de ventas
    cantidadVentas++;

    // Guardar la nueva venta en el archivo
    guardarVentasEnArchivo("ventas.txt", ventas, cantidadVentas);

    printf("Venta creada exitosamente.\n");
}

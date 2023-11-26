#ifndef FUNCIONES_H
#define FUNCIONES_H

// Enumeración para los tipos de usuarios
typedef enum {
    ADMINISTRADOR,
    BODEGUERO,
    VENDEDOR
} TipoUsuario;

// Estructura para los productos
typedef struct {
    char nombre[50];
    char categoria[50];
    char marca[50];
    int codigo;
    float precioCompra;
    int cantidadBodega;
} Producto;

// Estructura para los usuarios
typedef struct {
    char nombre[50];
    TipoUsuario tipo;
} Usuario;
// Estructura para las ventas
typedef struct {
    char local[50];
    char vendedor[50];
    char fechaVenta[20];
    float precioVenta;
    int codigoProducto;
    int cantidadVendida;
} Venta;
// Funciones
void cargarUsuariosDesdeArchivo(const char *nombreArchivo, Usuario *usuarios, int *cantidadUsuarios);
void guardarUsuariosEnArchivo(const char *nombreArchivo, const Usuario *usuarios, int cantidadUsuarios);
void guardarUsuarioEnArchivo(const char *nombreArchivo, const Usuario *usuario, int cantidadUsuarios);
void CrearUsuario();
void ActualizarUsuario();
void InicioSesion();

void cargarProductosDesdeArchivo(const char *nombreArchivo, Producto *productos, int *cantidadProductos);
void guardarProductosEnArchivo(const char *nombreArchivo, const Producto *productos, int cantidadProductos);
void CrearProducto();
void ActualizarProducto();

void cargarVentasDesdeArchivo(const char *nombreArchivo, Venta *ventas, int *cantidadVentas);
void guardarVentasEnArchivo(const char *nombreArchivo, const Venta *ventas, int cantidadVentas);
void RegistrarVenta();

#endif

//proveedor
#include<stdio.h>
#include<string.h>
#include "AdminProv.h"
#include "Productos_pedidos.h"
#include "Productos.h"

void modificar_perfilprov(AdminProv *mod); //modifica el perfil del proveedor. Recibe el estruct del perfil del proveedor

void mostrar_perfilprov(AdminProv perfil); //muestran el perfil del proveedor. Recibe el estruct del perfil del proveedor

int verificar_contrasenia(char cad[16]); //pide al usuario que introduzca su contrasenia y corrobora si la contrasenia es o no correcta.
// Recibe la contrasenia del proveedor

int mi_producto(char empresa[5],char gestor[5]); //Corrobora que el producto sobre el que se quiere hacer algo es provisto por el proveedor. Entra el id de la empresa
// del proveedor y el id del gestor del producto

int mi_pedido(ProductoPedido *pedidos,char busc[8],Producto *prod,AdminProv prov,int cantdad_productospedidos,int cantdad_prod); //Corrobora que el pedido sobre el que se quiere
//hacer algo es provisto por el proveedor. Recibe todos los estructs de pedidos, el id del pedido que se quiere manipular, todos los estructs de productos y
//el perfil del proveedor

void altaProveedor(AdminProv **proveedores, int *numProveedores);
void bajaProveedor(AdminProv **proveedores, int *numProveedores,char *id);
void buscarProveedor(AdminProv **proveedores, int *numProveedores);
void listarProveedores(AdminProv **proveedores, int *numProveedores);
void modificarProveedor(AdminProv **proveedores, int *numProveedores);

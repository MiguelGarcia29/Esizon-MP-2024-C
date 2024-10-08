#include "Transportista.h"

// Función para generar un ID único para un nuevo transportista
char* id_generator_trans(Transportista *t, int tamanio_vector) {
    int id_generada = 1;

    if (tamanio_vector != 0) {
        id_generada = atoi(t[tamanio_vector - 1].id_transp) + 1;
    }

    char* id = malloc(5 * sizeof(char)); // Se asigna memoria para el ID generado
    if (id == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }

    sprintf(id, "%04d", id_generada); // Se genera el ID con formato de 4 dígitos

    return id;
}

// Función para dar de alta un nuevo transportista
void alta_transportista(Transportista **t, int* tamanio_vector){

    Transportista nuevo_transportista;
    char *cadena = id_generator_trans(*t, *tamanio_vector); // Genera un nuevo ID para el transportista
    strcpy(nuevo_transportista.id_transp, cadena); // Asigna el ID generado al nuevo transportista
    free(cadena); // Libera la memoria asignada para el ID generado

    // Solicita al usuario información sobre el nuevo transportista
    printf("\nDime el nombre:");
    scanf("%20s", nuevo_transportista.nombre);
    flushInputBuffer();

    printf("\nDime el correo:");
    scanf("%30s", nuevo_transportista.email);
    flushInputBuffer();

    printf("\nDime la contraseña para acceder al sistema:");
    scanf("%15s", nuevo_transportista.contrasenia);
    flushInputBuffer();

    printf("\nDime el nombre de la empresa:");
    scanf("%20s", nuevo_transportista.nombre_empresa);
    flushInputBuffer();

    printf("\nDime la ciudad de reparto:");
    scanf("%20s", nuevo_transportista.ciudad_reparto);
    flushInputBuffer();

    *t = (Transportista *)realloc(*t, (*tamanio_vector + 1) * sizeof(Transportista));
    if (*t == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }
    (*t)[*tamanio_vector] = nuevo_transportista; // Guarda el nuevo transportista en el arreglo
    (*tamanio_vector)++;
}

// Función para dar de baja un transportista existente
void baja_transportista(Transportista *t , int* tamanio, char *id_baja){

    int encontrado = 0;

    // Busca el transportista con el ID dado y lo elimina del arreglo
    for(int i = 0 ; i < *tamanio ; i++) {
        if(strcmp(t[i].id_transp, id_baja) == 0){
            encontrado = 1;
            for(int j = i; j < *tamanio - 1; j++) {
                t[j] = t[j + 1];
            }
            (*tamanio)--; // Reduce el tamaño del arreglo
            printf("Transportista con ID %s ha sido dado de baja correctamente.\n", id_baja);
            break; // Sale del bucle una vez encontrado y eliminado el transportista
        }
    }

    if(encontrado == 0){
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

// Función para mostrar un listado de todos los transportistas dados de alta
void listado_transportista(Transportista *t, int tamanio){

    printf("ID Transportista - Nombre - Email - Contraseña - Nombre de la empresa - Ciudad de reparto\n");
    // Recorre el arreglo de transportistas y muestra la información de cada uno
    for(int i = 0 ; i < tamanio ; i++){
        printf("%s - %s - %s - %s - %s - %s\n", t[i].id_transp, t[i].nombre, t[i].email, t[i].contrasenia, t[i].nombre_empresa, t[i].ciudad_reparto);
    }
}

// Función para modificar el perfil de un transportista
void perfil_t(Transportista *t)
{
    // Muestra la información del transportista
    printf("ID Transportista: %s\n", t->id_transp);
    printf("Nombre: %s\n", t->nombre);
    printf("Contraseña: %s\n", t->contrasenia);
    printf("Email: %s\n", t->email);
    printf("Nombre de la empresa: %s\n", t->nombre_empresa);
    printf("Ciudad de reparto: %s\n", t->ciudad_reparto);

    // Solicita al usuario si desea modificar el perfil
    printf("¿Quieres modificar este perfil?\n");
    printf("1-Si\n");
    printf("2-No\n");
    int respuesta;
    scanf("%d", &respuesta);
    flushInputBuffer();

    // Si el usuario elige modificar el perfil, solicita la nueva información
    if(respuesta == 1) {
        printf("\nDime el nombre: ");
        scanf("%29s", t->nombre);
        flushInputBuffer();

        printf("\nDime el correo: ");
        scanf("%29s", t->email);
        flushInputBuffer();

        printf("\nDime la contraseña para acceder al sistema: ");
        scanf("%15s", t->contrasenia);
        flushInputBuffer();

        printf("\nDime el nombre de la empresa: ");
        scanf("%19s", t->nombre_empresa);
        flushInputBuffer();

        printf("\nDime la ciudad de reparto: ");
        scanf("%19s", t->ciudad_reparto);
        flushInputBuffer();
    }
}

// Función para realizar el reparto de productos asignados a un transportista
void reparto(ProductoPedido **pedidos, int *num_pedidos, char *id_transp) {
    // Variables locales
    int indice = 0;
    char id_producto[50];

    // Busca los productos asignados al transportista y en estado "enReparto"
    for (int i = 0; i < *num_pedidos; i++) {
        if (strcmp((*pedidos)[i].id_transp, id_transp) == 0 && strcmp((*pedidos)[i].estado_pedido, "enReparto") == 0) {
            // Muestra la información del producto
            printf("Productos asignados para reparto:\n");
            printf("ID Pedido: %s\n", (*pedidos)[i].id_pedido);
            printf("ID Producto: %s\n", (*pedidos)[i].id_prod);
            printf("Cantidad: %d\n", (*pedidos)[i].num_unid);
            printf("Fecha de entrega prevista: %s\n", (*pedidos)[i].fecha_entrega_prevista);
            printf("Importe: %.2f\n", (*pedidos)[i].importe);
            printf("-------------------------------------\n");
            indice = 1;
        }
    }

    // Si no se encontraron productos para repartir
    if (indice != 1) {
        printf("No se han encontrado pedidos asignados a esa ID\n");
    }
}

// Función para calcular la fecha de caducidad de un producto (7 días a partir de la fecha actual)
void fecha_caducidad(char *fecha)
{
    time_t rawtime;
    struct tm *info;

    // Obtiene la fecha y hora actual
    time(&rawtime);
    info = localtime(&rawtime);

    // Suma 7 días a la fecha actual
    rawtime += 7 * 24 * 60 * 60; // 7 días en segundos

    // Actualiza la estructura tm
    info = localtime(&rawtime);

    // Formatea la fecha y la guarda en la cadena proporcionada
    strftime(fecha, 11, "%d/%m/%Y", info);
}

// Función para realizar la entrega de un producto (en locker o domicilio)
void entrega(ProductoPedido **pedidos, CompartimentoLocker **comportamiento, int *num_pedidos, int *tamanio_compartimento, char *id_transp) {
    // Variables locales
    char id_producto[50];
    char contrasenia_locker[11];
    int encontrado = 0;
    int i = 0;

    // Solicita al usuario la ID del producto que desea entregar
    printf("Dime la id del producto que quieres entregar: ");
    fgets(id_producto, sizeof(id_producto), stdin);
    id_producto[strcspn(id_producto, "\n")] = '\0'; // Elimina el carácter de nueva línea

    // Busca el producto asociado a la ID ingresada y asignado al transportista
    while (i < *num_pedidos && encontrado == 0) {
        if (strcmp((*pedidos)[i].id_prod, id_producto) == 0 && strcmp((*pedidos)[i].id_transp, id_transp) == 0) {
            encontrado = 1;
            // Solicita al usuario el método de entrega (locker o domicilio)
            printf("¿Dónde lo quieres entregar?\n1-Locker\n2-Domicilio\n");
            int entrega;
            scanf("%d", &entrega);
            flushInputBuffer();
            switch (entrega) {
                case 1:
                    // Busca un compartimento de locker vacío para la entrega
                    for (int j = 0; j < *tamanio_compartimento; j++) {
                        if (strcmp((*pedidos)[i].id_locker, (*comportamiento)[j].id_locker) == 0 && strcmp((*comportamiento)[j].estado, "vacío") == 0) {
                            // Solicita al usuario el código numérico asignado al locker
                            printf("Dime el código numérico asignado al locker (10 dígitos): ");
                            fgets(contrasenia_locker, sizeof(contrasenia_locker), stdin);
                            contrasenia_locker[strcspn(contrasenia_locker, "\n")] = '\0'; // Elimina el carácter de nueva línea

                            // Asigna el código del locker al producto y actualiza su estado
                            strcpy((*pedidos)[i].cod_locker, contrasenia_locker);
                            strcpy((*comportamiento)[j].cod_locker, contrasenia_locker);
                            strcpy((*comportamiento)[j].estado, "ocupado");
                            char fecha[11];
                            obtener_fecha_actual(fecha);
                            strcpy((*comportamiento)[j].fecha_ocupacion, fecha);
                            printf("Producto entregado exitosamente en el locker.\n");

                            // Calcula y asigna la fecha de caducidad del producto en el locker
                            char fecha_vencimiento[11];
                            fecha_caducidad(fecha_vencimiento);
                            strcpy((*comportamiento)[j].fecha_caducidad, fecha_vencimiento);
                            return;
                        }
                    }
                    printf("No se encontró un locker vacío con la ID especificada.\n");
                    break;
                case 2:
                    // Actualiza el estado del producto como "entregado" si se entrega en domicilio
                    printf("Producto entregado exitosamente en el domicilio.\n");
                    strcpy((*pedidos)[i].estado_pedido, "entregado");
                    return;
                default:
                    printf("Esa opción no se contempla.\n");
                    break;
            }
            break;
        }
        i++;
    }

    // Si no se encuentra el producto con la ID ingresada o si no está asignado al transportista
    if (encontrado == 0) {
        printf("No se encuentra esa ID de producto asociada al transportista.\n");
    }
}

// Función para marcar productos no recogidos como devueltos
void retornarProductosNoRecogidos(ProductoPedido **productos, int *num_productos, Locker **lockers, int *num_lockers, char *localidad_consulta) {
    int i, j;
    char id_producto[50];

    // Solicita al usuario la ID del producto que desea marcar como devuelto
    printf("Ingrese el ID del producto que desea marcar como devuelto: ");
    fgets(id_producto, sizeof(id_producto), stdin);
    id_producto[strcspn(id_producto, "\n")] = '\0'; // Elimina el carácter de nueva línea

    // Busca el producto con la ID ingresada y en estado "enLocker"
    for (j = 0; j < *num_productos; j++) {
        if (strcmp((*productos)[j].id_locker, id_producto) == 0 && strcmp((*productos)[j].estado_pedido, "enLocker") == 0) {
            // Muestra la información del producto y solicita confirmación al usuario
            printf("Producto encontrado en el locker:\n");
            printf("ID Pedido: %s\n", (*productos)[j].id_pedido);
            printf("ID Producto: %s\n", (*productos)[j].id_prod);
            printf("Número de unidades: %d\n", (*productos)[j].num_unid);
            printf("Fecha de entrega prevista: %s\n", (*productos)[j].fecha_entrega_prevista);
            printf("Importe: %.2f\n", (*productos)[j].importe);
            printf("¿Desea marcar este producto como devuelto? (Sí/No): ");
            char respuesta[4];
            fgets(respuesta, sizeof(respuesta), stdin);

            // Si el usuario confirma, actualiza el estado del producto a "devuelto"
            if (strcmp(respuesta, "Sí\n") == 0 || strcmp(respuesta, "Si\n") == 0 || strcmp(respuesta, "sí\n") == 0 || strcmp(respuesta, "si\n") == 0) {
                strcpy((*productos)[j].estado_pedido, "devuelto");
                printf("Estado del producto actualizado correctamente.\n");
                return;
            } else {
                printf("El estado del producto no ha sido modificado.\n");
                return;
            }
        }
    }

    // Si no se encuentra el producto con la ID ingresada o no está en estado "enLocker"
    printf("No se encontró ningún producto con el ID especificado o no está en estado 'enLocker'.\n");
}

// Función para modificar los datos de un transportista existente
void modificar_transportista(Transportista **lista_transportistas, int *num_transportistas) {
    char id[9];

    // Solicita al usuario la ID del transportista a modificar
    printf("Ingrese el ID del transportista a modificar: ");
    fgets(id, 9, stdin);
    id[strcspn(id, "\n")] = '\0'; // Elimina el carácter de nueva línea

    // Busca el transportista con la ID ingresada y actualiza sus datos
    for (int i = 0; i < *num_transportistas; i++) {
        if (strcmp((*lista_transportistas)[i].id_transp, id) == 0) {
            // Solicita al usuario los nuevos datos del transportista
            printf("Ingrese el nuevo nombre del transportista: ");
            fgets((*lista_transportistas)[i].nombre, sizeof((*lista_transportistas)[i].nombre), stdin);
            (*lista_transportistas)[i].nombre[strcspn((*lista_transportistas)[i].nombre, "\n")] = '\0';

            printf("Ingrese el nuevo email del transportista: ");
            fgets((*lista_transportistas)[i].email, sizeof((*lista_transportistas)[i].email), stdin);
            (*lista_transportistas)[i].email[strcspn((*lista_transportistas)[i].email, "\n")] = '\0';

            printf("Ingrese la nueva contraseña del transportista: ");
            fgets((*lista_transportistas)[i].contrasenia, sizeof((*lista_transportistas)[i].contrasenia), stdin);
            (*lista_transportistas)[i].contrasenia[strcspn((*lista_transportistas)[i].contrasenia, "\n")] = '\0';

            printf("Ingrese el nuevo nombre de la empresa del transportista: ");
            fgets((*lista_transportistas)[i].nombre_empresa, sizeof((*lista_transportistas)[i].nombre_empresa), stdin);
            (*lista_transportistas)[i].nombre_empresa[strcspn((*lista_transportistas)[i].nombre_empresa, "\n")] = '\0';

            printf("Ingrese la nueva ciudad de reparto del transportista: ");
            fgets((*lista_transportistas)[i].ciudad_reparto, sizeof((*lista_transportistas)[i].ciudad_reparto), stdin);
            (*lista_transportistas)[i].ciudad_reparto[strcspn((*lista_transportistas)[i].ciudad_reparto, "\n")] = '\0';

            printf("Transportista modificado correctamente.\n");
            return;
        }
    }
    printf("No se encontró ningún transportista con la ID especificada.\n");
}

// Función para dar de baja un transportista existente
void dar_de_baja_transportista(Transportista **lista_transportistas, int *num_transportistas) {
    char id[5];

    // Solicita al usuario la ID del transportista que desea dar de baja
    printf("Ingrese el ID del transportista que desea dar de baja: ");
    fgets(id, 9, stdin);
    id[strcspn(id, "\n")] = '\0'; // Elimina el carácter de nueva línea

    // Busca el transportista con la ID ingresada y lo elimina del arreglo
    for (int i = 0; i < *num_transportistas; i++) {
        if (strcmp((*lista_transportistas)[i].id_transp, id) == 0) {
            for (int j = i; j < *num_transportistas - 1; j++) {
                (*lista_transportistas)[j] = (*lista_transportistas)[j + 1];
            }
            (*num_transportistas)--; // Reduce la cantidad de transportistas
            *lista_transportistas = realloc(*lista_transportistas, (*num_transportistas) * sizeof(Transportista)); // Reasigna memoria
            printf("Transportista dado de baja correctamente.\n");
            return;
        }
    }
    printf("No se encontró ningún transportista con la ID especificada.\n");
}


/*
int main() {
    Transportista *transportistas = NULL;
    int num_transportistas = 0;
    int opcion;
    char id[5];

    ProductoPedido productos_pedidos[100];
    ComportamientoLocker comportamiento_locker[100];
    int num_productos_pedidos = 0;

    do {
        printf("\nMenú de opciones:\n");
        printf("1. Alta de transportista\n");
        printf("2. Baja de transportista\n");
        printf("3. Listado de transportistas\n");
        printf("4. Perfil de transportista\n");
        printf("5. Reparto de productos\n");
        printf("6. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);
        flushInputBuffer();

        switch (opcion) {
            case 1:
                alta_transportista(&transportistas, &num_transportistas);
                break;
            case 2:
                printf("Ingrese el ID del transportista a dar de baja: ");
                scanf("%4s", id);
                flushInputBuffer();
                baja_transportista(transportistas, &num_transportistas, id);
                break;
            case 3:
                printf("\nListado de transportistas:\n");
                listado_transportista(transportistas, num_transportistas);
                break;
            case 4:
                printf("Ingrese el ID del transportista para ver/modificar su perfil: ");
                scanf("%4s", id);
                flushInputBuffer();
                perfil(transportistas, num_transportistas, id);
                break;
            case 5:
                printf("Ingrese el ID del transportista para realizar el reparto de productos: ");
                scanf("%4s", id);
                flushInputBuffer();
                reparto(productos_pedidos, num_productos_pedidos, id);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, elija una opción válida del menú.\n");
                break;
        }
    } while (opcion != 6);

    free(transportistas);

    return 0;
}
*/

// Guarda el vector de Transportitas en el archivo siguiendo la estructura:
/*
    o Identificador del transportista (Id_transp), 4 dígitos.
    o Nombre del transportista (Nombre), 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
    o Nombre de la empresa (Nombre), 20 caracteres máximo.
    o Ciudad de reparto (Ciudad), 20 caracteres máximo.
*/
void guardarTransportistasEnArchivo(Transportista *transportistas, int numTransportistas)
{
    FILE *archivo = fopen(Transportistas_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Transportistas.txt.\n");
        return;
    }

    for (int i = 0; i < numTransportistas; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-\n",
                transportistas[i].id_transp,
                transportistas[i].nombre,
                transportistas[i].email,
                transportistas[i].contrasenia,
                transportistas[i].nombre_empresa,
                transportistas[i].ciudad_reparto);
    }

    fclose(archivo);
}

Transportista *iniciarTransportistasDeArchivo(int *numTransportista)
{
    FILE *archivo = fopen(Transportistas_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Transportistas_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de Locker
    Transportista *transportistas = (Transportista *)malloc(count * sizeof(Transportista));
    if (transportistas == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Transportistas.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    for(int i=0;i<count;i++)
    {
        if(fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL){
        char *token = strtok(buffer, "-");
        strncpy(transportistas[i].id_transp, token, sizeof(transportistas[i].id_transp));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].nombre, token, sizeof(transportistas[i].nombre));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].email, token, sizeof(transportistas[i].email));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].contrasenia, token, sizeof(transportistas[i].contrasenia));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].nombre_empresa, token, sizeof(transportistas[i].nombre_empresa));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].ciudad_reparto, token, sizeof(transportistas[i].ciudad_reparto));

        }
    }
    fclose(archivo);
    *numTransportista = count;
    return transportistas;
}

int existeTransportista( Transportista ** trans, int *nTrans, char *idT){
    int existe = 0;
    for(int i=1; i<*nTrans && existe==0;i++){
        if(strcmp((*trans)[i].id_transp,idT)==0)
            existe = 1;
    }
    return existe;
}

void asignarProductoPedidoProv(ProductoPedido **pedidos, int *num_pedidos, Transportista ** trans, int *nTrans, char *idProv, Producto **productos, int * nProductos){

    char idProd[8];
    printf("\nId del producto en el pedido a asignar: ");
    fgets(idProd, 8, stdin);
    idProd[strcspn(idProd, "\n")] = '\0';

    if(productoEsDeProveedor(productos,nProductos,idProv,idProd)==0){
        printf("Ese producto no es suyo\n");
    }
    else{
    char idT[5];
    printf("\nId del transportista: ");
    fgets(idT, 5, stdin);
    idT[strcspn(idT, "\n")] = '\0';

    if(existeTransportista(trans,nTrans,idT)==0){
        printf("No existe ese transportista\n");
    }
    else{
        for(int i = 0 ; i < *num_pedidos ; i++){
                if(strcmp((*pedidos)[i].estado_pedido,"enPreparacion")==0&&strcmp((*pedidos)[i].id_prod,idProd)==0){
                    strcpy((*pedidos)[i].id_transp,idT);
                    printf("Transportista asignado\n");
                }
        }
    }
    }

}

void listar_transportistas(Transportista **lista_transportistas, int *num_transportistas) {
    printf("Lista de transportistas:\n");
    for (int i = 0; i < *num_transportistas; i++) {
        printf("ID: %s, Nombre: %s, Email: %s, Empresa: %s, Ciudad de Reparto: %s\n",
               (*lista_transportistas)[i].id_transp, (*lista_transportistas)[i].nombre,
               (*lista_transportistas)[i].email, (*lista_transportistas)[i].nombre_empresa,
               (*lista_transportistas)[i].ciudad_reparto);
    }
}

void agregar_transportista(Transportista **lista_transportistas, int *num_transportistas) {
    char id[9], nombre[21], email[31], contrasenia[16], nombre_empresa[21], ciudad_reparto[21];

    printf("Ingrese el ID del transportista: ");
    fgets(id, 9, stdin);
    id[strcspn(id, "\n")] = '\0';

    printf("Ingrese el nombre del transportista: ");
    fgets(nombre, 21, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    printf("Ingrese el email del transportista: ");
    fgets(email, 31, stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Ingrese la contraseña del transportista: ");
    fgets(contrasenia, 16, stdin);
    contrasenia[strcspn(contrasenia, "\n")] = '\0';

    printf("Ingrese el nombre de la empresa del transportista: ");
    fgets(nombre_empresa, 21, stdin);
    nombre_empresa[strcspn(nombre_empresa, "\n")] = '\0';

    printf("Ingrese la ciudad de reparto del transportista: ");
    fgets(ciudad_reparto, 21, stdin);
    ciudad_reparto[strcspn(ciudad_reparto, "\n")] = '\0';

    (*num_transportistas)++;
    *lista_transportistas = realloc(*lista_transportistas, (*num_transportistas) * sizeof(Transportista));
    if (*lista_transportistas == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo transportista.\n");
        exit(1);
    }

    Transportista nuevo_transportista = {id, nombre, email, contrasenia, nombre_empresa, ciudad_reparto};
    (*lista_transportistas)[(*num_transportistas) - 1] = nuevo_transportista;

}


void buscar_transportista(Transportista **lista_transportistas, int *num_transportistas) {
    char id[5];
    printf("Ingrese el ID del transportista que desea buscar: ");
    scanf("%s", id);

    for (int i = 0; i < *num_transportistas; i++) {
        if (strcmp((*lista_transportistas)[i].id_transp, id) == 0) {
            printf("Transportista encontrado:\n");
            printf("ID: %s, Nombre: %s, Email: %s, Empresa: %s, Ciudad de Reparto: %s\n",
                   (*lista_transportistas)[i].id_transp, (*lista_transportistas)[i].nombre,
                   (*lista_transportistas)[i].email, (*lista_transportistas)[i].nombre_empresa,
                   (*lista_transportistas)[i].ciudad_reparto);
            return;
        }
    }
    printf("No se encontró ningún transportista con el ID especificado.\n");
}



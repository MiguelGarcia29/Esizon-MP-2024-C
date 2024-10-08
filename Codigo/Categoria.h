#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilidades.h"


typedef struct {
    char id_categ[5];
    char descrip[51];
}Categoria;


//En las altas y bajas habra que añadir id cliente dependiendo sea proveedor o admin o cliente.
char* id_generator_categ(Categoria *, int );
void alta_categoria(Categoria **categoria, int* tamanio_vector);
void baja_categoria(Categoria **categorias, int *numCategorias);
int check_categ(Categoria **, int *,char *);
char *indicar_categ(Categoria **, int* , char *);
void modificarCategoria(Categoria **categorias, int *numCategorias);
void guardarCategoriasEnArchivo(Categoria *categorias, int numCategorias);
Categoria *iniciarCategoriasDeArchivo(int *numCat);
void listarCategorias(Categoria **categorias, int *numCategorias);
void buscarCategoria(Categoria **categorias, int *numCategorias);

#endif

/* 
Madrid, 25 de abril de 2017.
UNIVERSIDAD AUTÓNOMA DE MADRID - ESCUELA POLITÉCNICA SUPERIOR. 
DOBLE GRADO EN INGENIERÍA INFORMÁTICA Y MATEMÁTICAS - PROGRAMACIÓN II PRÁCTICA 4.

AUTORES: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo.
PAREJA: 02
*/ 

#ifndef TREE_H
#define TREE_H

#include "functions.h"
#include "types.h"
#include "list.h"

typedef struct _Tree Tree;
/* Tipos de los punteros a función soportados por el árbol */
typedef void (*destroy_elementtree_function_type)(void*);
typedef void *(*copy_elementtree_function_type)(const void*);
typedef int (*print_elementtree_function_type)(FILE *, const void*);
typedef int (*cmp_elementtree_function_type)(const void*, const void*);

/* Inicializa el árbol reservando memoria */
Tree* tree_ini(destroy_elementtree_function_type f1,
        copy_elementtree_function_type f2,
        print_elementtree_function_type f3,
        cmp_elementtree_function_type f4);

/* Libera el árbol y todos sus elementos */
void tree_free(Tree* pa);

/* Inserta en el árbol pa una copia del puntero po, devolviendo ERROR si el elemento ya existía en el árbol */
Status tree_insert(Tree* pa, const void* po);

/* Devuelve TRUE si se puede encontrar po en el árbol pa */
Bool tree_find(Tree* pa, const void* po);

/* Comprueba si un árbol está vacío */
Bool tree_isEmpty(const Tree* pa);

/* Devuelve la profundidad del árbol pa, considerando que un árbol vacío tiene profundidad -1 */
int tree_depth(const Tree* pa);

/* Devuelve el número de nodos del árbol pa, considerando que un árbol vacío tiene 0 nodos */
int tree_numNodes(const Tree* pa);

/******* Funciones de recorrido del árbol (P4_E3) ********/
/* Muestra el recorrido de un árbol en orden previo */
Status tree_preOrder(FILE* f, const Tree* pa);
/* Muestra el recorrido de un árbol en orden medio */
Status tree_inOrder(FILE* f, const Tree* pa);
/* Muestra el recorrido de un árbol en orden posterior */
Status tree_postOrder(FILE* f, const Tree* pa);

/****** Para el ejercicio opcional de P4_E3 *******/
/* Inserta en la lista l el recorrido de un árbol en orden previo */
Status tree_preOrderToList(List* l, const Tree* pa);
/* Inserta en la lista l el recorrido de un árbol en orden medio */
Status tree_inOrderToList(List* l, const Tree* pa);
/* Inserta en la lista l el recorrido de un árbol en orden posterior */
Status tree_postOrderToList(List* l, const Tree* pa);

#endif /* TREE_H */


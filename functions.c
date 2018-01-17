/* 
Madrid, 25 de abril de 2017.
UNIVERSIDAD AUTÓNOMA DE MADRID - ESCUELA POLITÉCNICA SUPERIOR. 
DOBLE GRADO EN INGENIERÍA INFORMÁTICA Y MATEMÁTICAS - PROGRAMACIÓN II PRÁCTICA 4.

AUTORES: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo.
PAREJA: 02
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

void destroy_intp_function(void* e) {
    free((int*) e);
}

void * copy_intp_function(const void* e) {
    int * dst;
    if (e == NULL)
        return NULL;
    dst = (int*) malloc(sizeof (int));
    /*Copiamos el elemento*/
    *(dst) = *((int*) e);
    return dst;
}

int print_intp_function(FILE * f, const void* e) {
    if (f != NULL && e != NULL)
        return fprintf(f, "%d ", *((int*) e));
    return -1;
}

/* La siguiente función permite comparar dos elementos, devolviendo un número positivo, negativo o cero 
 * según si el primer argumento es mayor, menor o igual que el segundo argumento */
int cmp_intp_function(const void *n1, const void *n2){
    int *a=NULL,*b=NULL;
    
    a=(int *)n1;
    b=(int *)n2;
    
    if(*a<*b){
        return -1;
    }
    else if (*a>*b){
        return 1;
    }
    else return 0;
}

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */
void destroy_node_function(void* e) {
    node_destroy((Node *) e);
}

void * copy_node_function(const void* e) {
    return node_copy((Node *) e);
}

int print_node_function(FILE * f, const void* e) {
    return node_print(f, (Node *) e);
}

int cmp_node_function(const void *n1, const void *n2){
    return node_cmp((const Node *)n1, (const Node *)n2);
}

void destroy_char_function(void* e) {
    free((char*) e);
}

void * copy_char_function(const void* e) {
    char *cop;
    int tam;
    if (e == NULL)
        return NULL;
    tam=strlen((char*)e);
    cop = (char*) malloc((tam+1)*sizeof (char));
    /*Copiamos el elemento*/
    strcpy(cop,(char*)e);
    return cop;
}

int print_char_function(FILE * f, const void* e) {
    char *c1=NULL;
    c1=(char*)e;
    if (f != NULL && e != NULL)
        return fprintf(f, "%s ", c1);
    return -1;
}

int cmp_char_function(const void *n1, const void *n2){
    char *c1,*c2;
    int cmp;
    
    c1=(char*)n1;
    c2=(char*)n2;
    
    if(n1==NULL || n2==NULL){
        fprintf(stderr,"cmp_char_function: invalid argument");
    }
    
    cmp=strcmp(c1,c2);

    return cmp;
}





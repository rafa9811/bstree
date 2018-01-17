/* 
Madrid, 25 de abril de 2017.
UNIVERSIDAD AUTÓNOMA DE MADRID - ESCUELA POLITÉCNICA SUPERIOR. 
DOBLE GRADO EN INGENIERÍA INFORMÁTICA Y MATEMÁTICAS - PROGRAMACIÓN II PRÁCTICA 4.

AUTORES: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo.
PAREJA: 02
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "types.h"
#include "functions.h"


struct _Node {
    char *name;
    int id;
};

Node * node_ini() {
    Node *n=NULL;
    
    n=(Node*)malloc(sizeof(Node));
    if(n==NULL){
        return NULL;
    }
    
    return n;
}


void node_destroy(Node * n) {
    if (n == NULL) return;
    free(n->name);
    free(n);
}


int node_getId(const Node * n) {
    int id;
    if (n == NULL) {
        return -1;
    }
    
    id = n->id;

    return id;
}



char* node_getName(const Node * n) {
    char *name = NULL;
    int tam;
    if (n == NULL) return NULL;
    
    tam=strlen(n->name);
    name = (char*) malloc((tam+1) * sizeof (char)); /*tam+1 para el caracter de fin de cadena*/
    strcpy(name, n->name);

    return name;
}



Node *node_setName(Node * n, const char* name) {
    int tam;
    
    if (name == NULL || n == NULL) return NULL;
    
    tam=strlen(name);
    
    n->name = (char*) malloc((tam+1) * sizeof (char));
    strcpy(n->name, name);

    return n;
}



Node * node_setId(Node * n, const int id) {
    if (n == NULL) {
        return NULL;
    }
    n->id = id;
    return n;
}



Bool node_equals(const Node * n1, const Node * n2) {
    if (n1 == NULL || n2 == NULL) {
        return FALSE;
    }
    if ((n1->id == n2->id) && (!strcmp(n1->name, n2->name))) return TRUE;
    return FALSE;
}



Node * node_copy(const Node * src) {
    Node *n2 = NULL;
    char* name;
    if (src == NULL) return NULL;
    n2 = node_ini();
    name= node_getName(src);
    n2=node_setId(n2, node_getId(src));
    n2=node_setName(n2, name);
    free(name);
    return n2;
}


int node_print(FILE *pf, const Node * n) {
    int c;
    if (pf == NULL || n == NULL) {
        return 0;
    }

    c = fprintf(pf, "[%d, %s]", n->id, n->name);

    return c;
}


int node_cmp(const Node *n1, const Node *n2){
    char *name1, *name2;
    if (n1 == NULL || n2 == NULL) return 0;
      
    /*Comparamos los ids de los nodos, si son iguales, se comparan los nombres.*/
    if(node_getId(n1) < node_getId(n2)){
        return -1;
    }
    else if (node_getId(n1) > node_getId(n2)){
        return 1;
    }
    name1= node_getName(n1);
    name2= node_getName(n2);
    if (strcmp(name1, name2) == 0){
	free(name1);
	free(name2);
	return 0;
    }
    free(name1);
    free(name2);
return 2;    
}

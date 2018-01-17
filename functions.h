/* 
Madrid, 25 de abril de 2017.
UNIVERSIDAD AUTÓNOMA DE MADRID - ESCUELA POLITÉCNICA SUPERIOR. 
DOBLE GRADO EN INGENIERÍA INFORMÁTICA Y MATEMÁTICAS - PROGRAMACIÓN II PRÁCTICA 4.

AUTORES: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo.
PAREJA: 02
*/ 

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void destroy_intp_function(void* e) ;

void * copy_intp_function(const void* e) ;

int print_intp_function(FILE * f, const void* e);

int cmp_intp_function(const void *n1, const void *n2);

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */
void destroy_node_function(void* e);

void * copy_node_function(const void* e);

int print_node_function(FILE * f, const void* e) ;

int cmp_node_function(const void *n1, const void *n2);

void destroy_char_function(void* e);

void * copy_char_function(const void* e);

int print_char_function(FILE * f, const void* e) ;

int cmp_char_function(const void *n1, const void *n2);

#endif /* FUNCTIONS_H */


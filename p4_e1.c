/* 
Madrid, 25 de abril de 2017.
UNIVERSIDAD AUTÓNOMA DE MADRID - ESCUELA POLITÉCNICA SUPERIOR. 
DOBLE GRADO EN INGENIERÍA INFORMÁTICA Y MATEMÁTICAS - PROGRAMACIÓN II PRÁCTICA 4.

AUTORES: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo.
PAREJA: 02
*/ 

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "functions.h"

int main(int argc, char** argv) {
    FILE *f=NULL;
    int data,numnodos,depth;
    int *num=NULL;
    Tree *tree=NULL;
    
    tree=tree_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    num=(int *)malloc(sizeof(int));
    
    f=fopen(argv[1],"r");
    if(f==NULL){
        printf("Error abriendo el archivo.");
        return -1;
    }
    
    while(!feof(f)){
        fscanf(f,"%d",&data);
        if(tree_insert(tree, &data)==ERROR){
            tree_free(tree);
	    free(num);
            return -1;
        }
    }
    
    numnodos=tree_numNodes(tree);
    fprintf(stdout,"Numero de nodos: %d\n",numnodos);
    
    depth=tree_depth(tree);
    fprintf(stdout,"Profundidad: %d\n",depth);
    
    fprintf(stdout,"> Introduzca un numero: ");
    scanf("%d",num);
    fprintf(stdout,"Numero introducido: %d\n", *num);
    
    if(tree_find(tree, (void*)num)==TRUE){
        fprintf(stdout,"El dato %d se encuentra dentro del Arbol\n",*num);
    }
    else{
        fprintf(stdout,"El dato %d NO se encuentra dentro del Arbol\n",*num);
    }
    
    tree_free(tree);
    free(num);
    fclose(f);

    return (EXIT_SUCCESS);
}

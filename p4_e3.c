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
    List *list=NULL,*list2=NULL,*list3=NULL;
    
    tree=tree_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    list=list_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    list2=list_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    list3=list_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    num=(int *)malloc(sizeof(int));
    
    f=fopen(argv[1],"r");
    if(f==NULL){
        printf("Error abriendo el archivo. Alto.");
        return -1;
    }
    
    while(!feof(f)){
        fscanf(f,"%d\n",&data);
        if(tree_insert(tree, &data)==ERROR){
            tree_free(tree);
            return -1;
        }
    }
    
    numnodos=tree_numNodes(tree);
    fprintf(stdout,"Numero de nodos: %d\n",numnodos);
    
    depth=tree_depth(tree);
    fprintf(stdout,"Profundidad: %d\n",depth);
    
    fprintf(stdout,"Orden previo: ");
    tree_preOrder(stdout,tree);
    fprintf(stdout,"\n");
    
    fprintf(stdout,"Orden medio: ");
    tree_inOrder(stdout,tree);
    fprintf(stdout,"\n");
    
    fprintf(stdout,"Orden posterior: ");
    tree_postOrder(stdout,tree);
    fprintf(stdout,"\n");
    
    
    fprintf(stdout,"Imprimiendo el arbol utilizando las funciones de listas: \n");
    fprintf(stdout,"Orden previo: ");
    tree_preOrderToList(list,tree);
    fprintf(stdout,"\n");
    
    fprintf(stdout,"Orden medio: ");
    tree_inOrderToList(list2,tree);
    fprintf(stdout,"\n");
    
    fprintf(stdout,"Orden posterior: ");
    tree_postOrderToList(list3,tree);
    fprintf(stdout,"\n");
    
    fprintf(stdout,"> Introduzca un numero: ");
    scanf("%d",num);
    fprintf(stdout,"Número introducido: %d\n", *num);
    
    if(tree_find(tree, (void*)num)==TRUE){
        fprintf(stdout,"El dato %d se encuentra dentro del Arbol\n",*num);
    }
    else{
        fprintf(stdout,"El dato %d NO se encuentra dentro del Arbol\n",*num);
    }
    
    free(num);
    list_free(list);
    list_free(list2);
    list_free(list3);
    tree_free(tree);
    fclose(f);

    return (EXIT_SUCCESS);
}


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
#include "node.h"

int main(int argc, char** argv) {
    FILE *f=NULL;
    Node *nd=NULL,*nd2=NULL;
    Tree *tree=NULL;
    
    int data,numnodos,depth;
    int *num=NULL;
    char *name,*namenode;
    
    if (argc>2) {
	printf("Demasiados argumentos. Alto.");	
	return -2;
    }

    tree=tree_ini(destroy_node_function,copy_node_function,print_node_function,cmp_node_function);
    num=(int *)malloc(sizeof(int));
    name=(char *)malloc(256*sizeof(char));
    namenode=(char *)malloc(256*sizeof(char));
    nd2=node_ini();
    
    f=fopen(argv[1],"r");
    if(f==NULL){
        printf("Error abriendo el archivo.");
	free(num);
        free(namenode);
        node_destroy(nd2);
        tree_free(tree);
        return -1;
    }
    
    while(!feof(f)){
        nd=node_ini();
        fscanf(f,"%d %s",&data,name);
        nd=node_setName(nd,name);
        nd=node_setId(nd,data);
        
        if(tree_insert(tree, (void*)nd)==ERROR){
            tree_free(tree);
	    free(num);
            free(namenode);
	    node_destroy(nd);
            node_destroy(nd2);
        	    
            return -1;
        }
        node_destroy(nd);
    }
    
    numnodos=tree_numNodes(tree);
    fprintf(stdout,"Numero de nodos: %d\n",numnodos);
    
    depth=tree_depth(tree);
    fprintf(stdout,"Profundidad: %d\n",depth);
    
    fprintf(stdout,"Introduzca un nodo: \n");
    fprintf(stdout,"Introduzca su id: \n");
    scanf("%d",num);
    nd2=node_setId(nd2,*num);
    fprintf(stdout,"Introduzca su nombre: \n");
    scanf("%s",namenode);
    nd2=node_setName(nd2,namenode);
    
    if(tree_find(tree, (void*)nd2)==TRUE){
        fprintf(stdout,"El dato %d se encuentra dentro del arbol\n",*num);
    }
    else{
        fprintf(stdout,"El dato %d NO se encuentra dentro del arbol\n",*num);
    }
    
    tree_free(tree);
    free(num);
    free(namenode);
    free(name);
    node_destroy(nd2);
    fclose(f);

    return (EXIT_SUCCESS);
}


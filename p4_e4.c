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

#include "tree.h"
#include "functions.h"

#define MAXTAM 128

int main(int argc, char** argv) {
    FILE *f=NULL;
    int numnodos,depth,tam;
    char *cad=NULL,*cadb2=NULL;
    char cadgen[MAXTAM],cadbus[MAXTAM];
    Tree *tree=NULL;

    tree=tree_ini(destroy_char_function,copy_char_function,print_char_function,cmp_char_function);

    f=fopen(argv[1],"r");
    if(f==NULL){
        printf("Error abriendo el archivo.");
        return -1;
    }
    
    while(!feof(f)){
        fscanf(f,"%s\n",cadgen);
        tam=strlen(cadgen);
        cad=(char*)malloc((tam+1)*sizeof(char));
        cad[tam]='\0';
        
        strcpy(cad,cadgen);
        
        if(tree_insert(tree, (void*)cad)==ERROR){
            tree_free(tree);
            return -1;
        }
        free(cad);
    }
    
    numnodos=tree_numNodes(tree);
    fprintf(stdout,"Numero de nodos: %d\n",numnodos);
    
    depth=tree_depth(tree);
    fprintf(stdout,"Profundidad: %d\n",depth);
    
    tree_inOrder(stdout,tree);
    fprintf(stdout,"\n");
    
    fprintf(stdout,"Introduzca una cadena para buscar en el árbol (siguiendo el mismo formato que en el fichero de entrada):\n ");
    scanf("%s",cadbus);
    cadb2=(char*)malloc((strlen(cadbus)+1)*sizeof(char));
    strcpy(cadb2,cadbus);
    
    if(tree_find(tree, (void*)cadb2)==TRUE){
        fprintf(stdout,"Elemento encontrado!\n");
    }
    else{
        fprintf(stdout,"Elemento NO encontrado!\n");
    }
    
    tree_free(tree);
    free(cadb2);
    fclose(f);

    return (EXIT_SUCCESS);
}


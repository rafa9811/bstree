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
#include "list.h"

typedef struct _NodeBT {
    void* info;
    struct _NodeBT* left;
    struct _NodeBT* right;
} NodeBT;


struct _Tree {
    NodeBT *root;
    int numNodes;
    
    destroy_elementtree_function_type destroy_element_function;
    copy_elementtree_function_type copy_element_function;
    print_elementtree_function_type print_element_function;
    cmp_elementtree_function_type cmp_element_function;
};

Tree* tree_ini(destroy_elementtree_function_type f1,copy_elementtree_function_type f2,print_elementtree_function_type f3,cmp_elementtree_function_type f4){
    Tree *tree=NULL;
    
    tree=(Tree*)malloc(sizeof(Tree));
    
    if(tree==NULL){
        fprintf(stderr,"tree_ini: error reservando memoria");
        return NULL;
    }
    
    tree->numNodes=0;
    
    tree->root=NULL;
    tree->destroy_element_function=f1;
    tree->copy_element_function=f2;
    tree->print_element_function=f3;
    tree->cmp_element_function=f4;
    
    return tree;
}

NodeBT *nodebt_ini(){
    NodeBT *nb=NULL;
    
    nb=(NodeBT*)malloc(sizeof(NodeBT));
    
    nb->left=NULL;
    nb->right=NULL;
    
    return nb;
}

void nodebt_destroy(Tree *t, NodeBT *pn){
    if(t==NULL||pn==NULL || pn->info==NULL){
        fprintf(stderr,"nodetb_destroy: invalid argument");
    }
    
    t->destroy_element_function(pn->info);
    
    free(pn);
}

Bool tree_isEmpty(const Tree* pa) {
    if (!pa) {
        fprintf(stderr,"tree_isEmpty: invalid argument.");
        return TRUE;
    }
    if (!pa->root) {
        return TRUE;
    }
    return FALSE;
}

void tree_free_rec(Tree*tree, NodeBT **pn) {
    if (*pn==NULL) {
        fprintf(stderr,"tree_destroy_rec: invalid argument.");
        return;
    }
    if ((*pn)->left!=NULL) { /* Liberación de subárbol izquierdo*/
        tree_free_rec(tree,&((*pn)->left));
    }
    if ((*pn)->right!=NULL) { /* Liberación de subárbol derecho*/
        tree_free_rec(tree,&((*pn)->right));
    }
    nodebt_destroy(tree,*pn); /* visitar nodo = liberar nodo*/
}

void tree_free(Tree* tree) {
    if (!tree) {
        fprintf(stderr,"tree_destroy: invalid argument.");
        return;
    }
    tree_free_rec(tree,&(tree->root)); /* Primera llamada: root*/
    free(tree);
}

Status tree_insert_rec(Tree *pa,NodeBT **ppn, const void* po) {
    int cmp;
    if (*ppn == NULL) { /*Encontrado lugar donde insertar: nodo nuevo apuntado por *ppn*/
        *ppn = nodebt_ini();
        if (*ppn == NULL){
            fprintf(stderr,"tree_insert_rec: error creating node.");
            return ERROR;
        }
        (*ppn)->info= pa->copy_element_function(po);
        if ((*ppn)->info== NULL) {
            nodebt_destroy(pa,*ppn);
            fprintf(stderr,"tree_insert_rec: error copying node.");
            return ERROR;
        }
        return OK;
    }
    /* Si todavía no se ha encontrado el hueco donde insertar, buscarlo en subárbol*/
    /* izquierdo ó derecho, según corresponda:*/
    cmp = pa->cmp_element_function(po, (*ppn)->info);
    if (cmp < 0)
        return tree_insert_rec(pa,&((*ppn)->left), po);
    if (cmp > 0)
        return tree_insert_rec(pa,&((*ppn)->right), po);
    return OK; /* Solo se sale por aquí si el elemento ya estaba en el árbol (cmp = 0)*/
}

Status tree_insert(Tree* pa, const void* po){
    if (!pa || !po){
        fprintf(stderr,"tree_insert: invalid argument.");
        return ERROR;
    }
    if (tree_insert_rec(pa, &(pa->root), po) == OK) {
        pa->numNodes++;
        return OK;
    }
    fprintf(stderr,"tree_insert: error tree_insert_rec return ERROR.");
    return ERROR;
}

Bool tree_find_rec(Tree* pa,NodeBT **ppn, const void* po){
    int cmp;
    
    if(pa==NULL || po ==NULL){
        fprintf(stderr,"tree_find_rec: invalid argument.");
        return FALSE;   
    }
    
    if(tree_isEmpty(pa)==TRUE){
        fprintf(stderr,"tree_find_rec: tree is empty.");
        return FALSE;
    }
    if((*ppn)==NULL){
        return FALSE;
    }
    cmp = pa->cmp_element_function(po, (*ppn)->info);
    if (cmp < 0)
        return tree_find_rec(pa,&((*ppn)->left), po);
    if (cmp > 0)
        return tree_find_rec(pa,&((*ppn)->right), po);
    
    return TRUE;
}

Bool tree_find(Tree *pa, const void *po){
    if(pa==NULL || po ==NULL){
        fprintf(stderr,"tree_find: invalid argument.");
        return FALSE;   
    }
    return tree_find_rec(pa,&(pa->root),po);
}

int tree_depth_rec(NodeBT **ppn){
    int i,j;
    
    if(*ppn==NULL ){
        return -1;   
    }
    
    i=tree_depth_rec(&((*ppn)->left));
    j=tree_depth_rec(&((*ppn)->right));
    
    if(i>j){
        return i+1;
    }
    else if(i<j){
        return j+1;
    }
    return i+1;
        
    
}
int tree_depth(const Tree* pa){
    int ret;
    NodeBT *nb=NULL;
    if(pa==NULL ){
        fprintf(stderr,"tree_depth: invalid argument.");
        return -1;   
    }
    nb=(NodeBT*)pa->root;
    ret=tree_depth_rec(&(nb));

    return ret;
}

/* Devuelve el número de nodos del árbol pa, considerando que un árbol vacío tiene 0 nodos */
int tree_numNodes(const Tree* pa){
    if(pa==NULL ){
        fprintf(stderr,"tree_numNodes: invalid argument.");
        return -1;   
    }
    return pa->numNodes;
}

Status tree_preOrder_rec(FILE* f,const Tree* pa, NodeBT *ppn){
    if(ppn==NULL){
        return OK;
    }
    pa->print_element_function(f,ppn->info);
    tree_preOrder_rec(f,pa,ppn->left);
    tree_preOrder_rec(f,pa,ppn->right);
    
    return OK;
}

Status tree_preOrder(FILE* f, const Tree* pa){
    NodeBT *pn;
    if(f==NULL || pa==NULL){
        fprintf(stderr,"tree_preOrder: invalid argument");
        return ERROR;
    }
    
    if(tree_isEmpty(pa)==TRUE)return OK;
    
    pn=(NodeBT *)(pa->root);
    
    return tree_preOrder_rec(f,pa,pn);
}

Status tree_inOrder_rec(FILE* f, const Tree* pa, NodeBT *ppn){
    if(ppn==NULL){
        return OK;
    }
    
    if(ppn->left!=NULL){
        tree_inOrder_rec(f,pa,ppn->left);
    }
    pa->print_element_function(f,ppn->info);
    
    if(ppn->right!=NULL){
        tree_inOrder_rec(f,pa,ppn->right);
    }
    
    return OK;
}

Status tree_inOrder(FILE* f, const Tree* pa){
    NodeBT *pn;
    if(f==NULL || pa==NULL){
        fprintf(stderr,"tree_preOrder: invalid argument");
        return ERROR;
    }
    
    if(tree_isEmpty(pa)==TRUE)return OK;
    
    pn=(NodeBT *)(pa->root);
    
    return tree_inOrder_rec(f,pa,pn);
}

Status tree_postOrder_rec(FILE* f, const Tree* pa, NodeBT *ppn){
    if(ppn==NULL){
        return OK;
    }
    
    if(ppn->left!=NULL){
        tree_postOrder_rec(f,pa,ppn->left);
    }
    
    if(ppn->right!=NULL){
        tree_postOrder_rec(f,pa,ppn->right);
    }
    
    pa->print_element_function(f,ppn->info);
    
    return OK;
}

Status tree_postOrder(FILE* f, const Tree* pa){
    NodeBT *pn;
    if(f==NULL || pa==NULL){
        fprintf(stderr,"tree_preOrder: invalid argument");
        return ERROR;
    }
    
    if(tree_isEmpty(pa)==TRUE)return OK;
    
    pn=(NodeBT *)(pa->root);
    
    return tree_postOrder_rec(f,pa,pn);
}

Status tree_preOrderToList_rec(List *list,const Tree* pa, NodeBT *ppn){
    if(ppn==NULL){
        return OK;
    }
    
    list_insertLast(list,(void *)ppn->info);
    tree_preOrderToList_rec(list,pa,ppn->left);
    tree_preOrderToList_rec(list,pa,ppn->right);
    
    return OK;
}

Status tree_preOrderToList(List *list, const Tree* pa){
    NodeBT *pn;
    if(list==NULL || pa==NULL){
        fprintf(stderr,"tree_preOrder: invalid argument");
        return ERROR;
    }
    
    if(tree_isEmpty(pa)==TRUE)return OK;
    
    pn=(NodeBT *)(pa->root);
    
    tree_preOrderToList_rec(list,pa,pn);
    
    list_print(stdout,list);
    
    return OK;
}

Status tree_inOrderToList_rec(List *list, const Tree* pa, NodeBT *ppn){
    if(ppn==NULL){
        return OK;
    }
    
    if(ppn->left!=NULL){
        tree_inOrderToList_rec(list,pa,ppn->left);
    }

    list_insertLast(list,(void *)ppn->info);
    
    if(ppn->right!=NULL){
        tree_inOrderToList_rec(list,pa,ppn->right);
    }
    
    return OK;
}

Status tree_inOrderToList(List *list, const Tree* pa){
    NodeBT *pn;
    if(list==NULL || pa==NULL){
        fprintf(stderr,"tree_preOrder: invalid argument");
        return ERROR;
    }
    
    if(tree_isEmpty(pa)==TRUE)return OK;
    
    pn=(NodeBT *)(pa->root);
    
    tree_inOrderToList_rec(list,pa,pn);
    
    list_print(stdout,list);
    
    return OK;
}

Status tree_postOrderToList_rec(List *list, const Tree* pa, NodeBT *ppn){
    if(ppn==NULL){
        return OK;
    }
    
    if(ppn->left!=NULL){
        tree_postOrderToList_rec(list,pa,ppn->left);
    }
    
    if(ppn->right!=NULL){
        tree_postOrderToList_rec(list,pa,ppn->right);
    }
    
    list_insertLast(list,(void *)ppn->info);
    
    
    return OK;
}

Status tree_postOrderToList(List *list, const Tree* pa){
    NodeBT *pn;
    if(list==NULL || pa==NULL){
        fprintf(stderr,"tree_preOrder: invalid argument");
        return ERROR;
    }
    
    if(tree_isEmpty(pa)==TRUE)return OK;
    
    pn=(NodeBT *)(pa->root);
    
    tree_postOrderToList_rec(list,pa,pn);
    
    list_print(stdout,list);
    
    return OK;
}


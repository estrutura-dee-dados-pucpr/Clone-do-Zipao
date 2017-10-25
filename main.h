#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DIR '1'
//#define ESQ '0'
#define DECOMP 1
#define COMP 2
#define TRUE 1
#define FALSE 0
#define ID "ID\0"
#define END_LINE '\n'
#define ESC_CHAR '-'

typedef struct _node{
    char data;
    int peso;
    struct _node * esq;
    struct _node * dir;
}NODE;

typedef struct _element{
    NODE * node;
    struct _element * prox;
}ELEMENT;


int isFolha(NODE * );
char * muda_formato(char *, char *);
char * le_arquivo(char *);
void init_vals(int , char * *, char * *, int *, char * *);
void  zero1(NODE *, char , char *);
void print2DUtil(NODE *, int );
void init_list(ELEMENT * *);
void Tree_inOrder(NODE *);
void prt(ELEMENT * );
NODE * new_node(char  , int , NODE * , NODE * );
NODE * init_tree(ELEMENT * );
ELEMENT  *init_alfabeto(ELEMENT * *, int , int *);
ELEMENT *sort(ELEMENT *); ///TODO: MUDAR PARA INSERT
void tabela_simbolos(NODE * , char * simbolos[]);
int * init_aparicoes(char * );
void compila(char *, char *, char * *, NODE * , int *);

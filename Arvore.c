#include "main.h"

NODE * new_node(char  data, int peso, NODE * esq, NODE * dir){
    NODE * res = (NODE * ) malloc(sizeof(NODE));
    res -> data = data;
    res -> peso = peso;
    res -> esq = esq;
    res -> dir = dir;

    return res;
}

NODE * init_tree(ELEMENT * ancora){
    int peso_res = ancora ->prox->node->peso + ancora->node->peso;

        NODE * nNode = new_node(NULL, peso_res, ancora ->prox->node, ancora->node);
        ancora -> prox -> node = nNode;
        //deleteNode(ancora);
        ancora = ancora -> prox;
        //printf("->Novo alfabeto: \n");
        ancora = sort(ancora);
       // prt(ancora);
        if(ancora -> prox == NULL)
            return ancora->node;
    return(init_tree(ancora));
}

int isFolha(NODE * node){
    if( (node -> esq  == NULL)&& (node -> dir == NULL))
        return TRUE;
    return FALSE;
}

void Tree_inOrder(NODE *n){

     if(n==NULL)

           return;

     Tree_inOrder(n->esq);

     printf("Peso: %d, Data: %c\n", n->peso, n->data);

     Tree_inOrder(n->dir);

}

void  zero1(NODE * raiz, char c, char * ans){
    static int j;
    int k, i;
    static char res[4];
    static int achouResp = FALSE;
    //printf("PESO do no: %d\n", raiz -> peso);

    if(achouResp == 1){
        memset(res, 0, 100);
        achouResp = FALSE;
    }

    if(isFolha(raiz -> dir) == TRUE){
        if(raiz ->dir -> data == c){
            res[j] = '1';
          //  printf("RES: %s, len: %d\n", res, strlen(res));
            for(i = 0; i < strlen(res); i++){
                ans[i] = res[i];
            }
            j = 0;
            achouResp = TRUE;
            return  ;
        }
    }
    if(isFolha(raiz -> esq) == TRUE){
        if(raiz ->esq -> data == c){
            res[j] = '0';
          //  printf("RES: %s, len: %d\n", res, strlen(res));
            for(i = 0; i < strlen(res); i++){
                ans[i] = res[i];
            }
            j = 0;
            achouResp = TRUE;
            return ;
        }
    }

    if(isFolha(raiz -> dir) == FALSE){
       // printf("ERR DIR\n");
        res[j] = '1';
        j++;
        zero1(raiz->dir, c, ans);
    }
    if(isFolha(raiz -> esq) == FALSE){
      //  printf("ERR ESQ\n");
        res[j] = '0';
        j++;
        zero1(raiz->esq, c, ans);
    }

    if(j != 0)
        j--;
    return;
}
void print2DUtil(NODE *root, int space)
{
    int i;
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->dir, space);

    // Print current node after space
    // count
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("C: %c P: %d\n", root->data, root -> peso);

    // Process left child
    print2DUtil(root->esq, space);
}


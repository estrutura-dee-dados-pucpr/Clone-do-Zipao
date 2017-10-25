#include "main.h"

int * init_aparicoes(char * stream){
	int * res = (int * ) calloc(255, sizeof(int));


	int i;

	for(i = 0; i < 256; i++)
		res[i] = 0;
	for (i = 0; i < strlen(stream); i++){
		res[(unsigned char) stream[i]]++;

	//IMPRIMIR PORCENTAGEM: printf("Inicializando aparicoes... %g \%\n", ((double) i*100/strlen(stream)) );system("CLS");

	}


	return res;
}

ELEMENT  * init_alfabeto( ELEMENT * * ancora, int index, int * aparicoes){
	//printf("NEW LOOP, Index: %d\n", index);
    int i, j = 0, k = 0;
    ELEMENT * res;

    res = (ELEMENT * ) malloc(sizeof(ELEMENT) );

    do{
       // printf("Index: %d\n ", index);
        index++;
        if(index >= 256)
            return ancora;
    }while(aparicoes[index] == 0);

    res -> node = new_node( (char) index, aparicoes[index], NULL, NULL);

    //printf("Adicionado NODE com data %c e peso %d\n", res -> node -> data, res -> node -> peso);
    res ->prox = *ancora;
    *ancora = res;

    return init_alfabeto(ancora, index, aparicoes);
}
void init_list(ELEMENT * * ancora){
    * ancora = NULL;
}
void prt(ELEMENT * res){

    char  c = (res -> node -> data);
    printf("C: %c, P: %d\n", c, res -> node -> peso);
    if(res ->prox != NULL)
    prt(res -> prox);
}

ELEMENT *sort(ELEMENT *lst) {
    if (!lst || !lst-> prox)
         return lst;
   ELEMENT *q = lst, *p = lst-> prox-> prox;
  while (p && p-> prox) {
    q = q-> prox;
    p = p-> prox-> prox;
  }
   ELEMENT *mid = q-> prox;
  q-> prox = NULL;
   ELEMENT *fst = sort(lst), *snd = sort(mid);
   ELEMENT rtn[1], *tail = rtn;
  while (fst && snd) {
    if (fst->node -> peso < snd->node -> peso) {
      tail-> prox = fst;
      tail = fst;
      fst = fst-> prox;
    } else {
      tail-> prox = snd;
      tail = snd;
      snd = snd-> prox;
    }
  }
  while (fst) {
    tail-> prox = fst;
    tail = fst;
    fst = fst-> prox;
  }
  while (snd) {
    tail-> prox = snd;
    tail = snd;
    snd = snd-> prox;
  }
  tail-> prox = NULL;
  return rtn-> prox;
}


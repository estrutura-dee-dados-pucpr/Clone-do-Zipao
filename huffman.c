#include "main.h"

#define MASK_1 0b00000001
#define MASK_2 0b00000010
#define MASK_3 0b00000100
#define MASK_4 0b00001000
#define MASK_5 0b00010000
#define MASK_6 0b00100000
#define MASK_7 0b01000000
#define MASK_8 0b10000000

int zeroOuUm(char * str){
    int i;
    for(i = 0; i < strlen(str); i++)
        if(str[i] != '0' && str[i] != '1')
            return FALSE;
    return TRUE;
}




void compila(char * path, char * stream, char * * simbolos, NODE * raiz, int * freq){
    char buffer[9], * codigo_da_letra, * id = ID, asd = '\n';
    int j = 0, k = 0, qtde = 0, i = 0;
    long int helper;
    unsigned char l = 0;
    char tmp = 0;
    char a = 0;
    printf("PATH: %s\n", path);
    FILE * fp = fopen(path, "wb");

    fprintf(fp, "%s\0", ID);
    printf("ID: %s\n", ID);

    for(i = 0; i < 256; i++){
        if(freq[i] != 0){
            qtde++;
        }
    }

    fprintf(fp, "%d\n", qtde);
    printf("QTDE: %d\n", qtde);

    for(l = 0; l < 255; l++){
        if(freq[l] != 0){
            //    printf("WRITING: %c AS %d\n", i, freq[i]);
            fprintf(fp, "%c%d^", l, freq[l]);
        }
    }
    fprintf(fp, "%d", strlen(stream));
    memset(buffer, 0, sizeof(buffer));
    printf("COPACTANDO... %d\n", strlen(stream));

   // print2DUtil(raiz, 2);

    for(i = 0; i < strlen(stream); i ++){
        if(simbolos[stream[i]] == '\0')
            continue;
        codigo_da_letra = simbolos[stream[i]];
     //   printf("Codigo da letra: %s\n", );
        for(j, k = 0; k < strlen(codigo_da_letra); j++,k++){
          //  printf("a");
            if(strlen(buffer) == 8){
            //    printf("TMPBUFF: %s\n", buffer);
                helper = strtol(buffer, NULL, 2);
             //   printf("HELPER: %c\n", helper);
                fwrite(&helper, sizeof(unsigned char), 1, fp);
                j = 0;
                memset(buffer, 0, sizeof(buffer));
            }
            if(codigo_da_letra[k] != '\0')
                buffer[j] = codigo_da_letra[k];
        }
    }
    printf("SAI");
    while(strlen(buffer) < 8){
            buffer[j] = '0';
            j++;
    }
    printf("TMP EM CASA\n");
    helper = strtol(buffer, NULL, 2);
    fwrite(&helper, sizeof(char), 1, fp);
    fclose(fp);
}


void tabela_simbolos(NODE * raiz, char * simbolos[256]){
    static int j;
    int k, i;
    static char res[100];
    static int achouResp = FALSE;
    static int isArrayClear = FALSE;
     if(raiz==NULL)
           return;
           if(!isArrayClear){
            for(i = 0; i < 100; i++)
                res[i] = 0;
                isArrayClear = TRUE;
           }

  /**  if(achouResp == TRUE){
        printf("LIMPEI achouResp\n");
        memset(res, 0, 100);
        achouResp = FALSE;
    }*/
    //if(raiz -> data != NULL)
   // printf("\tPESO do no: %d, Char: %c, tempRes: %s\n",raiz -> peso,  raiz -> data, res);



    if(isFolha(raiz) == FALSE){
     //   printf("ERR ESQ\n");
        res[j] = '0';
        j++;
        tabela_simbolos(raiz->esq, simbolos);
      // printf("ERR DIR\n");
        res[j] = '1';
        j++;
        tabela_simbolos(raiz->dir, simbolos);
        res[j] = 0;
        j--;

     } else if(raiz -> data != NULL){
            simbolos[raiz -> data] = (char * )malloc( sizeof(char) * strlen(res) + 1);
            memset(simbolos[raiz -> data], 0, sizeof(simbolos[raiz -> data]));
            memcpy(simbolos[raiz  -> data], res, strlen(res) + 1);
         //  printf("C: %c -> %s\n",raiz -> data , simbolos[raiz -> data]);
           res[j] = 0;
            j--;
            achouResp = TRUE;
            return;
    }


}

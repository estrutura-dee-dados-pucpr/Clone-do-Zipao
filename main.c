#include "main.h"

int main(int argc, char * * argv){
    if(strcmp(argv[1], "-c") == 0)
       compilar(argc, argv);
    else if(strcmp(argv[1], "-d") == 0)
        descompilar(argc, argv);
}

void descompilar(int argc, char * * argv){
    FILE * fp = fopen(argv[2], "rb");
    int  aparicoes[256], tmp = 0, qtde = 0, i, tam , j = 0;
    char id[100];
    unsigned char c = 0, bit, byte;
    NODE * raiz = NULL, * node;
    ELEMENT * alfabeto = NULL;

    unsigned char * stream;

    char * out_path = muda_formato(argv[2], "txt");

    if(!fp){
        printf("FALHA AO ABRIR O ARQUIVO !");
        exit(1);
    }

    ///TODO: CHECAR SE BATE O ID
    fgets(id, strlen(ID) + 1, fp);
    printf("ID: %s\n", id, ID);

    fscanf(fp, "%d", &qtde);  //Pega a quantidade de letras utilizadas
    printf("QTDE: %d\n", qtde);

    memset(aparicoes, 0, sizeof(aparicoes));

    //Inicializa o alfabeto com suas qtdes
    for(i = 0; i < qtde; i++){
        fscanf(fp, "%c%d^", &c ,&tmp);
        aparicoes[c] = tmp;
        printf("%c: %d\n", c ,tmp);
    }

    fscanf(fp, "%d", &tam);//Pega a quantidade de chars no role
    printf("TAM: %d\n", tam);


    stream = (unsigned char * ) malloc(sizeof(unsigned char) * tam  + 1);
    i = 0;


    init_list(&alfabeto);
    init_alfabeto( &alfabeto, 0, aparicoes);

    alfabeto=sort(alfabeto);
    raiz = init_tree(alfabeto);
    node = raiz;

    memset(stream, 0, sizeof(stream));

    do{
        fscanf(fp, "%c", &byte);

        for(i = 0; i < 8; i++){
            if( strlen(stream) > tam - 1)
                break;
            bit = (byte >> 7- i) & 0x1;
         //   printf("CASD: %d\t", bit);
            if(isFolha(node)){
                stream[j] = node -> data;
                j++;
                node = raiz;
            }
            if(bit == 1)
                node = node -> dir;
            else
                node = node -> esq;
        }

    }while(!feof(fp));

    stream[strlen(stream)] = '\0';

    fclose(fp);

    fp = fopen(out_path, "wb");

    fprintf(fp, "%s", stream);

    printf("DECOMPILADO!!\n");

}



void compilar(int argc, char * * argv){
    ELEMENT * alfabeto;
    NODE * raiz;

    int i;
    char * stream, * out_name;
    int * aparicoes;
    int idOp;
    char * simbolos[256];

    init_vals(argc, argv, &stream, &idOp, &out_name);
    printf("Innited vals\n");

    aparicoes = init_aparicoes(stream);
    printf("Innited aparicoes\n");
    for(i = 0; i < 256; i++){
        if(aparicoes[i] != 0)
            printf("%d: %d\n", i, aparicoes[i]);
    }

    //init_list(&alfabeto);
   // init_alfabeto( &alfabeto, 0, aparicoes);
    printf("Innited alfabeto\n");

    alfabeto=sort(alfabeto);
    raiz = init_tree(alfabeto);
    printf("Innited tree");

    tabela_simbolos(raiz, &simbolos);
    printf("Innited simbolos\n");
    printf("PATH: %s\n", out_name);
    compila(out_name, stream, simbolos, raiz, aparicoes);
    printf("COMPILADO!!!\n");
}


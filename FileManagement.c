#include "main.h"

char * le_arquivo(char * path){
    char * buffer = NULL;
    int size, lido;
    FILE *  file = fopen(path, "r");

    if(file){
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);

        buffer = (char *) malloc(size + 1);
        buffer[size] = '\0';
        lido = fread(buffer, sizeof(char), size, file);
        //printf("Buffer: %s\n", buffer);
        fclose(file);
        return buffer;
    }
}

char * muda_formato(char * nome, char * novo_formato){
    char res[1000];
    int i, j;
    int achouPonto = FALSE;
memset(res, 0, sizeof(res));
    for(i = strlen(nome), j = 0; i >= 0; i--){
        if(nome[i] == '.')
            achouPonto = TRUE;
        if(achouPonto){
            res[i] = nome[i];
        }else{
            res[i] = novo_formato[j];
            j++;
        }
    }
    printf("RES: %s, len %d\n", res, strlen(res));
    return res;
}



///TODO: LIDAR COM EXCESSOES
void init_vals(int argc, char * * argv, char * * stream, int * op, char * * out_name){
    printf("ARGC %s\n", argv[2]);
    char * tmp = NULL, * tmp_out, formato[] = "fael";
    if(argc < 3){
        printf("Erro na chamada do programa. O formato é: aaa.exe -operacao entrada saida ");
        exit(1);
    }else if(argc == 3){
        if(strcmp(argv[1], "-d") == 0){
            *op = DECOMP;
        }else if(strcmp(argv[1], "-c") == 0){
            *op = COMP;
        }else{
            printf("Erro na chamada do programa. O formato é: aaa.exe, -operacao entrada saida ");
            exit(1);
        }
        * stream = le_arquivo(argv[2]);
        if( * stream == NULL) {
         //   printf("TMP: %s\n", * stream);
            printf("Erro no caminho do arquivo, tente novamente");
            exit(1);
        }
       ///\ printf("STREAM: %s\n", * stream);
        //printf("STREAM: %s\n", stream);
        tmp_out = muda_formato(argv[2], formato);
        * out_name = (char * ) malloc(strlen(tmp_out));

        strcpy(*out_name, tmp_out);
        printf("TMP_OUT> %s\n", * out_name);
        //return tmp;
    }
}

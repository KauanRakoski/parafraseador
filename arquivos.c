#include "arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abrir_criar_arquivos (FILE **in, char *in_name, FILE **dict, char *dict_name, FILE **out, char *out_name){
    int success = 1;

    *in = fopen(in_name, "r");

    if (*in == NULL){
        printf("Nao foi possivel ler o arquivo de entrada!\n");
        success = 0;
    }

    *dict = fopen(dict_name, "r");

    if (*dict == NULL){
        printf("Nao foi possivel ler dicionario\n");
        success = 0;
    }

    *out = fopen(out_name, "w");

    if (*out == NULL){
        printf("Nao foi possivel criar arquivo de saida\n");
        success = 0;
    }

    return success;
}

void fechar_arquivos (FILE *in, FILE *dict, FILE *out){
    fclose(in);
    fclose(dict);
    fclose(out);
}

int le_sinonimo (FILE *ptr, char chave[40], char sinonimo[40]){
    if (!feof(ptr)){
        fscanf(ptr, "%s %s\n", chave, sinonimo);
        return 1;
    }
    
    return 0;
}

int gera_estatisticas (int tipo_arv, char *in, char *dict, int nodos, int alt, int rot, int comp){
    char arv_tipo[4], file_name[40];
    FILE *stats;

    if (tipo_arv == 0){
        strcpy(arv_tipo, "ABP");
        strcpy(file_name, "Estatisticas_ABP.txt");
    }
    else{
        strcpy(arv_tipo, "AVL");
        strcpy(file_name, "Estatisticas_AVL");
    }
    
    stats = fopen(file_name, "w");

    fprintf(stats, "========== Estatisticas %s ========== \n", arv_tipo);
    fprintf(stats, "Arquivo de entrada: %s\n", in);
    fprintf(stats, "Dicionario: %s\n", dict);
    fprintf(stats, "Numero de nodos: %d\n", nodos);
    fprintf(stats, "Altura da arvore: %d\n", alt);
    fprintf(stats, "Rotacoes: %d\n", rot);
    fprintf(stats, "Comparacoes realizadas: %d", comp);

    fclose(stats);

    return 1;
}


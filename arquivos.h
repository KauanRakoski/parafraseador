#include <stdio.h>
#include <stdlib.h>

#ifndef ARQUIVOS_H
#define ARQUIVOS_H

// Abre e cria arquivos necessários para o programa
// retorna 1 se sucesso e 0 senão
int abrir_criar_arquivos (FILE **in, char *in_name, FILE **dict, char *dict_name, FILE **out, char *out_name);

// Fecha os arquivos abertos e criados anteriormente
void fechar_arquivos (FILE *in, FILE *dict, FILE *out);

// dado um arquivo de dicionário, e duas strings de destino, lê uma palavra e seu sinônimo do arquivo
// retorna 1 se leitura sucedida e 0 senão.
int le_sinonimo (FILE *ptr, char chave[40], char sinonimo[40]);

// Gera um arquivo de estatísticas da árvore e do programa
int gera_estatisticas (int tipo_arv, char *in, char *dict, int nodos, int alt, int rot, int comp);

#endif
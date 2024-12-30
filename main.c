#include "arvores.h"
#include "arquivos.h"
#include <string.h>

void gera_parafrases(FILE *in, FILE *out, Abp* arv);
void escreve_sinonimo (FILE *out, char palavra[40], Abp *arv);
Abp* consulta (Abp *a, char *chave);

// Variáveis globais para estatísticas
int comp = 0;

int main (int argc, char* argv[]){
    // Criamos variáveis para armazenar o nome e os ponteiros dos arquivos
    char in_name[40], dicionario[40], out_name[40]; 
    FILE *in, *dict, *out;

    // Variáveis passadas como referência para estatísticas
    int num_nodos = 0, rotacoes = 0, altura = 0;

    // Criamos strings para armazenar as chaves e sinonimos lidos e inicializamos uma árvore
    char chave[40], sinonimo[40];
    Abp *arv = incializaArvore();

    // Abrimos e criamos arquivos com base nos parâmetros passados
    strcpy(in_name, argv[1]);
    strcpy(dicionario, argv[2]);
    strcpy(out_name, argv[3]);

    abrir_criar_arquivos(&in, in_name, &dict, dicionario, &out, out_name);

    // Construímos árvore de sinônimos
    while(le_sinonimo(dict, chave, sinonimo)){
        arv = insereAbp(arv, chave, sinonimo);
        num_nodos++;
    }

    altura = Altura(arv);
    
    // Geramos paráfrases
    gera_parafrases(in, out, arv);
    gera_estatisticas(0, in_name, dicionario, num_nodos, altura, rotacoes, comp);

    // Fechamos os arquivos
    fechar_arquivos(in, dict, out);


    return 0;
}

void gera_parafrases(FILE *in, FILE *out, Abp* arv){
    char palavra[40], c;
    int i = 0, naoespaco = 1;

    while ((c = getc(in)) != EOF){

        // Se for um caractere válido, construímos a palavra
        if (c != ' ' && c != '\n' && i < 39){
            naoespaco = 1;
            palavra[i] = c;
            i++;
        } 
        // Senão,
        else {
            // Se tiver formado palavra, terminamos ela
            if (naoespaco){
                palavra[i] = '\0';
                i = 0;

                // E geramos sinônimo
                escreve_sinonimo(out, palavra, arv);

                // preservamos quebras de linha
                if (c == '\n')
                    fprintf(out, "\n");
            }

            naoespaco = 0;
        }
    }

    // se ainda houver alguma palavra, escrevemos
    if (naoespaco){
        palavra[i] = '\0';
        escreve_sinonimo(out, palavra, arv);
    }
}

void escreve_sinonimo (FILE *out, char palavra[40], Abp *arv){
    char sinonimo[40];
    Abp *temp = incializaArvore();

    temp = consulta(arv, palavra);

    // Se não existir sinônimo, escrevemos a própria palavra
    if (temp == NULL){
        strcpy(sinonimo, palavra);
    } else {
        strcpy (sinonimo, temp->sinonimo);
    }

    fprintf(out, "%s ", sinonimo); 
}

// Função fornecida para consulta e calculo de comparações
Abp* consulta (Abp *a, char *chave){
    comp++;

    while (a != NULL){
        if (!strcmp(a->chave, chave)){
            comp++;
            return a;
        } else {
            comp++;
            
            if (strcmp(a->chave, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL;
};
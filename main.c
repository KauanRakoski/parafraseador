#include "arvores.h"
#include "arquivos.h"
#include <string.h>

void gera_parafrases(FILE *in, FILE *out, Abp* arv);
void gera_parafrases_avl(FILE *in, FILE *out, Avl* arv);
void escreve_sinonimo (FILE *out, char palavra[40], Abp *arv);
void escreve_sinonimo_avl(FILE *out, char palavra[40], Avl *arv);
Abp* consulta (Abp *a, char *chave);
Avl* consulta_avl (Avl *a, char *chave);

// Variáveis globais para estatísticas
int comp = 0;
int comp2 = 0;

int main (int argc, char* argv[]){
    // Criamos variáveis para armazenar o nome e os ponteiros dos arquivos
    char in_name[40], dicionario[40], out_name[40]; 
    FILE *in, *dict, *out;

    // Variáveis passadas como referência para estatísticas
    int num_nodos = 0, rotacoes = 0, altura = 0;
    int num_nodos2 = 0, rotacoes2 = 0, altura2 = 0;

    // Criamos strings para armazenar as chaves e sinonimos lidos e inicializamos uma árvore
    char chave[40], sinonimo[40];
    Abp *arv = incializaArvore();
    Avl *arv_avl = inicializaArvoreAVL();
    int ok;

    // Abrimos e criamos arquivos com base nos parâmetros passados
    strcpy(in_name, argv[1]);
    strcpy(dicionario, argv[2]);
    strcpy(out_name, argv[3]);

    abrir_criar_arquivos(&in, in_name, &dict, dicionario, &out, out_name);

    // Construímos árvore de sinônimos (ABP)
    while(le_sinonimo(dict, chave, sinonimo)){
        arv = insereAbp(arv, chave, sinonimo);
        num_nodos++;
    }

    rewind(dict);

    // Construímos a árvore de sinônimos (AVL)
     while(le_sinonimo(dict, chave, sinonimo)){
        arv_avl = insereAVL(arv_avl, chave, sinonimo, &ok, &rotacoes2);
        num_nodos2++;
    }


    //Calculamos as alturas das árvores
    altura = Altura(arv);
    altura2 = AlturaAVL(arv_avl);
    
    // Geramos paráfrases
    gera_parafrases(in, out, arv);
    rewind(out);
    rewind(in);
    gera_parafrases_avl(in, out, arv_avl);

    //Geramos estatísticas
    gera_estatisticas(0, in_name, dicionario, num_nodos, altura, rotacoes, comp);
    gera_estatisticas1(0, in_name, dicionario, num_nodos2, altura2, rotacoes2, comp2);

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

void gera_parafrases_avl(FILE *in, FILE *out, Avl* arv){
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
                escreve_sinonimo_avl(out, palavra, arv);

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
        escreve_sinonimo_avl(out, palavra, arv);
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

void escreve_sinonimo_avl(FILE *out, char palavra[40], Avl *arv)
{
    char sinonimo[40];
    Avl *temp = incializaArvoreAVL();

    temp = consulta_avl(arv, palavra);

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

Avl* consulta_avl (Avl *a, char *chave)
{
    comp2++;

    while (a != NULL){
        if (!strcmp(a->chave, chave)){
            comp2++;
            return a;
        } else {
            comp2++;
            
            if (strcmp(a->chave, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL;
}
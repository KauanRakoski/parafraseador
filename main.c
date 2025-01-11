#include "arvores.h"
#include "arquivos.h"
#include <string.h>
#include <strings.h>
#include <locale.h>

void gera_parafrases(FILE *in, FILE *out, Abp* arv);
void gera_parafrases_avl(FILE *in, FILE *out, Avl* arv);
void escreve_sinonimo (FILE *out, char palavra[40], Abp *arv);
void escreve_sinonimo_avl(FILE *out, char palavra[40], Avl *arv);
Abp* consulta (Abp *a, char *chave);
Avl* consulta_avl (Avl *a, char *chave);

// Variáveis globais para estatísticas
int comp = 0;

int main (int argc, char* argv[]){
    setlocale(LC_ALL, "");
    // Criamos variáveis para armazenar o nome e os ponteiros dos arquivos
    char in_name[40], dicionario[40], out_name[40]; 
    FILE *in, *dict, *out;

    // Variável de controle para dizer se é avl. Se for 1, é AVL, se for 0 é ABP (padrão)
    int arv_type = 0;

    // Variáveis passadas como referência para estatísticas
    int num_nodos = 0, rotacoes = 0, altura = 0;

    // Criamos strings para armazenar as chaves e sinonimos lidos e inicializamos uma árvore
    char chave[40], sinonimo[40];
    Abp *arv = incializaArvore();
    Avl *arv_avl = inicializaAVL();
    int ok;

    // Abrimos e criamos arquivos com base nos parâmetros passados
    strcpy(in_name, argv[1]);
    strcpy(dicionario, argv[2]);
    strcpy(out_name, argv[3]);

    // verificamos se o flag é para AVL
    if (argv[4] != NULL && !strcmp(argv[4], "-avl"))
        arv_type = 1;
    
    abrir_criar_arquivos(&in, in_name, &dict, dicionario, &out, out_name);

    rewind(dict);

    // Construímos árvore de sinônimos (ABP)
    if(!arv_type){
        while(le_sinonimo(dict, chave, sinonimo)){
            arv = insereAbp(arv, chave, sinonimo);
            num_nodos++;
        }

        altura = Altura(arv);
        gera_parafrases(in, out, arv);
    } else {
        // Construímos a árvore de sinônimos (AVL)
        while(le_sinonimo(dict, chave, sinonimo)){
            arv_avl = insereAVL(arv_avl, chave, sinonimo, &ok, &rotacoes);
            num_nodos++;
        }
        
        altura = AlturaAVL(arv_avl);
        gera_parafrases_avl(in, out, arv_avl);
    }
    
    //Geramos estatísticas
    gera_estatisticas(arv_type, in_name, dicionario, num_nodos, altura, rotacoes, comp);

    // Fechamos os arquivos
    fechar_arquivos(in, dict, out);

    return 0;
}

int c_valid(char c){
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
    int res = 1, i, tam = strlen(separador);

    for(i = 0; i < tam; i++)
    {
        if(c == separador[i])
        {
            res = 0;
            i = tam;
        }
    }

    return res;
}

void gera_parafrases(FILE *in, FILE *out, Abp* arv){
    char palavra[40], c;
    int i = 0, naoespaco = 1;

    while ((c = getc(in)) != EOF){

        // Se for um caractere válido, construímos a palavra
        if (c_valid(c) && i < 39){
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
            }

            // preservamos caracteres "inválidos"
            fprintf(out, "%c", c);
            //printf("%c\n", c);

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
        if (c_valid(c) && i < 39){
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
            }

            // preservamos caracteres "inválidos"   
            fprintf(out, "%c", c);    

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

    setlocale(LC_ALL, "");
    fprintf(out, "%s", sinonimo); 
}

void escreve_sinonimo_avl(FILE *out, char palavra[40], Avl *arv)
{
    char sinonimo[40];
    Avl *temp = inicializaAVL();

    temp = consulta_avl(arv, palavra);

    // Se não existir sinônimo, escrevemos a própria palavra
    if (temp == NULL){
        strcpy(sinonimo, palavra);
    } else {
        strcpy (sinonimo, temp->sinonimo);
    }

    setlocale(LC_ALL, "");
    fprintf(out, "%s", sinonimo); 
}

// Função fornecida para consulta e calculo de comparações
Abp* consulta (Abp *a, char *chave){
    comp++;   

    
    while (a != NULL){
        if (!strcasecmp(a->chave, chave)){
            comp++;
            return a;
        } else {
            comp++;
            if (strcasecmp(a->chave, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL;
};

Avl* consulta_avl (Avl *a, char *chave)
{
    comp++;

    while (a != NULL){
        if (!strcasecmp(a->chave, chave)){
            comp++;
            return a;

        } else {
            comp++;
            
            if (strcasecmp(a->chave, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL;
}
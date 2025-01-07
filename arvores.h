#ifndef ARVORES_H
#define ARVORES_H

typedef struct nodoABP {
    char chave[40];
    char sinonimo[40];
    struct nodoABP *esq;
    struct nodoABP *dir;
} Abp;

typedef struct nodoAVL
{
    char chave[40];
    char sinonimo[40];
    int fb;
    struct TNodoA *esq;
    struct TNodoA *dir;
}Avl;

// Inicializa uma árvore vazia
Abp* incializaArvore (void);
Avl* inicializaAVL(void);

// Insere uma palavra com seu sinônimo em uma ABP baseado na ordem lexicográfica
Abp* insereAbp (Abp* arv, char chave[40], char sinonimo[40]);
Avl* insereAVL (Avl* a, char chave[40], char sinonimo[40], int *ok, int *rotacoes);

// calcula a altura de uma árvore
int Altura (Abp *a);
int AlturaAVL(Avl *a);

//Rotações AVL
Avl* rotacao_simples_direita (Avl* p);
Avl* rotacao_simples_esquerda (Avl* p);
Avl* rotacao_dupla_direita (Avl* p);
Avl* rotacao_dupla_esquerda (Avl* p);

//Funções Auxiliares para as Inserções
Avl* Caso1 (Avl *a , int *ok, int *rotacoes);
Avl* Caso2 (Avl *a , int *ok, int *rotacoes);

#endif
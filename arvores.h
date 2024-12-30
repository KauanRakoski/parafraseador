#ifndef ARVORES_H
#define ARVORES_H

typedef struct nodoABP {
    char chave[40];
    char sinonimo[40];
    struct nodoABP *esq;
    struct nodoABP *dir;
} Abp;

// Inicializa uma árvore vazia
Abp* incializaArvore (void);

// Insere uma palavra com seu sinônimo em uma ABP baseado na ordem lexicográfica
Abp* insereAbp (Abp* arv, char chave[40], char sinonimo[40]);

// calcula a altura de uma árvore
int Altura (Abp *a);


#endif
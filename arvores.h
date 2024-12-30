#ifndef ARVORES_H
#define ARVORES_H

typedef struct nodoABP {
    char chave[40];
    char sinonimo[40];
    struct nodoABP *esq;
    struct nodoABP *dir;
} Abp;

#endif
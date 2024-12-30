#include "arvores.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Abp* incializaArvore (void){
    return NULL;
}

Abp* insereAbp (Abp* arv, char chave[40], char sinonimo[40]){
    stringToLower(chave);
    stringToLower(sinonimo);

    if (arv == NULL){
        arv = (Abp*) malloc (sizeof(Abp));
        strcpy(arv->chave, chave);
        strcpy(arv->sinonimo, sinonimo);
        arv->esq = NULL;
        arv->dir = NULL;
    }

    // se for menor em ordem lexicográfica, inserimos na esquerda
    else if (strcmp(chave, arv->chave) < 0)
        arv->esq = insereAbp(arv->esq, chave, sinonimo);
    
    // senão, inserimos na direita
    else
        arv->dir = insereAbp(arv->dir, chave, sinonimo);

    return arv;
}

comp = 0;

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

    return a;
}

static void stringToLower (char palavra[40]){
    for (int i = 0; palavra[i] != '\0'; i++){
        palavra[i] = tolower(palavra[i]);
    }
}
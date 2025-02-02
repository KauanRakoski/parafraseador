#include "arvores.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


Abp* incializaArvore (void){
    return NULL;
}

Abp* insereAbp (Abp* arv, char chave[40], char sinonimo[40]){

    if (arv == NULL){
        arv = (Abp*) malloc (sizeof(Abp));
        strcpy(arv->chave, chave);
        strcpy(arv->sinonimo, sinonimo);
        arv->esq = NULL;
        arv->dir = NULL;
    }

    // se for menor em ordem lexicográfica, inserimos na esquerda
    else if (strcasecmp(chave, arv->chave) < 0){
        arv->esq = insereAbp(arv->esq, chave, sinonimo);
    }
    
    // senão, inserimos na direita
    else{
        arv->dir = insereAbp(arv->dir, chave, sinonimo);
    }

    return arv;
}

// Calcula a altura de uma ABP, baseado na quantidade de nós
int Altura (Abp *a){
    int Alt_Esq, Alt_Dir;
    
    if (a == NULL)
        return 0;

    else {
        // a altura da árvoré é 1 + a maior altura entre seus filhos
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);

        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}


Avl* inicializaAVL(void)
{
    return NULL;
}

//Insere AVL dos slides de aula com adaptações
Avl* insereAVL (Avl* a, char chave[40], char sinonimo[40], int *ok, int *rotacoes)
{

    if (a == NULL) 
    {
        a = (Avl*) malloc(sizeof(Avl));
        strcpy(a->sinonimo, sinonimo);
        strcpy(a->chave, chave);
        a->esq = NULL;
        a->dir = NULL;
        a->fb = 0;
        *ok = 1;
    }
    else if (strcasecmp(chave, a->chave) < 0) 
    {
        a->esq = insereAVL(a->esq,chave, sinonimo,ok, rotacoes);
        if (*ok) 
        {
            switch (a->fb) 
            {
                case -1: a->fb = 0; *ok = 0; break;
                case 0: a->fb = 1; break;
                case 1: a= Caso1(a,ok, rotacoes); break;
            }
        }
    }
    else 
    {
        a->dir = insereAVL(a->dir,chave, sinonimo,ok, rotacoes);
        if (*ok) 
        {
            switch (a->fb) 
            {
                case 1: a->fb = 0; *ok = 0; break;
                case 0: a->fb = -1; break;
                case -1: a = Caso2(a,ok, rotacoes); break;
            }
        }
    }
 return a;
}

// Calcula a altura de uma AVL
int AlturaAVL(Avl *a)
{
    int Alt_Esq, Alt_Dir;
    
    if (a == NULL)
        return 0;

    else {
        Alt_Esq = AlturaAVL (a->esq);
        Alt_Dir = AlturaAVL (a->dir);

        // A altura de um nó é 1 + a maior altura entre seus filhos
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

//Função oriunda dos slides de aula com adaptações
Avl* rotacao_simples_direita (Avl* p)
{
    Avl *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->fb = 0;
    p = u;
    return p;
}

//Função oriunda dos slides de aula com adaptações
Avl* rotacao_simples_esquerda (Avl* p)
{
    Avl *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->fb = 0;
    p = z;
    return p;

}

//Função oriunda dos slides de aula com adaptações
Avl* rotacao_dupla_direita (Avl* p)
{
    Avl *u, *v;

    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->fb == 1) p->fb = -1;
    else p->fb = 0;
    if (v->fb == -1) u->fb = 1;
    else u->fb = 0;
    p = v;
    return p;
}

//Função oriunda dos slides de aula com adaptações
Avl* rotacao_dupla_esquerda (Avl* p)
{
    Avl *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->fb == -1) p->fb = 1;
    else p->fb = 0;
    if (y->fb == 1) z->fb = -1;
    else z->fb = 0;
    p = y;
    return p;
}

//Função oriunda dos slides de aula com adaptações
Avl* Caso1 (Avl *a , int *ok, int *rotacoes)
{
    Avl *z;
    z = a->esq;
    if (z->fb == 1)
    {
        a = rotacao_simples_direita(a);
        *rotacoes += 1;
    }
       
    else
    {
        a = rotacao_dupla_direita(a);
        *rotacoes = *rotacoes + 1;
    }
        
    a->fb = 0;
    *ok = 0;
    return a;
}

//Função oriunda dos slides de aula com adaptações
Avl* Caso2 (Avl *a , int *ok, int *rotacoes)
{
    Avl *z = inicializaAVL();

    z = a->dir;
    if (z->fb == -1)
    {
        a = rotacao_simples_esquerda(a);
        *rotacoes+= 1;
    }

    else
    {
        a = rotacao_dupla_esquerda(a);
        *rotacoes = *rotacoes + 1;
    }

    a->fb = 0;
    *ok = 0;
    return a;
}

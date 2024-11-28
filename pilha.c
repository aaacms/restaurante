#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

Pilha* criaPilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memoria para a pilha.\n");
        exit(1);
    }

    p->prim = NULL;
    return p;
}
void push(Pilha *p, float v) {
    if (p == NULL) {
        printf("Pilha nao inicializada.\n");
        return;
    }
    Lista* n = (Lista*)malloc(sizeof(Lista));
    if (n == NULL) {
        printf("Erro ao alocar memoria para o novo elemento da pilha.\n");
        exit(1);
    }
    n->info = v;
    n->prox = p->prim;
    p->prim = n;
}

float pop(Pilha *p) {
    if (p->prim == NULL) {
        printf("Pilha vazia.\n");
        return -1;
    }
    Lista* t = p->prim;
    float v = t->info;
    p->prim = t->prox;
    free(t);
    return v;
}

void pilhaLibera(Pilha *p) {
    if (p != NULL) {
        Lista *atual = p->prim;
        while (atual != NULL) {
            Lista *temp = atual->prox;
            free(atual);
            atual = temp;
        }
        free(p);
    }
}

int tamanhoPilha(Pilha *p){
    int cont = 0;
    if (p != NULL) {
        Lista *atual = p->prim;
        while (atual != NULL) {
            Lista *temp = atual->prox;
            cont++;
            atual = temp;
        }
    }
    return cont;
}
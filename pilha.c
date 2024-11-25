
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

Pilha* criaPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL;
    return p;
}

void push(Pilha *p, float v) {
    Lista* n = (Lista*)malloc(sizeof(Lista));
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
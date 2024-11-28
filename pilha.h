#ifndef PILHA_H
#define PILHA_H

// Lista e Pilha de pratos
typedef struct lista {
    float info;
    struct lista* prox;
} Lista;

typedef struct pilha {
    Lista* prim; // aponta para o topo da pilha
} Pilha;

Pilha* criaPilha();
void push(Pilha *p, float v);
float pop(Pilha *p);
void pilhaLibera(Pilha *p);
int tamanhoPilha(Pilha *p);


#endif

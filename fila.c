//
// Created by amand on 30/10/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "fila.h"


Fila* filaCria(void){
    Fila* temp = (Fila*) malloc(sizeof(Fila));
    temp->n = 0;
    temp->ini = 0;
    return temp;
}

bool filaVazia(Fila* filaClientes){
    if(filaClientes->n == 0) return true;
    else return false;
}

void filaInsere(Fila* filaClientes, int quantos){
    int fim = (filaClientes->ini + filaClientes->n)%N;
    if(filaClientes->n == N){
        printf("Capacidade da fila estourou, não foi possível inserir!\n");
        return;
    }
    filaClientes->vet[fim]=quantos;
    filaCLientes->n++;
}

int filaRetira(Fila* filaClientes){
    if(!filaVazia(filaClientes)){
        int temp = filaClientes->vet[filaClientes->ini];
        filaClientes->ini=(filaClientes->ini + 1)%N;
        filaClientes->n--;
        return v;
    }else {
        printf("Fila vazia, nada a remover!");
        return 0;
    }
}

void filaLibera(Fila* filaClientes){
    free(filaClientes);
}

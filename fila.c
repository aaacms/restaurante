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
    return (filaClientes->n == 0);
}

void filaInsere(Fila* filaClientes, int quantos){
    int fim = (filaClientes->ini + filaClientes->n)%N;
    if(filaClientes->n == N){
        printf("Capacidade da fila estourou, não foi possível inserir!\n");
        return;
    }
    GrupoClientes novoGrupo = {quantos, filaClientes->n + 1};
    filaClientes->vet[fim] = novoGrupo;
    filaClientes->n++;
}

int filaRetira(Fila* filaClientes){
    if (!filaVazia(filaClientes)) {
        GrupoClientes temp = filaClientes->vet[filaClientes->ini];
        filaClientes->ini = (filaClientes->ini + 1) % 100;
        filaClientes->n--;
        return temp.qtd;
    } else {
        printf("Fila vazia, nada a remover!\n");
        return 0;
    }
}

void filaLibera(Fila* filaClientes){
    free(filaClientes);
}

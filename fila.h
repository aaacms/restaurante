//
// Created by amand on 30/10/2024.
//

#ifndef FILA_H
#define FILA_H

#endif //FILA_H

#define N 100

typedef struct fila {
    int n; 
    int ini;
    int vet[N];
}Fila;

Fila* filaCria(void);

bool filaVazia(Fila* filaClientes);
void filaInsere(Fila* filaClientes, int quantos);
int filaRetira(Fila* filaClientes);
void filaLibera(Fila* filaClientes);

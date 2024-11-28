#include <stdbool.h>
#ifndef FILA_H
#define FILA_H

#define N 100

typedef struct gpClientes {
    int qtd;
    int senha;
    struct gpClientes *prox;
} GrupoClientes;

typedef struct fila {
    GrupoClientes *ini;
    GrupoClientes *fim;
}Fila;

Fila* filaCria(void);
bool filaVazia(Fila* filaClientes);
void filaInsere(Fila* filaClientes, int quantos);
int filaRetira(Fila* filaClientes);
int filaRetiraMeio(Fila* filaClientes, int senha);
void filaLibera(Fila* f);
GrupoClientes* filaAcha(Fila* filaClientes, int senha);
int clientesDesistiram(GrupoClientes* grupo, Fila* filaClientes);

#endif
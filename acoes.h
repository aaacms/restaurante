#ifndef ACOES_H
#define ACOES_H
#include "fila.h"
#include "pilha.h"

typedef struct {
    int numero;
    int ocupada; // 0 = livre, 1 = ocupada
    int pessoas;
    int comanda;
} Mesa;

void abrirRestaurante(Mesa **mesas, int *linhas, int *colunas);

void chegarClientes(Mesa **mesas, int *linhas, int *colunas, Fila *filaClientes);

void finalizarRefeicao();

void desistirDeEsperar();

void reporPratos(Pilha *pilha);

void removerPratos(Pilha *pilha, int quantidade);

void imprimirEstado();

#endif //ACOES_H

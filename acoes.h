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

void abrirRestaurante(Mesa ***mesas, int *linhas, int *colunas, Pilha **pilhaPratos);

void colocaClienteNaMesa(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilhaPratos, int novos_clientes);

void chegarClientes(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilhaPratos);

void finalizarRefeicao(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilhaPratos);

void desistirDeEsperar(Fila *filaClientes);

void repoeAutomatico(Pilha** pilha);

void reporPratos(Pilha **pilha);

void removerPratos(Pilha *pilha, int quantidade);

void imprimirEstado(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilha);

#endif

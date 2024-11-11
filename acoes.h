//
// Created by amand on 06/11/2024.
//

#ifndef ACOES_H
#define ACOES_H

typedef struct {
    int numero;
    int ocupada; // 0 = livre, 1 = ocupada
    int pessoas;
    int comanda;
} Mesa;

void abrirRestaurante(Mesa ***mesas, int *linhas, int *colunas);

void chegarClientes();

void finalizarRefeicao();

void desistirDeEsperar();

void reporPratos();

void imprimirEstado();

#endif //ACOES_H

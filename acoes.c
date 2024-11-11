#include <stdio.h>
#include <stdlib.h>
#include "acoes.h"
#include "fila.h"
#include "pilha.h"


void abrirRestaurante(Mesa **mesas, int *linhas, int *colunas) {

    printf("Informe o número de linhas de mesas: ");
    scanf("%d", linhas);
    printf("Informe o número de colunas de mesas: ");
    scanf("%d", colunas);


    mesas = (Mesa **)malloc((*linhas) * sizeof(Mesa **));
    for (int i = 0; i < *linhas; i++) {
        mesas[i] = (Mesa *)malloc((*colunas) * sizeof(Mesa));
    }


    int contador = 1;
    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            mesas[i][j].numero = contador;
            mesas[i][j].ocupada = 0;
            mesas[i][j].pessoas = 0;
            mesas[i][j].comanda = 0;
            contador++;
        }
    }

    printf("Restaurante aberto com %d mesas (%d linhas x %d colunas).\n", (*linhas) * (*colunas), *linhas, *colunas);
}

void chegarClientes() {
    // Implementar lógica para chegada de clientes e alocação de mesas ou fila de espera

}

void finalizarRefeicao() {
    // Implementar lógica para finalizar refeição, liberar mesa e chamar clientes da fila

}

void desistirDeEsperar() {
    // Implementar lógica para remover grupo da fila de espera

}

void reporPratos() {
    // Implementar lógica para adicionar pratos à pilha de pratos

}

void imprimirEstado() {
    // Implementar lógica para imprimir estado atual das mesas, fila de espera e pilha de pratos

}

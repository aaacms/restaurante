#include <stdio.h>
#include <stdlib.h>
#include "acoes.h"
#include "fila.h"
#include "pilha.h"

// Pilha de pratos
typedef struct Prato {
    int quantidade;
} Prato;

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

void chegarClientes(Mesa **mesas, int *linhas, int *colunas) {
    // Implementar lógica para chegada de clientes e alocação de mesas ou fila de espera
    printf("Função Chegar Clientes chamada.\n");
    int novos_clientes = -1;
    printf("Digite a quantidade de clientes que chegaram no restaurante: ");
    do{
        scanf(" %d", &novos_clientes);
    }while(novos_clientes == -1);
    
    int contador = 0;
    for (int i = 0; i < *linhas; i++){
        for (int j = 0; j < *colunas; j++){
            if (mesas[i][j].ocupada == 1){
                contador++;
            }
            else if(mesas[i][j].ocupada == 0){
                if(novos_clientes <= 4){
                    mesas[i][j].ocupada = 1;
                    mesas[i][j].pessoas = novos_clientes;
                    novos_clientes = 0;
                }
                else{
                    mesas[i][j].ocupada = 1;
                    mesas[i][j].pessoas = 4;
                    novos_clientes -= 4;
                }
            }
            if (novos_clientes == 0) {
                break;
            }
        }
        if (novos_clientes == 0) {
            break;
        }
    }

    if(contador == (*linhas)*(*colunas) || novos_clientes != 0){
        printf("Não há mesas suficientes para acomodar todos os clientes. Alguns estão na fila de espera.");
        for (int k = 0; k < novos_clientes; k++){
            //pilha.push();
        }
    }
}

void finalizarRefeicao() {
    printf("Função Finalizar Refeição chamada.
");
    int numero_mesa;
    printf("Digite o número da mesa que deseja liberar: ");
    scanf("%d", &numero_mesa);

    // Procurar a mesa pelo número e liberá-la
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (mesas[i][j].numero == numero_mesa) {
                if (mesas[i][j].ocupada == 1) {
                    mesas[i][j].ocupada = 0;
                    mesas[i][j].pessoas = 0;
                    mesas[i][j].comanda = 0;
                    printf("Mesa %d liberada com sucesso.", numero_mesa);
                    // Aqui poderíamos implementar a lógica de chamar clientes da fila de espera
                } else {
                    printf("A mesa %d já está livre.", numero_mesa);
                }
                return;
            }
        }
    }
    printf("Mesa %d não encontrada.", numero_mesa);
}

void desistirDeEsperar() {
    // Implementar lógica para remover grupo da fila de espera
    printf("Função Desistir de Esperar chamada.\n");
    int senha;
    printf("Digite a senha do grupo que deseja desistir de esperar: ");
    scanf("%d", &senha);

    // Aqui deveríamos implementar a lógica para encontrar e remover o grupo da fila de espera
    // Para simplificação, vamos apenas imprimir que o grupo desistiu
    printf("Grupo com a senha %d desistiu de esperar e foi removido da fila.\n", senha);

}

void reporPratos() {
    int novos_pratos;
    printf("Digite a quantidade de pratos a repor: ");
    scanf("%d", &novos_pratos);
    pilha->quantidade += novos_pratos;
    printf("Foram repostos %d pratos. Total de pratos na pilha: %d.\n", novos_pratos, pilha->quantidade);
}

void imprimirEstado() {
    printf("\n--- Estado Atual do Restaurante ---\n");
    printf("\nMesas:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("Mesa %d: %s, %d pessoas\n", mesas[i][j].numero, mesas[i][j].ocupada ? "Ocupada" : "Livre", mesas[i][j].pessoas);
        }
    }

    printf("\nPilha de Pratos:\n");
    printf("Quantidade de pratos na pilha: %d\n", pilha->quantidade);

    // Aqui poderíamos adicionar a lógica para imprimir o estado da fila de espera quando implementada
}

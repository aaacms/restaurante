#include <stdio.h>
#include <stdlib.h>
#include "acoes.h"
#include "fila.h"
#include "pilha.h"

void abrirRestaurante(Mesa ***mesas, int *linhas, int *colunas, Pilha **pilhaPratos) {

    printf("Informe o número de linhas de mesas: ");
    scanf("%d", linhas);
    printf("Informe o número de colunas de mesas: ");
    scanf("%d", colunas);

    *mesas = (Mesa **)malloc((*linhas) * sizeof(Mesa *));
    if (*mesas == NULL) {
        printf("Erro ao alocar memória para as linhas de mesas.\n");
        exit(1);
    }
    for (int i = 0; i < *linhas; i++) {
        (*mesas)[i] = (Mesa *)malloc((*colunas) * sizeof(Mesa));
        if ((*mesas)[i] == NULL) {
            printf("Erro ao alocar memória para as colunas de mesas.\n");
            exit(1);
        }
    }
    
    int contador = 1;
    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            (*mesas)[i][j].numero = contador;
            (*mesas)[i][j].ocupada = 0;
            (*mesas)[i][j].pessoas = 0;
            (*mesas)[i][j].comanda = 0;
            for (int k = 0; k < 4; k++) {
                push(*pilhaPratos, 1);
            }
            contador++;
        }
    }

    printf("Restaurante aberto com %d mesas (%d linhas x %d colunas).\n", (*linhas) * (*colunas), *linhas, *colunas);
}

void removerPratos(Pilha *pilha, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        if (pop(pilha) == -1) {
            printf("Não há pratos suficientes para remover.\n");
            break;
        }
    }
}

void colocaClienteNaMesa(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilhaPratos, int novos_clientes) {

    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            if (mesas[i][j].ocupada == 0)
            {
                if(novos_clientes <= 4)
                {
                    mesas[i][j].ocupada = 1;
                    mesas[i][j].pessoas = novos_clientes;
                    //remove pratos da pilha para colocar na mesa para os clientes que chegaram
                    removerPratos(*pilhaPratos, mesas[i][j].pessoas);
                    novos_clientes = 0;
                }
                else
                {
                    mesas[i][j].ocupada = 1;
                    mesas[i][j].pessoas = 4;
                    novos_clientes -= 4;
                }
            }
            if (novos_clientes == 0)
            {
                break;
            }
        }
        if (novos_clientes == 0)
        {
            break;
        }
    }

    if(novos_clientes > 0){
        printf("Não há mesas suficientes para acomodar todos os clientes. Alguns estão na fila de espera.");
        filaInsere(*filaClientes, novos_clientes);
    }
}

void chegarClientes(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilhaPratos) {

    int novos_clientes = -1;

    printf("Digite a quantidade de clientes que chegaram no restaurante: ");
    do {
        scanf(" %d", &novos_clientes);
    } while (novos_clientes < 0);
    
    colocaClienteNaMesa(mesas, linhas, colunas, filaClientes, pilhaPratos, novos_clientes);
}



void finalizarRefeicao(Mesa **mesas, int *linhas, int *colunas, Fila *filaClientes, Pilha *pilhaPratos) {
    printf("Função Finalizar Refeição chamada.");
    int numero_mesa;
    printf("Digite o número da mesa que deseja liberar: ");
    scanf("%d", &numero_mesa);

    // Procurar a mesa pelo número e liberá-la
    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            if (mesas[i][j].numero == numero_mesa) {
                if (mesas[i][j].ocupada == 1) {
                    mesas[i][j].ocupada = 0;
                    mesas[i][j].pessoas = 0;
                    mesas[i][j].comanda = 0;
                    printf("Mesa %d liberada com sucesso.", numero_mesa);

                    if (!filaVazia(filaClientes)) {
                        int grupo = filaRetira(filaClientes);
                        printf("Chamando grupo da fila de espera com %d pessoas.\n", grupo);
                        colocaClienteNaMesa(mesas, linhas, colunas, &filaClientes, &pilhaPratos, grupo);
                    }
                } else {
                    printf("A mesa %d já está livre.", numero_mesa);
                }
                return;
            }
        }
    }
    printf("Mesa %d não encontrada.", numero_mesa);
}

void desistirDeEsperar(Fila *filaClientes) {

    if (filaVazia(filaClientes)) {
        printf("Nenhum grupo na fila de espera para desistir.\n");
    } else {
        int senha;
        printf("Digite a senha do grupo que deseja desistir de esperar: ");
        scanf("%d", &senha);
        int removido = filaRetiraMeio(filaClientes, senha);
        if (removido > 0) {
            printf("Grupo com a senha %d desistiu de esperar e foi removido da fila.\n", senha);
        }
    }
}

void reporPratos(Pilha *pilha) {
    int novos_pratos;
    printf("Digite a quantidade de pratos a repor: ");
    scanf("%d", &novos_pratos);
    for (int i = 0; i < novos_pratos; i++) {
        push(pilha, 1);
    }
    printf("Foram repostos %d pratos.\n", novos_pratos);
}

void imprimirEstado(Mesa **mesas, int *linhas, int *colunas, Pilha *pilha, Fila *filaClientes) {
    printf("\n\t\t--- Estado Atual do Restaurante ---\n");
    printf("\nMesas:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("\tMesa %d: %s, %d pessoas\n", mesas[i][j].numero, mesas[i][j].ocupada ? "Ocupada" : "Livre", mesas[i][j].pessoas);
        }
    }

    printf("\nPilha de Pratos:\n");
    printf("\tQuantidade de pratos na pilha: %d\n", tamanhoPilha(pilha));

    printf("\nFila de Espera:\n");
    if (filaVazia(filaClientes)) {
        printf("\tNenhum grupo aguardando na fila de espera.\n");
    } else {
        GrupoClientes *atual = filaClientes->ini;
        while (atual != NULL) {
            printf("\tGrupo com senha %d: %d pessoas aguardando\n", atual->senha, atual->qtd);
            atual = atual->prox;
        }
    }
}

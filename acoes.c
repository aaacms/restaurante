#include <stdio.h>
#include <stdlib.h>
#include "acoes.h"
#include "pilha.h"
#include "fila.h"


void abrirRestaurante(Mesa ***mesas, int *linhas, int *colunas, Pilha **pilhaPratos) {

    printf("Informe o numero de linhas de mesas: ");
    scanf("%d", linhas);
    printf("Informe o numero de colunas de mesas: ");
    scanf("%d", colunas);

    *mesas = (Mesa **)malloc((*linhas) * sizeof(Mesa *));
    if (*mesas == NULL) {
        printf("Erro ao alocar memoria para as linhas de mesas.\n");
        exit(1);
    }
    for (int i = 0; i < *linhas; i++) {
        (*mesas)[i] = (Mesa *)malloc((*colunas) * sizeof(Mesa));
        if ((*mesas)[i] == NULL) {
            printf("Erro ao alocar memoria para as colunas de mesas.\n");
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
            printf("Nao ha pratos suficientes na pilha.\n");
            reporPratos(&pilha);
            pop(pilha);
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
                    printf(" - %d acomodados na mesa %d\n", mesas[i][j].pessoas, mesas[i][j].numero);
                    novos_clientes = 0;
                }
                else
                {
                    mesas[i][j].ocupada = 1;
                    mesas[i][j].pessoas = 4;
                    //remove pratos da pilha para colocar na mesa para os clientes que chegaram
                    removerPratos(*pilhaPratos, mesas[i][j].pessoas);
                    printf(" - %d acomodados na mesa %d\n", mesas[i][j].pessoas, mesas[i][j].numero);
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
        printf(" - Nao ha mesas suficientes para acomodar todos os clientes. %d foram alocados na fila de espera.\n", novos_clientes);
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



void finalizarRefeicao(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilhaPratos) {

    int numero_mesa;
    printf("Digite o numero da mesa que deseja liberar: ");
    scanf("%d", &numero_mesa);

    // Procurar a mesa pelo numero e libera-la
    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            if (mesas[i][j].numero == numero_mesa) {
                if (mesas[i][j].ocupada == 1) {
                    mesas[i][j].ocupada = 0;
                    mesas[i][j].pessoas = 0;
                    mesas[i][j].comanda = 0;
                    printf(" - Mesa %d liberada com sucesso.\n", numero_mesa);

                    if (!filaVazia(*filaClientes)) {
                        int grupo = filaRetira(*filaClientes);
                        printf(" - Chamando grupo da fila de espera com %d pessoas.\n", grupo);
                        colocaClienteNaMesa(mesas, linhas, colunas, filaClientes, pilhaPratos, grupo);
                    }
                } else {
                    printf("A mesa %d ja esta livre.\n", numero_mesa);
                }
                return;
            }
        }
    }
    printf("Mesa %d nao encontrada.\n", numero_mesa);
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
            printf(" - Grupo com a senha %d desistiu de esperar e foi removido da fila.\n", senha);
        }
    }
}

void repoeAutomatico(Pilha** pilha){
    int novos_pratos = 20;
    for (int i = 0; i < novos_pratos; i++) {
        push(*pilha, 1);
    }
    printf(" - Foram repostos automaticamente %d pratos.\n", novos_pratos);
}

void reporPratos(Pilha **pilha) {
    int novos_pratos;
    printf("Digite a quantidade de pratos a repor: ");
    scanf("%d", &novos_pratos);
    for (int i = 0; i < novos_pratos; i++) {
        push(*pilha, 1);
    }
    printf(" - Foram repostos %d pratos.\n", novos_pratos);
}

void imprimirEstado(Mesa **mesas, int *linhas, int *colunas, Fila **filaClientes, Pilha **pilha) {
    printf("\n\t\t--- Estado Atual do Restaurante ---\n");
    printf("\nMesas:\n");
    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            printf("\tMesa %d: %s, %d pessoas\n", mesas[i][j].numero, mesas[i][j].ocupada ? "Ocupada" : "Livre", mesas[i][j].pessoas);
        }
    }

    printf("\nPilha de Pratos:\n");
    printf("\tQuantidade de pratos na pilha: %d\n", tamanhoPilha(*pilha));

    printf("\nFila de Espera:\n");
    if (filaVazia(*filaClientes)) {
        printf("\tNenhum grupo aguardando na fila de espera.\n");
    } else {
        GrupoClientes *atual = (*filaClientes)->ini;
        while (atual != NULL) {
            printf("\tGrupo com senha %d: %d pessoas aguardando\n", atual->senha, atual->qtd);
            atual = atual->prox;
        }
    }
}

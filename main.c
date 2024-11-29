#include <stdio.h>
#include "acoes.h"
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"

void menu(Mesa **mesas, int *linhas, int *colunas, Pilha **pilhaPratos, Fila **filaClientes, bool *naFila) {
    int opcao, cont_pratos = 0;

    do {
        printf("\n--- Sistema de Gerenciamento de Restaurante ---\n");
        printf("1) Abrir restaurante\n");
        printf("2) Chegar clientes ao restaurante\n");
        printf("3) Finalizar refeicao/liberar mesa\n");
        printf("4) Desistir de esperar\n");
        printf("5) Repor pratos\n");
        printf("6) Imprimir estado do restaurante\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                abrirRestaurante(&mesas, linhas, colunas, pilhaPratos);
                break;
            case 2:
                chegarClientes(mesas, linhas, colunas, filaClientes, pilhaPratos, naFila);
                break;
            case 3:
                finalizarRefeicao(mesas, linhas, colunas, filaClientes, pilhaPratos, naFila);
                break;
            case 4:
                desistirDeEsperar(*filaClientes);
                break;
            case 5:
                reporPratos(pilhaPratos);
                break;
            case 6:
                imprimirEstado(mesas, linhas, colunas, filaClientes, pilhaPratos);
                break;
            case 0:
                printf("Saindo...\n");
                if (mesas != NULL) {
                     for (int i = 0; i < *linhas; i++) {
                        free(mesas[i]);
                    }
                    free(mesas);
                }
                if (*filaClientes != NULL) {
                    filaLibera(*filaClientes);
                }
                if (*pilhaPratos != NULL) {
                    pilhaLibera(*pilhaPratos);
                }
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        cont_pratos++;
        if(cont_pratos%6 == 0){
            printf("\nUm funcionário está repondo os pratos...\n");
            repoeAutomatico(pilhaPratos);
        }

    } while(opcao != 0);
}

int main() {
    Mesa *mesas = NULL;
    int linhas = 0, colunas = 0;
    bool naFila = false;
    Pilha *pilhaPratos = criaPilha();
    Fila *filaClientes = filaCria();
    menu(&mesas, &linhas, &colunas, &pilhaPratos, &filaClientes, &naFila);
    return 0;
}


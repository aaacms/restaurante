#include <stdio.h>
#include "acoes.h"
#include <stdlib.h>

#include "fila.h"
#include "pilha.h"

void menu(Mesa **mesas, int *linhas, int *colunas, Pilha *pilhaPratos, Fila *filaClientes) {
    int opcao;

    do {
        printf("\n--- Sistema de Gerenciamento de Restaurante ---\n");
        printf("1) Abrir restaurante\n");
        printf("2) Chegar clientes ao restaurante\n");
        printf("3) Finalizar refeição/liberar mesa\n");
        printf("4) Desistir de esperar\n");
        printf("5) Repor pratos\n");
        printf("6) Imprimir estado do restaurante\n");
        printf("0) Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                abrirRestaurante(&mesas, &linhas, &colunas, &pilhaPratos);
                break;
            case 2:
                chegarClientes(mesas, &linhas, &colunas, &filaClientes);
                break;
            case 3:
                finalizarRefeicao(mesas, linhas, colunas);
                break;
            case 4:
                desistirDeEsperar();
                break;
            case 5:
                reporPratos(&pilhaPratos);
                break;
            case 6:
                imprimirEstado(mesas, linhas, colunas, &pilhaPratos);
                break;
            case 0:
                printf("Saindo...\n");
                if (mesas != NULL) {
                    for (int i = 0; i < linhas; i++) {
                        free(mesas[i]);
                    }
                    free(mesas);
                }
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

int main() {
    Mesa *mesas = NULL;
    int linhas = 0, colunas = 0;
    Pilha* pilhaPratos = criaPilha();
    Fila* filaClientes = filaCria();
    menu(&mesas, &linhas, &colunas, &pilhaPratos, &filaClientes);
    return 0;
}


#include <stdio.h>
#include "acoes.h"
#include <stdlib.h>

void menu(Mesa **mesas, int *linhas, int *colunas) {
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
                abrirRestaurante(mesas, linhas, colunas);
            break;
            case 2:
                chegarClientes(mesas, linhas, colunas);
            break;
            case 3:
                finalizarRefeicao();
            break;
            case 4:
                desistirDeEsperar();
            break;
            case 5:
                reporPratos();
            break;
            case 6:
                imprimirEstado();
            break;
            case 0:
                printf("Saindo...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

int main() {
    Mesa *mesas = NULL;
    int linhas = 0, colunas = 0;
    menu(&mesas, &linhas, &colunas);
    return 0;
}


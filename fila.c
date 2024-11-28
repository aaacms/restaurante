#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "fila.h"


Fila* filaCria() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

bool filaVazia(Fila* filaClientes){
    if (filaClientes == NULL) {
        printf("Fila não inicializada.\n");
        return true;
    }
    return (filaClientes->ini == 0);
}

void filaInsere(Fila* filaClientes, int quantos){
    if (filaClientes == NULL) {
        printf("Fila não inicializada.\n");
        return;
    }
    GrupoClientes* novoGrupo = (GrupoClientes*) malloc(sizeof(GrupoClientes));
    if (novoGrupo == NULL) {
        printf("Erro ao alocar memória para o novo grupo de clientes.\n");
        exit(1);
    }

    novoGrupo->qtd = quantos;
    novoGrupo->senha = (filaClientes->fim == NULL) ? 1 : filaClientes->fim->senha + 1;
    novoGrupo->prox = NULL;

    if (filaVazia(filaClientes)) {
        filaClientes->ini = novoGrupo;
    } else {
        filaClientes->fim->prox = novoGrupo;
    }
    filaClientes->fim = novoGrupo;
}

int filaRetira(Fila* filaClientes){
    if (filaClientes == NULL || filaVazia(filaClientes)) {
        printf("Fila vazia ou não inicializada, nada a remover!\n");
        return 0;
    }
    GrupoClientes* temp = filaClientes->ini;
    int qtdRemovido = temp->qtd;
    filaClientes->ini = temp->prox;
    if (filaClientes->ini == NULL) {
        filaClientes->fim = NULL;
    }
    free(temp);
    return qtdRemovido;
}

int filaRetiraMeio(Fila* filaClientes, int senha) {
    if (filaClientes == NULL || filaVazia(filaClientes)) {
        printf("Fila vazia ou não inicializada, nada a remover!\n");
        return 0;
    }
    GrupoClientes* atual = filaClientes->ini;
    GrupoClientes* anterior = NULL;

    while (atual != NULL && atual->senha != senha) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Grupo com a senha %d não encontrado na fila.\n", senha);
        return 0;
    }

    int qtdRemovido = atual->qtd;
    if (anterior == NULL) {
        // O grupo a ser removido está no início da fila
        filaClientes->ini = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    if (atual == filaClientes->fim) {
        // O grupo a ser removido está no final da fila
        filaClientes->fim = anterior;
    }

    free(atual);
    return qtdRemovido;
}

void filaLibera(Fila *f) {
    if (f != NULL) {
        GrupoClientes* atual = f->ini;
        while (atual != NULL) {
            GrupoClientes* temp = atual->prox;
            free(atual);
            atual = temp;
        }
        free(f);
    }
}

GrupoClientes* filaAcha(Fila* filaClientes, int senha){
    if(filaClientes->ini == NULL) return NULL;
    GrupoClientes* temp = filaClientes;
    for(; temp != NULL; temp = temp->prox){
        if(temp->senha == senha) return temp;
    }
    printf("Não há um grupo com essa senha na fila. Tente outra.\n");
    return NULL;
}

int clientesDesistiram(GrupoClientes* grupo, Fila* filaClientes){
    int retorno;
    if(grupo == filaClientes->ini){
        retorno = filaRetira(filaClientes);
        return retorno;
    }
    GrupoClientes* aux = filaClientes->ini;
    GrupoClientes* ant = NULL;
    while(aux != grupo){
        ant = aux;
        aux = aux->prox;
    }
    if(grupo == filaClientes->fim){
        filaClientes->fim = ant;
        ant->prox = NULL;
        retorno = aux->qtd;
        free(aux);
        return retorno;
    }
    ant->prox = aux->prox;
    retorno = aux->qtd;
    free(aux);
    return retorno;
}
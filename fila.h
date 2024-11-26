#ifndef FILA_H
#define FILA_H



#define N 100

typedef struct gpClientes {
    int qtd;
    int senha;
} GrupoClientes;

typedef struct fila {
    int n; 
    int ini;
    GrupoClientes vet[N];
}Fila;

Fila* filaCria(void);

bool filaVazia(Fila* filaClientes);
void filaInsere(Fila* filaClientes, int quantos);
int filaRetira(Fila* filaClientes);
void filaLibera(Fila* filaClientes);

#endif //FILA_H
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

struct pacote
{
    char tipo;
    float peso;
    int valido;
};

struct no
{
    Pacote pacote;
    struct no *prox;
};

struct fila {
    Lista * inicio;
    Lista * fim;
    int tamanho;
};

Fila * criarFila() {
    Fila * fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void enfileirar(Fila * fila, Pacote pacote) {
    Lista * novo = (Lista*)malloc(sizeof(Lista));
    novo->pacote = pacote;
    novo->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

Pacote desenfileirar(Fila * fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia. N�o � poss�vel desenfileirar.\n");
        exit(1);
    }
    Lista * temp = fila->inicio;
    Pacote pacote = temp->pacote;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(temp);
    fila->tamanho--;
    return pacote;
    
}

int filaVazia(Fila * fila) {
    return (fila->tamanho == 0) ? 1 : 0;
}

void destruirFila(Fila* fila) {
    while (!filaVazia(fila)) {
        desenfileirar(fila);
    }
    free(fila);
}

void imprimirFila(Fila * fila) {
    Lista * atual = fila->inicio;
    while (atual != NULL) {
        printf("Pacote [Tipo: %c, Peso: %.2f, Valido: %s]\n",
               atual->pacote.tipo,
               atual->pacote.peso,
               atual->pacote.valido ? "Sim" : "Nao");
        atual = atual->prox;
    }
}

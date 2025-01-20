#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

struct pilha
{
    Lista *topo;
    int tamanho;
};

Pilha *criarPilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void empilharPacote(Pilha *pilha, Pacote pacote)
{
    Lista *novoNo = (Lista *)malloc(sizeof(Lista));
    novoNo->pacote = pacote;
    novoNo->prox = pilha->topo;
    pilha->topo = novoNo;
    pilha->tamanho++;
    printf("Pacote do tipo %c com peso %.2f empilhado.\n", pacote.tipo, pacote.peso);
}

Pacote desempilharPacote(Pilha *pilha)
{
    if (pilhaVazia(pilha))
    {
        printf("Pilha vazia!\n");
        exit(1);
    }
    Lista *noRemovido = pilha->topo;
    Pacote pacote = noRemovido->pacote;
    pilha->topo = noRemovido->prox;
    free(noRemovido);
    pilha->tamanho--;
    return pacote;
}

int pilhaVazia(Pilha *pilha)
{
    return pilha->topo == NULL;
}

void destruirPilha(Pilha *pilha)
{
    while (!pilhaVazia(pilha))
    {
        desempilharPacote(pilha);
    }
    free(pilha);
}

#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Estrutura de uma pilha
struct pilha
{
    int quantidadeEmbalagens;
    int quantidadePacotes;
    int capacidade;
    Fila *topo;
};

// Cria uma nova pilha
Pilha *criarPilha(int limite)
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha != NULL)
    {
        pilha->topo = NULL;
        pilha->quantidadeEmbalagens = 0;
        pilha->quantidadePacotes = 0;
        pilha->capacidade = limite;
    }
    else
    {
        printf("Erro ao alocar memoria para a pilha.\n");
        return NULL;
    }
    return pilha;
}

// Empilha uma fila na pilha
void empilhar(Pilha *pilha, Fila *fila)
{
    if (fila == NULL)
    {
        printf("Fila vazia.\n");
        return;
    }
    if (pilha == NULL)
    {
        printf("Pilha nao criada.\n");
        return;
    }
    if (pilha->quantidadeEmbalagens == pilha->capacidade)
    {
        printf("Nao eh possivel empilhar! A pilha suporta apenas %d embalagens.\n", pilha->capacidade);
        return;
    }
    fila->prox = pilha->topo;
    pilha->topo = fila;
    pilha->quantidadeEmbalagens++;
    pilha->quantidadePacotes += fila->unidades;
    printf("Embalagem empilhada com sucesso!\n");
}

// Desempilha uma fila da pilha
void desempilhar(Pilha *pilha)
{
    if (pilha->topo == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }
    Fila *fila = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->quantidadeEmbalagens--;
    pilha->quantidadePacotes -= fila->unidades;
    destruirFila(fila);
}

// Imprime a pilha
void imprimirPilha(Pilha *pilha)
{
    if (pilha->topo == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }
    Fila *atual = pilha->topo;
    int i = pilha->quantidadeEmbalagens;
    while (atual != NULL)
    {
        printf("--- [%d] - EMBALAGEM - %s ----------------------------------------\n", i--, pilha->topo->inicio->pacote.tipo);
        imprimirFila(atual);
        atual = atual->prox;
    }
}

// Destrói a pilha
void destruirPilha(Pilha *pilha)
{
    while ((pilha)->topo != NULL)
    {
        desempilhar(pilha);
    }
    free(pilha);
    pilha = NULL;
}
#include <stdio.h>
#include "Fila.h"
#include "Pilha.h"
#include <stdlib.h>

struct pilha
{
    Fila *topo;
    int tamanho;
};

Pilha *criarPilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha != NULL)
    {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
    else
    {
        printf("Erro ao alocar memoria para a pilha.\n");
        return NULL;
    }
    return pilha;
}

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
    fila->prox = (pilha)->topo;
    (pilha)->topo = fila;
    (pilha)->tamanho++;
}

void desempilhar(Pilha **pilha)
{
    if ((*pilha)->topo == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }
    Fila *fila = (*pilha)->topo;
    (*pilha)->topo = (*pilha)->topo->prox;
    (*pilha)->tamanho--;
    destruirFila(fila);
}

void imprimirPilha(Pilha *pilha)
{
    if (pilha->topo == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }
    Fila *atual = pilha->topo;
    int i = 1;
    while (atual != NULL)
    {
        printf("---------------------- [%d] ----------------------\n", i++);
        imprimirFila(atual);
        atual = atual->prox;
    }
}

void imprimirTamanho(Pilha *pilha)
{
    printf("Tamanho da pilha: %d\n", pilha->tamanho);
}

void destuirPilha(Pilha **pilha)
{
    while ((*pilha)->topo != NULL)
    {
        desempilhar(pilha);
    }
    free(*pilha);
    *pilha = NULL;
}
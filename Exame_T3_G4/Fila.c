#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"


// Estrutura de um pacote de sumo
struct pacote
{
    int id;
    char tipo[3];
    float peso;
    int valido;
    int cheio;
};

// Estrutura de um nó da lista
struct no
{
    Pacote pacote;
    struct no *prox;
};

// Estrutura de uma fila
struct fila
{
    Lista *inicio;
    Lista *fim;
    int unidades;
    struct fila *prox; // Apontador para a próxima fila
};

// Cria uma nova fila
Fila *criarFila()
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    fila->unidades = 0;
    return fila;
}

// Enfileira um pacote na fila
void enfileirar(Fila *fila, Pacote pacote)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->pacote = pacote;
    novo->prox = NULL;
    if (fila->fim == NULL)
    {
        fila->inicio = fila->fim = novo;
    }
    else
    {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->unidades++;
}

// Desenfileira um pacote da fila
Pacote desenfileirar(Fila *fila)
{
    if (filaVazia(fila))
    {
        printf("[Erro] Fila vazia. Nao e possivel desenfileirar.\n");
        Pacote pacoteVazio;
        pacoteVazio.id = -1;
        return pacoteVazio;
    }
    Lista *temp = fila->inicio;
    Pacote pacote = temp->pacote;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;
    free(temp);
    fila->unidades--;
    return pacote;
}

// Desenfileira um pacote específico da fila
Pacote desenfileirarPacote(Fila *fila, Pacote pacote)
{
    if (filaVazia(fila))
    {
        printf("A fila está vazia.\n");
        Pacote pacoteVazio;
        pacoteVazio.id = -1;
        return pacoteVazio;
    }

    Lista *atual = fila->inicio;
    Lista *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->pacote.id == pacote.id)
        {
            if (anterior == NULL)
            {
                // O pacote está no início da fila
                fila->inicio = atual->prox;
            }
            else
            {
                // O pacote está no meio ou no final da fila
                anterior->prox = atual->prox;
            }

            if (atual == fila->fim)
            {
                // O pacote está no final da fila
                fila->fim = anterior;
            }

            Pacote pacoteRemovido = atual->pacote;
            free(atual);
            fila->unidades--;
            return pacoteRemovido;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Pacote não encontrado na fila.\n");
    Pacote pacoteNaoEncontrado;
    pacoteNaoEncontrado.id = -1; // Indica que o pacote não foi encontrado
    return pacoteNaoEncontrado;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila)
{
    return (fila->unidades == 0) ? 1 : 0;
}

// Destrói a fila
void destruirFila(Fila *fila)
{
    while (!filaVazia(fila))
    {
        desenfileirar(fila);
    }
    free(fila);
}

// Imprime a fila
void imprimirFila(Fila *fila)
{
    Lista *atual = fila->inicio;
    while (atual != NULL)
    {
        printf("Pacote [ID: %03d, Tipo: %s, Peso: %.2f, Valido: %s, Cheio: %s]\n",
               atual->pacote.id,
               atual->pacote.tipo,
               atual->pacote.peso,
               atual->pacote.valido ? "Sim" : "Nao",
               atual->pacote.cheio ? "Sim" : "Nao");
        atual = atual->prox;
    }
}
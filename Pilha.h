#include "Fila.h"
typedef struct pilha Pilha;

Pilha *criarPilha();
void empilhar(Pilha *pilha, Fila *fila);
void desempilhar(Pilha **pilha);
void ImprimirPilha(Pilha *pilha);
void imprimirTamanho(Pilha *pilha);
void destruirPilha(Pilha **pilha);
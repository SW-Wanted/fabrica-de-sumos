#include "Fila.h"
typedef struct pilha Pilha;

Pilha *criarPilha(int limite);
void empilhar(Pilha *pilha, Fila *fila);
void desempilhar(Pilha *pilha);
void imprimirPilha(Pilha *pilha);
void destruirPilha(Pilha *pilha);
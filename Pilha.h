#include "Fila.h"
typedef struct no Lista;
typedef struct pilha Pilha;


Pilha * criarPilha();
void empilharPacote(Pilha *pilha, Pacote pacote);
Pacote desempilharPacote(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void destruirPilha(Pilha *pilha);

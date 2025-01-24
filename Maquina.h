#include "Pilha.h"
typedef struct maquina Maquina;

Maquina *criarMaquina(char *nome, char *tipo, int tempoProcessamento, int capacidade);
void encherPacotes(Maquina *maquina, Fila *filaEnchimento, Fila *filaEmbalamento);
void inserirPacoteManual(Fila *filaPA, Fila *filaPB);
void inserirPacoteAutomatico(Fila *filaPA, Fila *filaPB, const char *nomeArquivo);
void validarPacotes(Fila *filaEmbalamento, int *prejuizo);
void encaminhar(Fila *filaEmbalamento, Maquina *maquina);
void embalarPacotes(Maquina *maquinaEmbalamento, Pilha *pilhaEmbalagem, int limite, int tempoProcessamento);
void empilharEmbalagem(Pilha *pilha, Fila *embalagens);
void destruirMaquina(Maquina *maquina);
void imprimirRelatorios(Fila *filaPA, Fila *filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);
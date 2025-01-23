#include "Fila.h"
#include "Pilha.h"
void inserirPacoteManual(Fila *filaPA, Fila *filaPB);
void inserirPacoteAutomatico(Fila *filaPA, Fila *filaPB, const char *nomeArquivo);
void validarFila(Fila *fila, char tipoEsperado);
void encherPacotes(Fila *filaInicial, Fila *filaEmbalamento, int tempoEnchimento);
Fila *embalarPacotes(Fila *filaEmbalamento, int limite, int tempoProcessamento);
void empilharEmbalagem(Pilha *pilha, Fila *fila);
void imprimirRelatorios(Fila *filaPA, Fila *filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);

#include "Fila.h"

// Menus e op��es
void inserirPacoteManual(Fila * filaPA, Fila * filaPB);
void inserirPacoteAutomatico(Fila * filaPA, Fila * filaPB, const char * nomeArquivo);
void validarFila(Fila * fila, char tipoEsperado);
void processarFilaEnchimento(Fila * filaEnchimento, Fila * filaEmbalamento, int limiteGrupo);
void imprimirRelatorios(Fila * filaPA, Fila * filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);

// Fun��es auxiliares
Pacote criarPacote(char tipo, float peso);
int validarPacote(Pacote pacote, char tipoEsperado);

#include "Fila.h"

// Menus e opções
void inserirPacoteManual(Fila * filaPA, Fila * filaPB);
void validarFila(Fila * fila, char tipoEsperado);
void processarFilaEnchimento(Fila * filaEnchimento, Fila * filaEmbalamento, int limiteGrupo);
void imprimirRelatorios(Fila * filaPA, Fila * filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);

// Funções auxiliares
Pacote criarPacote(char tipo, float peso);
int validarPacote(Pacote pacote, char tipoEsperado);

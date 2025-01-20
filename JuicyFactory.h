#include "Fila.h"
<<<<<<< HEAD
void inserirPacoteManual(Fila *filaPA, Fila *filaPB);
void inserirPacoteAutomatico(Fila *filaPA, Fila *filaPB, const char *nomeArquivo);
void validarFila(Fila *fila, char tipoEsperado);
void processarFilaEnchimento(Fila *filaEnchimento, Fila *filaEmbalamento, int limiteGrupo);
void imprimirRelatorios(Fila *filaPA, Fila *filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);
=======

// Menus e opcoes
void inserirPacoteManual(Fila * filaPA, Fila * filaPB);
void inserirPacoteAutomatico(Fila * filaPA, Fila * filaPB, const char * nomeArquivo);
void validarFila(Fila * fila, char tipoEsperado);
void processarFilaEnchimento(Fila * filaEnchimento, Fila * filaEmbalamento, int limiteGrupo);
void imprimirRelatorios(Fila * filaPA, Fila * filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);

// Fun��es auxiliares
Pacote criarPacote(char tipo, float peso);
int validarPacote(Pacote pacote, char tipoEsperado);
>>>>>>> a53313eae0fa86af99ed01928c152b82480ab18c

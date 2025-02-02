#include "Pilha.h"
typedef struct maquina Maquina;

Maquina *criarMaquina(char *nome, char *tipo, float tempoProcessamento, int capacidade);
Pacote criarPacote(char *tipo, float peso);
int validarPacote(Pacote pacote);
void inserirPacoteManual(Fila *filaPA, Fila *filaPB);
void inserirPacoteAutomatico(Fila *filaPA, Fila *filaPB, const char *nomeArquivo);
void encherPacotes(Maquina *maquinaEnchimento, Fila *filaEnchimento, Fila *filaEmbalamento);
void validarProdutosFilaEmbalamento(Fila *filaEmbalamento, int *prejuizo);
void encaminhar(Fila *filaEmbalamento, Maquina *maquina);
void embalarEEmpilharPacotes(Maquina *maquinaEmbalamento, Pilha *pilhaEmbalagem);
void destruirMaquina(Maquina *maquina);
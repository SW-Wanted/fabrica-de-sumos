typedef struct pacote Pacote;
typedef struct no No;
typedef struct fila Fila;

Fila * criarFila();
void enfileirar(Fila * fila, Pacote pacote);
Pacote desenfileirar(Fila* fila);
int filaVazia(Fila * fila);
void destruirFila(Fila* fila);
void imprimirFila(Fila* fila);


// Funções auxiliares
Pacote criarPacote(char tipo, float peso);
int validarPacote(Pacote pacote, char tipoEsperado);

// Menus e opções
void menu(Fila* filaPA, Fila* filaPB);
void inserirPacoteManual(Fila* filaPA, Fila* filaPB);
void validarFila(Fila* fila, char tipoEsperado);
void processarFilaEnchimento(Fila* filaEnchimento, Fila* filaEmbalamento);
void imprimirRelatorios(Fila* filaPA, Fila* filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB);

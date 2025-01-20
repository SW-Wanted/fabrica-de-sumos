typedef struct pacote Pacote;
typedef struct no Lista;
typedef struct fila Fila;

Fila * criarFila();
void enfileirar(Fila * fila, Pacote pacote);
Pacote desenfileirar(Fila * fila);
int filaVazia(Fila * fila);
void destruirFila(Fila * fila);
void imprimirFila(Fila * fila);


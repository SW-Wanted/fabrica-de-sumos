#include <stdio.h>
#include <stdlib.h>
#include "JuicyFactory.h"

struct pacote{
    char tipo;
    float peso;
    int valido;
};

struct no {
    Pacote pacote;
    struct no * prox;
};

struct fila {
    struct no * inicio;
    struct no * fim;
    int tamanho;
};

Fila * criarFila() {
    Fila * fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void enfileirar(Fila * fila, Pacote pacote) {
    No* novo = (No*)malloc(sizeof(No));
    novo->pacote = pacote;
    novo->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

Pacote desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia. Não é possível desenfileirar.\n");
        exit(1);
    }
    No* temp = fila->inicio;
    Pacote pacote = temp->pacote;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(temp);
    fila->tamanho--;
    return pacote;
}

int filaVazia(Fila * fila) {
    return (fila->tamanho == 0) ? 1 : 0;
}

void destruirFila(Fila* fila) {
    while (!filaVazia(fila)) {
        desenfileirar(fila);
    }
    free(fila);
}

void imprimirFila(Fila* fila) {
    No * atual = fila->inicio;
    while (atual != NULL) {
        printf("Pacote [Tipo: %c, Peso: %.2f, Valido: %s]\n",
               atual->pacote.tipo,
               atual->pacote.peso,
               atual->pacote.valido ? "Sim" : "Nao");
        atual = atual->prox;
    }
}

// Funções Auxiliares
Pacote criarPacote(char tipo, float peso) {
    Pacote pacote;
    pacote.tipo = tipo;
    pacote.peso = peso;
    pacote.valido = 1;
    return pacote;
}

int validarPacote(Pacote pacote, char tipoEsperado) {
    if (pacote.tipo != tipoEsperado) return 0;
    if ((tipoEsperado == 'A' && (pacote.peso >= 50 && pacote.peso <= 100)) ||
        (tipoEsperado == 'B' && (pacote.peso >= 100 && pacote.peso <= 200))) {
        return 0;
    }
    return 1;
}

// Menu principal
void menu(Fila* filaPA, Fila* filaPB) {
    int opcao;
    int descartadosA = 0, descartadosB = 0, processadosA = 0, processadosB = 0;

    do {
        printf("\n=== Fábrica de Sumos ===\n");
        printf("1. Inserir pacote manualmente\n");
        printf("2. Validar pacotes\n");
        printf("3. Processar fila de enchimento\n");
        printf("4. Imprimir filas\n");
        printf("5. Relatórios\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirPacoteManual(filaPA, filaPB);
                break;
            case 2:
                validarFila(filaPA, 'A');
                validarFila(filaPB, 'B');
                break;
            case 3:
                processarFilaEnchimento(filaPA, filaPB);
                break;
            case 4:
                printf("\n--- Fila PA ---\n");
                imprimirFila(filaPA);
                printf("\n--- Fila PB ---\n");
                imprimirFila(filaPB);
                break;
            case 5:
                imprimirRelatorios(filaPA, filaPB, descartadosA, descartadosB, processadosA, processadosB);
                break;
            case 6:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 6);
}

// Opção 1: Inserção manual
void inserirPacoteManual(Fila* filaPA, Fila* filaPB) {
    char tipo;
    float peso;
    printf("Digite o tipo do pacote (A ou B): ");
    scanf(" %c", &tipo);
    printf("Digite o peso do pacote: ");
    scanf("%f", &peso);

    Pacote novoPacote = criarPacote(tipo, peso);
    if (tipo == 'A') {
        enfileirar(filaPA, novoPacote);
        printf("Pacote inserido na fila PA.\n");
    } else if (tipo == 'B') {
        enfileirar(filaPB, novoPacote);
        printf("Pacote inserido na fila PB.\n");
    } else {
        printf("Tipo de pacote inválido!\n");
    }
}

// Opção 2: Validação
void validarFila(Fila* fila, char tipoEsperado) {
    No * atual = fila->inicio;
    while (atual != NULL) {
        atual->pacote.valido = validarPacote(atual->pacote, tipoEsperado);
        atual = atual->prox;
    }
    printf("Fila validada para tipo %c.\n", tipoEsperado);
}

// Opção 3: Processar Fila de Enchimento (simples para demonstração)
void processarFilaEnchimento(Fila * filaEnchimento, Fila * filaEmbalamento) {
    printf("Funcionalidade em desenvolvimento.\n");
}

// Opção 5: Relatórios
void imprimirRelatorios(Fila* filaPA, Fila* filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB) {
    printf("\n=== Relatórios ===\n");
    printf("PA Processados: %d\n", processadosA);
    printf("PB Processados: %d\n", processadosB);
    printf("PA Descartados: %d\n", descartadosA);
    printf("PB Descartados: %d\n", descartadosB);
    printf("Lucro e prejuízo: Em desenvolvimento\n");
}

#include <stdio.h>
#include <stdlib.h>

#include "Fila.h"
#include "Pilha.h"
#include "JuicyFactory.h"

// Fun��es Auxiliares
Pacote criarPacote(char tipo, float peso)
{
    Pacote pacote = {tipo, peso, 1};
    return pacote;
}

int validarPacote(Pacote pacote, char tipoEsperado)
{
    if (pacote.tipo != tipoEsperado)
        return 0;
    if ((tipoEsperado == 'A' && (pacote.peso >= 198 && pacote.peso <= 202)) ||
        (tipoEsperado == 'B' && (pacote.peso >= 990 && pacote.peso <= 1020)))
        return 1;

    return 0;
}

// Op��o 1: Inser��o manual
void inserirPacoteManual(Fila *filaPA, Fila *filaPB)
{
    char tipo;
    float peso;

    printf("Tipo de pacote (A | B): ");
    scanf(" %c", &tipo);

    printf("Peso do pacote:\nA: [198 - 202]\nB: [990 - 1020] ");
    scanf("%f", &peso);

    Pacote novoPacote = criarPacote(tipo, peso);

    if (tipo == 'A')
    {
        enfileirar(filaPA, novoPacote);
        printf("Pacote inserido na fila PA.\n");
    }
    else if (tipo == 'B')
    {
        enfileirar(filaPB, novoPacote);
        printf("Pacote inserido na fila PB.\n");
    }
    else
    {
        printf("Tipo de pacote inv�lido!\n");
        // TODO: Adicionar uma vari�vel contadora de preju�zos
    }
}

// Nova função: Inserção automática
void inserirPacoteAutomatico(Fila *filaPA, Fila *filaPB, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char tipo;
    float peso;
    while (fscanf(arquivo, " %c %f", &tipo, &peso) == 2)
    {
        Pacote novoPacote = criarPacote(tipo, peso);
        if (tipo == 'A')
        {
            enfileirar(filaPA, novoPacote);
        }
        else if (tipo == 'B')
        {
            enfileirar(filaPB, novoPacote);
        }
        else
        {
            printf("Tipo de pacote inválido no arquivo!\n");
        }
    }

    fclose(arquivo);
    printf("Pacotes inseridos automaticamente a partir do arquivo %s.\n", nomeArquivo);
}

// Op��o 2: Valida��o
void validarFila(Fila *fila, char tipoEsperado)
{
    Lista *atual = fila->inicio;
    while (atual != NULL)
    {
        atual->pacote.valido = validarPacote(atual->pacote, tipoEsperado);
        atual = atual->prox;
    }
    printf("Fila validada para tipo %c.\n", tipoEsperado);
}

// Op��o 3: Processar Fila de Enchimento (simples para demonstra��o)
void processarFilaEnchimento(Fila *filaEnchimento, Fila *filaEmbalamento, int limiteGrupo)
{
    int i;

    if (filaEnchimento->tamanho < limiteGrupo)
    {
        printf("Nao ha pacotes suficientes para processar.\n");
        return;
    }

    printf("Processando grupo de %d pacotes.\n", limiteGrupo);
    for (i = 0; i < limiteGrupo; i++)
    {
        Pacote pacote = desenfileirar(filaEnchimento);
        enfileirar(filaEmbalamento, pacote);
    }

    printf("Grupo de pacotes movido para fila de embalamento.\n");
}

void encherPacotes(Fila *filaInicial, Fila *filaEmbalamento, int tempoEnchimento)
{
    while (filaInicial->tamanho > 0)
    {
        Pacote pacote = desenfileirar(filaInicial);
        printf("Enchendo pacote do tipo %c com peso %.2f...\n", pacote.tipo, pacote.peso);
        Sleep(tempoEnchimento * 1000); // Simula o tempo de enchimento em segundos
        enfileirar(filaEmbalamento, pacote);
        printf("Pacote do tipo %c com peso %.2f foi enchido e movido para a fila de embalamento.\n", pacote.tipo, pacote.peso);
    }
}

// Op��o 4: Imprimir filas
void imprimirRelatorios(Fila *filaPA, Fila *filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB)
{
    FILE *relatorio = fopen("relatorio.txt", "w");
    if (relatorio == NULL)
    {
        printf("Erro ao criar o arquivo de relatório.\n");
        return;
    }

    float lucroA = processadosA * 1.5;    // Exemplo de cálculo de lucro
    float lucroB = processadosB * 2.0;    // Exemplo de cálculo de lucro
    float prejuizoA = descartadosA * 0.5; // Exemplo de cálculo de prejuízo
    float prejuizoB = descartadosB * 1.0; // Exemplo de cálculo de prejuízo

    fprintf(relatorio, "Quantidade de produto embalado:\n");
    fprintf(relatorio, "Tipo A: %d\n", processadosA);
    fprintf(relatorio, "Tipo B: %d\n", processadosB);
    fprintf(relatorio, "Total: %d\n", processadosA + processadosB);

    fprintf(relatorio, "Quantidade de produto descartado:\n");
    fprintf(relatorio, "Tipo A: %d\n", descartadosA);
    fprintf(relatorio, "Tipo B: %d\n", descartadosB);
    fprintf(relatorio, "Total: %d\n", descartadosA + descartadosB);

    fprintf(relatorio, "Lucro previsto:\n");
    fprintf(relatorio, "Tipo A: %.2f\n", lucroA);
    fprintf(relatorio, "Tipo B: %.2f\n", lucroB);

    fprintf(relatorio, "Prejuízo:\n");
    fprintf(relatorio, "Tipo A: %.2f\n", prejuizoA);
    fprintf(relatorio, "Tipo B: %.2f\n", prejuizoB);

    fclose(relatorio);
    printf("Relatório gerado com sucesso.\n");
}

void encaminharPacotes(Fila *filaEmbalamento, Fila *filaPA, Fila *filaPB)
{
    int countPA = 0;
    int countPB = 0;

    while (filaEmbalamento->tamanho > 0)
    {
        Pacote pacote = desenfileirar(filaEmbalamento);

        if (pacote.tipo == 'A' && countPA < 6)
        {
            enfileirar(filaPA, pacote);
            countPA++;
            printf("Pacote do tipo A encaminhado para a máquina PA.\n");
        }
        else if (pacote.tipo == 'B' && countPB < 4)
        {
            enfileirar(filaPB, pacote);
            countPB++;
            printf("Pacote do tipo B encaminhado para a máquina PB.\n");
        }
        else
        {
            printf("Limite de pacotes atingido para o tipo %c.\n", pacote.tipo);
            enfileirar(filaEmbalamento, pacote); // Reenfileira o pacote se o limite for atingido
            break;
        }
    }
}

// Adicionar a funcionalidade de embalar e empilhar pacotes

void embalarEmpilhar(Fila *filaPA, Fila *filaPB, Pilha *pilhaPA, Pilha *pilhaPB)
{
    int limiteA = 6;
    int limiteB = 4;

    if (filaPA->tamanho >= limiteA)
    {
        printf("Embalando %d pacotes do tipo A...\n", limiteA);
        for (int i = 0; i < limiteA; i++)
        {
            Pacote pacote = desenfileirar(filaPA);
            empilharPacote(pilhaPA, pacote);
        }
    }
    else
    {
        printf("Não há pacotes suficientes do tipo A para embalar.\n");
    }

    if (filaPB->tamanho >= limiteB)
    {
        printf("Embalando %d pacotes do tipo B...\n", limiteB);
        for (int i = 0; i < limiteB; i++)
        {
            Pacote pacote = desenfileirar(filaPB);
            empilharPacote(pilhaPB, pacote);
        }
    }
    else
    {
        printf("Não há pacotes suficientes do tipo B para embalar.\n");
    }
}

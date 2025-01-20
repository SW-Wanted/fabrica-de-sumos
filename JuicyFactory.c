#include <stdio.h>
#include <stdlib.h>

#include "Fila.h"
#include "JuicyFactory.h"

// Funcoes auxiliares
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

// Opcao 1: Insercao manual
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
        printf("Tipo de pacote invalido!\n");
        // TODO: Adicionar uma variavel contadora de prejuizos
    }
}

// Nova funcao: Insercao automatica
void inserirPacoteAutomatico(Fila *filaPA, Fila *filaPB, const char *nomeArquivo)
{
    FILE *arquivo;
    do
    {
        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL)
        {
            char opcao;
            printf("Erro ao abrir o arquivo '%s'. Deseja tentar novamente? (S/N): ", nomeArquivo);
            scanf(" %c", &opcao);
            if (opcao == 'N' || opcao == 'n')
            {
                printf("Operacao cancelada pelo usuario.\n");
                return;
            }
            printf("Tente novamente: ");
            scanf("%s", nomeArquivo);
        }
    } while (arquivo == NULL);

    char tipo;
    float peso;
    while (fscanf(arquivo, " %c %f", &tipo, &peso) == 2)
    {
        if (validarPacote(criarPacote(tipo, peso), tipo))
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
            printf("Pacote do tipo %c com peso %.2f inserido automaticamente a partir do arquivo %s.\n", tipo, peso, nomeArquivo);
        }
        else
        {
            printf("Formato invalido no arquivo! Tipo: %c, Peso: %.2f\n", tipo, peso);
        }
    }

    fclose(arquivo);
}

// Opcao 2: Validacao
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

// Opcao 3: Processar Fila de Enchimento (simples para demonstracao)
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

// Opcao 4: Imprimir filas
void imprimirRelatorios(Fila *filaPA, Fila *filaPB, int descartadosA, int descartadosB, int processadosA, int processadosB)
{
    FILE *relatorio = fopen("relatorio.txt", "w");
    if (relatorio == NULL)
    {
        printf("Erro ao criar o arquivo de relatorio.\n");
        return;
    }

    float lucroA = processadosA * 1.5;    // Exemplo de calculo de lucro
    float lucroB = processadosB * 2.0;    // Exemplo de calculo de lucro
    float prejuizoA = descartadosA * 0.5; // Exemplo de calculo de prejuizo
    float prejuizoB = descartadosB * 1.0; // Exemplo de calculo de prejuizo

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

    fprintf(relatorio, "Prejuizo:\n");
    fprintf(relatorio, "Tipo A: %.2f\n", prejuizoA);
    fprintf(relatorio, "Tipo B: %.2f\n", prejuizoB);

    fclose(relatorio);
    printf("Relatorio gerado com sucesso.\n");
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
            printf("Pacote do tipo A encaminhado para a maquina PA.\n");
        }
        else if (pacote.tipo == 'B' && countPB < 4)
        {
            enfileirar(filaPB, pacote);
            countPB++;
            printf("Pacote do tipo B encaminhado para a maquina PB.\n");
        }
        else
        {
            printf("Limite de pacotes atingido para o tipo %c.\n", pacote.tipo);
            enfileirar(filaEmbalamento, pacote); // Reenfileira o pacote se o limite for atingido
            break;
        }
    }
}
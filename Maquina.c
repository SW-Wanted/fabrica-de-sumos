#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Maquina.h"

static int pacoteID = 1;

struct maquina
{
    char nome[50];
    char tipo[20];
    int tempoProcessamento;
    int unidadesProcessadas;
    int produtosAtuais;
    int capacidade;
    Fila *filaProcessamento;
};

Maquina *criarMaquina(char *nome, char *tipo, int tempoProcessamento, int capacidade)
{
    Maquina *maquina = (Maquina *)malloc(sizeof(Maquina));
    strcpy(maquina->nome, nome);
    strcpy(maquina->tipo, tipo);
    maquina->tempoProcessamento = tempoProcessamento;
    maquina->unidadesProcessadas = 0;
    maquina->produtosAtuais = 0;
    maquina->capacidade = capacidade;
    maquina->filaProcessamento = criarFila();
    return maquina;
}

// Funcoes auxiliares
Pacote criarPacote(char *tipo, float peso)
{
    Pacote pacote;
    pacote.id = rand();
    strcpy(pacote.tipo, tipo);
    pacote.peso = peso;
    pacote.valido = 0;
    pacote.cheio = 0;
    return pacote;
}

int validarPacote(Pacote pacote, char *tipoEsperado)
{
    printf("Pacote [Tipo: %s, Peso: %.2f]\n", pacote.tipo, pacote.peso);
    if (strcmp(pacote.tipo, tipoEsperado) != 0)
        return 0;

    if ((strcmp(tipoEsperado, "PA") == 0 && pacote.peso == 200) ||
        (strcmp(tipoEsperado, "PB") == 0 && pacote.peso == 1000))
        return 1;

    return 0;
}

// Opcao 1: Insercao manual
void inserirPacoteManual(Fila *filaPA, Fila *filaPB)
{
    char tipo[3];
    float peso;

    printf("Tipo de pacote\n");
    printf("PA - 200 ml\nPB - 1000 ml\n");
    printf("> ");
    scanf(" %s", &tipo);

    if (strcmp(tipo, "PA") == 0)
    {
        peso = 200;
        Pacote novoPacote = criarPacote("PA", peso);
        enfileirar(filaPA, novoPacote);
        printf("Pacote inserido na fila PA.\n");
    }
    else if (strcmp(tipo, "PB") == 0)
    {
        peso = 1000;
        Pacote novoPacote = criarPacote("PB", peso);
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
            printf("> ");
            scanf(" %s", &opcao);
            if (opcao == 'N' || opcao == 'n')
            {
                printf("Operacao cancelada pelo usuario.\n");
                return;
            }
            printf("Tente novamente: ");
            scanf("%s", nomeArquivo);
        }
    } while (arquivo == NULL);

    char tipo[3];
    float peso;
    while (fscanf(arquivo, "%s %f", tipo, &peso) == 2)
    {
        if (validarPacote(criarPacote(tipo, peso), tipo))
        {
            Pacote novoPacote = criarPacote(tipo, peso);
            if (strcmp(tipo, "PA") == 0)
            {
                enfileirar(filaPA, novoPacote);
            }
            else if (strcmp(tipo, "PB") == 0)
            {
                enfileirar(filaPB, novoPacote);
            }
            printf("Pacote do tipo %s com peso %.2f inserido automaticamente a partir do arquivo %s.\n", tipo, peso, nomeArquivo);
        }
        else
        {
            printf("Formato invalido no arquivo! Tipo: %s, Peso: %.2f\n", tipo, peso);
        }
    }

    fclose(arquivo);
}

void encherPacotes(Maquina *maquina, Fila *filaEnchimento, Fila *filaEmbalamento)
{
    if (filaEnchimento == NULL)
    {
        printf("Nao ha pacotes para encher.\n");
        return;
    }
    while (!filaVazia(filaEnchimento))
    {
        enfileirar(maquina->filaProcessamento, desenfileirar(filaEnchimento));
        maquina->produtosAtuais++;
        maquina->unidadesProcessadas++;
        printf("Enchendo pacote...\n");
        Sleep(maquina->tempoProcessamento * 1000); // Simula o tempo de enchimento em segundos
        Pacote pacote = desenfileirar(maquina->filaProcessamento);
        pacote.cheio = 1;
        enfileirar(filaEmbalamento, pacote);
        maquina->produtosAtuais--;
        printf("Pacote do tipo %s com peso %.2f foi enchido e movido para a fila de embalamento.\n", pacote.tipo, pacote.peso);
    }
}

void validarPacotes(Fila *filaEmbalamento, int *prejuizo)
{
    if (filaVazia(filaEmbalamento))
    {
        printf("Nao ha pacotes na Fila de Embalamento para validar.\n");
        return;
    }
    Lista *atual = filaEmbalamento->inicio;
    while (atual != NULL)
    {
        Pacote pacote = atual->pacote;
        printf("Validando pacotes...\n");
        if (validarPacote(pacote, pacote.tipo) && pacote.cheio)
        {
            pacote.valido = 1;
            printf("Pacote do tipo %s com peso %.2f foi validado.\n", pacote.tipo, pacote.peso);
        }
        else
        {
            (*prejuizo)++;
            printf("Pacote do tipo %s com peso %.2f foi removido por estar fora do padrao.\n", pacote.tipo, pacote.peso);
            desenfileirar(filaEmbalamento);
        }
        atual = atual->prox;
    }
}

void encaminhar(Fila *filaEmbalamento, Maquina *maquina)
{
    if (filaVazia(filaEmbalamento))
    {
        printf("Nao ha pacotes para encaminhar para a %s.\n", maquina->nome);
        return;
    }

    while (!filaVazia(filaEmbalamento))
    {
        if (maquina->produtosAtuais >= maquina->capacidade)
        {
            printf("A %s esta cheia.\n", maquina->nome);
            break;
        }
        Pacote pacote = desenfileirar(filaEmbalamento);
        if (strcmp(pacote.tipo, "PA") == 0 && maquina->produtosAtuais < 6)
        {
            enfileirar(maquina->filaProcessamento, pacote);
            maquina->produtosAtuais++;
            printf("Pacote do tipo %s com peso %.2f foi encaminhado para a %s.\n", pacote.tipo, pacote.peso, maquina->nome);
        }
        else if (strcmp(pacote.tipo, "PB") == 0 && maquina->produtosAtuais < 4)
        {
            enfileirar(maquina->filaProcessamento, pacote);
            maquina->produtosAtuais++;
            printf("Pacote do tipo %s com peso %.2f foi encaminhado para a %s.\n", pacote.tipo, pacote.peso, maquina->nome);
        }
        else
        {
            enfileirar(filaEmbalamento, pacote); // Reenfileira o pacote se não puder ser encaminhado
            break;
        }
    }
}

void empilharEmbalagem(Pilha *pilha, Fila *embalagens)
{
    if (embalagens == NULL)
    {
        printf("Nao ha embalagens para empilhar.\n");
        return;
    }
    printf("Empilhando embalagens...\n");
    empilhar(pilha, embalagens);
}

void embalarPacotes(Maquina *maquinaEmbalamento, Pilha *pilhaEmbalagem, int limite, int tempoProcessamento)
{
    if (maquinaEmbalamento->produtosAtuais < limite)
    {
        printf("Nao ha pacotes suficientes para embalar (%d/%d).\n", maquinaEmbalamento->produtosAtuais, limite);
        return;
    }
    Fila *embalagem = criarFila();
    int pacotesEmbalados = 0;
    while (pacotesEmbalados < limite && maquinaEmbalamento->produtosAtuais > 0)
    {
        Pacote pacote = desenfileirar(maquinaEmbalamento->filaProcessamento);
        maquinaEmbalamento->produtosAtuais--;
        enfileirar(embalagem, pacote);
        printf("Embalando pacote do tipo %s com peso %.2f...\n", pacote.tipo, pacote.peso);
        Sleep(tempoProcessamento * 1000); // Simula o tempo de embalamento em segundos
        pacotesEmbalados++;
    }
    empilharEmbalagem(pilhaEmbalagem, embalagem);
}

void destruirMaquina(Maquina *maquina)
{
    if (maquina != NULL)
    {
        destruirFila(maquina->filaProcessamento);
        free(maquina);
    }
}

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
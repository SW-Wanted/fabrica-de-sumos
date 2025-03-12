#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Fila.h"
#include "Maquina.h"

// Estrutura de uma maquina
struct maquina
{
    char nome[50];
    char tipo[20];
    float tempoProcessamento;
    int unidadesProcessadasPorDia;
    int capacidade;
    Fila *filaProcessamento;
};

// Cria uma nova maquina
Maquina *criarMaquina(char *nome, char *tipo, float tempoProcessamento, int capacidade)
{
    Maquina *maquina = (Maquina *)malloc(sizeof(Maquina));
    strcpy(maquina->nome, nome);
    strcpy(maquina->tipo, tipo);
    maquina->tempoProcessamento = tempoProcessamento;
    maquina->unidadesProcessadasPorDia = 0;
    maquina->capacidade = capacidade;
    maquina->filaProcessamento = criarFila();
    return maquina;
}

// Criar um novo pacote
Pacote criarPacote(char *tipo, float peso)
{
    Pacote pacote;
    pacote.id = rand() % 1000 + 1; // Gera um ID aleatório entre 1 e 1000
    strcpy(pacote.tipo, tipo);
    pacote.peso = peso;
    pacote.valido = 0;
    pacote.cheio = 0;
    return pacote;
}

// Funcao auxiliar para validar um pacote
int validarPacote(Pacote pacote)
{
    if ((strcmp(pacote.tipo, "PA") == 0 && pacote.peso == 200) ||
        (strcmp(pacote.tipo, "PB") == 0 && pacote.peso == 1000))
        return 1;

    return 0;
}

// Insere um pacote manualmente para a fila de enchimento
void inserirPacoteManual(Fila *filaEnchimentoPA, Fila *filaEnchimentoPB)
{
    char tipo[3];
    float peso;

    printf("Tipo de pacote\n");
    printf("PA - 200 ml\nPB - 1000 ml\n");
    printf("> ");
    scanf(" %s", &tipo);
    strupr(tipo);

    if (strcmp(tipo, "PA") == 0)
    {
        printf("Peso (ml)\n");
        printf("> ");
        scanf(" %f", &peso);
        Pacote novoPacote = criarPacote("PA", peso);
        enfileirar(filaEnchimentoPA, novoPacote);
        printf("Pacote inserido na fila de enchimento PA.\n");
    }
    else if (strcmp(tipo, "PB") == 0)
    {
        printf("Peso (ml)\n");
        printf("> ");
        scanf(" %f", &peso);
        Pacote novoPacote = criarPacote("PB", peso);
        enfileirar(filaEnchimentoPB, novoPacote);
        printf("Pacote inserido na fila de enchimento PB.\n");
    }
    else
        printf("O pacote do tipo %s nao eh reconhecido! Portanto, nao podera ser inserido em nenhuma fila.\n", tipo, peso);
}

// Insere pacotes automaticamente para a fila de enchimento
void inserirPacoteAutomatico(Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, const char *nomeArquivo)
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
            printf("Digite o nome do arquivo: ");
            scanf("%s", nomeArquivo);
        }
    } while (arquivo == NULL);

    char tipo[3];
    float peso;
    while (fscanf(arquivo, "%s %f", tipo, &peso) == 2)
    {
        strupr(tipo);
        Pacote novoPacote = criarPacote(tipo, peso);
        if (strcmp(tipo, "PA") == 0)
        {
            enfileirar(filaEnchimentoPA, novoPacote);
            printf("Pacote do tipo %s com peso %.2f inserido automaticamente a partir do arquivo %s.\n", tipo, peso, nomeArquivo);
        }
        else if (strcmp(tipo, "PB") == 0)
        {
            enfileirar(filaEnchimentoPB, novoPacote);
            printf("Pacote do tipo %s com peso %.2f inserido automaticamente a partir do arquivo %s.\n", tipo, peso, nomeArquivo);
        }
        else
            printf("O pacote do tipo %s nao eh reconhecido! Portanto, nao podera ser inserido em nenhuma fila.\n", tipo, peso);
    }

    fclose(arquivo);
}

// Enche os pacotes da fila de enchimento e move para a fila de embalamento
void encherPacotes(Maquina *maquinaEnchimento, Fila *filaEnchimento, Fila *filaEmbalamento)
{
    if (filaVazia(filaEnchimento))
    {
        printf("Nao ha pacotes na fila de Enchimento!\n");
        return;
    }
    printf("Enchendo pacotes...\n");
    while (!filaVazia(filaEnchimento))
    {
        enfileirar(maquinaEnchimento->filaProcessamento, desenfileirar(filaEnchimento));
        Sleep(maquinaEnchimento->tempoProcessamento * 1000);
        Pacote pacote = desenfileirar(maquinaEnchimento->filaProcessamento);
        maquinaEnchimento->unidadesProcessadasPorDia++;
        pacote.cheio = 1;
        enfileirar(filaEmbalamento, pacote);
        printf("Pacote do tipo %s com peso %.2f foi enchido e movido para a fila de embalamento.\n", pacote.tipo, pacote.peso);
    }
}

// Valida os pacotes da fila de embalamento e remove os pacotes defeituosos
void validarProdutosFilaEmbalamento(Fila *filaEmbalamento, int *prejuizo)
{
    if (filaVazia(filaEmbalamento))
    {
        printf("Nao ha pacotes na Fila de Embalamento para validar.\n");
        return;
    }

    Lista *atual = filaEmbalamento->inicio;
    printf("Validando pacotes...\n");
    while (atual != NULL)
    {
        Pacote *pacote = &atual->pacote;
        if (pacote->valido)
        {
            printf("Pacote do tipo %s com peso %.2f ja foi validado anteriormente.\n", pacote->tipo, pacote->peso);
        }
        else if (validarPacote(*pacote) && pacote->cheio)
        {
            pacote->valido = 1;
            printf("Pacote do tipo %s com peso %.2f foi validado.\n", pacote->tipo, pacote->peso);
        }
        else
        {
            desenfileirarPacote(filaEmbalamento, *pacote);
            (*prejuizo)++;
            printf("Pacote do tipo %s com peso %.2f foi removido da fila de embalamento por estar fora do padrao.\n", pacote->tipo, pacote->peso);
        }
        atual = atual->prox;
    }
}

// Encaminha os pacotes da fila de embalamento para a maquina de embalamento
void encaminhar(Fila *filaEmbalamento, Maquina *maquinaEmbalamento)
{
    if (filaVazia(filaEmbalamento))
    {
        printf("Nao ha pacotes para encaminhar para a %s.\n", maquinaEmbalamento->nome);
        return;
    }

    if (!filaEmbalamento->fim->pacote.valido)
    {
        printf("Existem pacotes nao validados na fila de embalamento. Valide os pacotes antes de encaminhar para %s.\n", maquinaEmbalamento->nome);
        return;
    }

    if (maquinaEmbalamento->filaProcessamento->unidades >= maquinaEmbalamento->capacidade)
    {
        printf("A %s atingiu o limite de %d pacotes. Esvazie-a para voltar a utilizar.\n", maquinaEmbalamento->nome, maquinaEmbalamento->capacidade);
        return;
    }

    while (!filaVazia(filaEmbalamento) && maquinaEmbalamento->filaProcessamento->unidades < maquinaEmbalamento->capacidade)
    {
        Pacote pacote = desenfileirar(filaEmbalamento);
        enfileirar(maquinaEmbalamento->filaProcessamento, pacote);
        maquinaEmbalamento->unidadesProcessadasPorDia++;
        printf("Pacote do tipo %s com peso %.2f foi encaminhado para a %s.\n", pacote.tipo, pacote.peso, maquinaEmbalamento->nome);
        if (maquinaEmbalamento->filaProcessamento->unidades >= maquinaEmbalamento->capacidade)
        {
            printf("A %s atingiu o limite de %d pacotes.\n", maquinaEmbalamento->nome, maquinaEmbalamento->capacidade);
            break;
        }
    }
}

// Embala e empilha os pacotes da maquina de embalamento
void embalarEEmpilharPacotes(Maquina *maquinaEmbalamento, Pilha *pilhaEmbalagem)
{
    if (maquinaEmbalamento->filaProcessamento->unidades < maquinaEmbalamento->capacidade)
    {
        printf("Nao ha pacotes suficientes na %s (%d/%d).\n", maquinaEmbalamento->nome, maquinaEmbalamento->filaProcessamento->unidades, maquinaEmbalamento->capacidade);
        return;
    }
    if (pilhaEmbalagem == NULL)
    {
        printf("Nao existe uma pilha de embalagem.\n");
        return;
    }
    Fila *embalagens = criarFila();
    int pacotesEmbalados = 0;
    printf("Embalando pacotes...\n");
    while (pacotesEmbalados < maquinaEmbalamento->capacidade && maquinaEmbalamento->filaProcessamento->unidades > 0)
    {
        Pacote pacote = desenfileirar(maquinaEmbalamento->filaProcessamento);
        enfileirar(embalagens, pacote);
        maquinaEmbalamento->unidadesProcessadasPorDia++;
        Sleep(maquinaEmbalamento->tempoProcessamento * 1000);
        printf("Pacote do tipo %s com peso %.2f foi adicionado a embalagem.\n", pacote.tipo, pacote.peso);
        pacotesEmbalados++;
    }
    printf("Os %d Pacotes foram embalados com sucesso!\n", pacotesEmbalados);
    if (embalagens == NULL)
    {
        printf("Nao ha embalagem para empilhar.\n");
        return;
    }
    printf("Empilhando a embalagem...\n");
    Sleep(500);
    empilhar(pilhaEmbalagem, embalagens);
}

// Destroi uma maquina
void destruirMaquina(Maquina *maquina)
{
    if (maquina != NULL)
    {
        destruirFila(maquina->filaProcessamento);
        free(maquina);
    }
}
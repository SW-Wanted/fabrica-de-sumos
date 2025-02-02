#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "Fila.h"
#include "Fila.c"
#include "Maquina.h"
#include "Maquina.c"
#include "Pilha.h"
#include "Pilha.c"

// Definir coloração do texto
void definirCor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Permite ao usuario ler a mensagem antes de limpar a tela
void pressioneEnter(char opcao[2])
{
    if (strcmp(opcao, "7") != 0)
    {
        printf("\nPressione Enter para continuar...\n");

        getchar(); // Le o '\n' pendente do scanf.
        while (getchar() != '\n')
            ; // Garante que o buffer esta limpo.
        system("cls");
    }
}

// Apresenta o menu principal e destaca a opcao selecionada
void menuPrincipal(int selectedOption)
{
    definirCor(14); // Amarelo
    printf("\n%*s\n", 66, "|--------------------------------------------------------------------|");
    printf("%*s\n", 66, "|                        Fabrica de Sumos                            |");
    printf("%*s\n", 66, "|--------------------------------------------------------------------|");
    definirCor(7); // Branco

    if (selectedOption == 1)
        definirCor(10); // Verde
    printf("%*s\n", 66, "| [1] Inserir Pacote                                                 |");
    definirCor(7); // Branco

    if (selectedOption == 2)
        definirCor(10); // Verde
    printf("%*s\n", 66, "| [2] Encher Pacotes                                                 |");
    definirCor(7); // Branco

    if (selectedOption == 3)
        definirCor(10); // Verde
    printf("%*s\n", 66, "| [3] Validar Produto                                                |");
    definirCor(7); // Branco

    if (selectedOption == 4)
        definirCor(10); // Verde
    printf("%*s\n", 66, "| [4] Encaminhar Pacotes para Maquina de Embalamento                 |");
    definirCor(7); // Branco

    if (selectedOption == 5)
        definirCor(10); // Verde
    printf("%*s\n", 66, "| [5] Embalar & Empilhar                                             |");
    definirCor(7); // Branco

    if (selectedOption == 6)
        definirCor(10); // Verde
    printf("%*s\n", 66, "| [6] Imprimir                                                       |");
    definirCor(7); // Branco

    if (selectedOption == 7)
        definirCor(12); // Vermelho
    printf("%*s\n", 66, "| [7] Terminar Simulacao                                             |");
    definirCor(14); // Amarelo
    printf("%*s\n", 66, "|--------------------------------------------------------------------|");
    printf("Escolha uma opcao do menu usando o seu teclado [1, 2, 3, 4, 5, 6, 7] : \n");
    definirCor(7); // Branco
}

// Inicializa as filas, máquinas e pilhas
void inicializarEstruturas(Fila **filaEnchimentoPA, Fila **filaEnchimentoPB, Maquina **maquinaEnchimentoPA, Maquina **maquinaEnchimentoPB, Fila **filaEmbalamentoPA, Fila **filaEmbalamentoPB, Maquina **maquinaEmbalamentoPA, Maquina **maquinaEmbalamentoPB, Pilha **pilhaPA, Pilha **pilhaPB)
{
    float tempoProcessamentoMaquinaEnchimentoPA = 0.3;
    float tempoProcessamentoMaquinaEnchimentoPB = 1;
    int capacidadeMaquinaEnchimentoPA = 1;
    int capacidadeMaquinaEnchimentoPB = 1;

    float tempoProcessamentoMaquinaEmbalamentoPA = 0.2;
    float tempoProcessamentoMaquinaEmbalamentoPB = 0.8;
    int capacidadeMaquinaEmbalamentoPA = 6;
    int capacidadeMaquinaEmbalamentoPB = 4;

    // Inicializa as filas de enchimento
    *filaEnchimentoPA = criarFila();
    *filaEnchimentoPB = criarFila();

    // Inicializa as máquinas de enchimento
    *maquinaEnchimentoPA = criarMaquina("Maquina de Enchimento PA", "PA", tempoProcessamentoMaquinaEnchimentoPA, capacidadeMaquinaEnchimentoPA);
    *maquinaEnchimentoPB = criarMaquina("Maquina de Enchimento PB", "PB", tempoProcessamentoMaquinaEnchimentoPB, capacidadeMaquinaEnchimentoPB);

    // Inicializa as filas de embalamento
    *filaEmbalamentoPA = criarFila();
    *filaEmbalamentoPB = criarFila();

    // Inicializa as máquinas de embalamento
    *maquinaEmbalamentoPA = criarMaquina("Maquina de Embalamento PA", "PA", tempoProcessamentoMaquinaEmbalamentoPA, capacidadeMaquinaEmbalamentoPA);
    *maquinaEmbalamentoPB = criarMaquina("Maquina de Embalamento PB", "PB", tempoProcessamentoMaquinaEmbalamentoPB, capacidadeMaquinaEmbalamentoPB);

    // Inicializa as pilhas de embalagens
    *pilhaPA = criarPilha(4);
    *pilhaPB = criarPilha(3);
}

// Menu para inserir pacotes manualmente ou automaticamente
void menuInserirPacote(Fila *filaPA, Fila *filaPB)
{
    int opcaoInsercao;
    printf("[1] Manual\n");
    printf("[2] Automatico\n");
    printf("> ");
    scanf("%d", &opcaoInsercao);

    if (opcaoInsercao == 1)
    {
        inserirPacoteManual(filaPA, filaPB);
    }
    else if (opcaoInsercao == 2)
    {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile("*.txt", &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            printf("Nenhum arquivo .txt encontrado.\n");
        }
        else
        {
            printf("Arquivos disponiveis:\n\n");
            do
            {
                printf("- %s\n", findFileData.cFileName);
            } while (FindNextFile(hFind, &findFileData) != 0);
            printf("\n");
            FindClose(hFind);

            char nomeArquivo[100];
            printf("Digite o nome do arquivo: ");
            scanf("%s", nomeArquivo);
            inserirPacoteAutomatico(filaPA, filaPB, nomeArquivo);
        }
    }
    else
    {
        printf("Opcao invalida!\n");
    }
}

// Menu para encher pacotes do tipo PA, PB ou ambos
void menuEncherPacotes(Maquina *maquinaEnchimentoA, Maquina *maquinaEnchimentoB, Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB)
{
    printf("[1] Encher pacotes do tipo PA\n");
    printf("[2] Encher pacotes do tipo PB\n");
    printf("[3] Encher todos os pacotes\n");
    printf("> ");
    int opcaoEnchimento;
    scanf("%d", &opcaoEnchimento);

    switch (opcaoEnchimento)
    {
    case 1:
        encherPacotes(maquinaEnchimentoA, filaEnchimentoPA, filaEmbalamentoPA);
        break;
    case 2:
        encherPacotes(maquinaEnchimentoA, filaEnchimentoPB, filaEmbalamentoPB);
        break;
    case 3:
        encherPacotes(maquinaEnchimentoA, filaEnchimentoPA, filaEmbalamentoPA);
        encherPacotes(maquinaEnchimentoB, filaEnchimentoPB, filaEmbalamentoPB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

// Menu para validar pacotes do tipo PA, PB ou ambos
void menuValidarProduto(Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, int *descartadosPA, int *descartadosPB)
{
    printf("[1] Validar pacotes do tipo PA\n");
    printf("[2] Validar pacotes do tipo PB\n");
    printf("[3] Validar todos os pacotes\n");
    printf("> ");
    int opcaoValidacao;
    scanf("%d", &opcaoValidacao);

    switch (opcaoValidacao)
    {
    case 1:
        validarProdutosFilaEmbalamento(filaEmbalamentoPA, descartadosPA);
        break;
    case 2:
        validarProdutosFilaEmbalamento(filaEmbalamentoPB, descartadosPB);
        break;
    case 3:
        validarProdutosFilaEmbalamento(filaEmbalamentoPA, descartadosPA);
        validarProdutosFilaEmbalamento(filaEmbalamentoPB, descartadosPB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

// Menu para encaminhar pacotes para a máquina de embalamento PA, PB ou ambas
void menuEncaminharPacotes(Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, Maquina *maquinaEmbalamentoA, Maquina *maquinaEmbalamentoB)
{
    printf("[1] Encaminhar pacotes para %s\n", maquinaEmbalamentoA->nome);
    printf("[2] Encaminhar pacotes para %s \n", maquinaEmbalamentoB->nome);
    printf("[3] Encaminhar todos os pacotes\n");
    printf("> ");
    int opcaoEncaminhamento;
    scanf("%d", &opcaoEncaminhamento);

    switch (opcaoEncaminhamento)
    {
    case 1:
        encaminhar(filaEmbalamentoPA, maquinaEmbalamentoA);
        break;
    case 2:
        encaminhar(filaEmbalamentoPB, maquinaEmbalamentoB);
        break;
    case 3:
        encaminhar(filaEmbalamentoPA, maquinaEmbalamentoA);
        encaminhar(filaEmbalamentoPB, maquinaEmbalamentoB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

// Menu para embalar pacotes do tipo PA, PB ou ambos
void menuEmbalagem(Maquina *maquinaEmbalamentoA, Maquina *maquinaEmbalamentoB, Pilha *pilhaPA, Pilha *pilhaPB)
{
    printf("[1] Embalar pacotes do tipo PA\n");
    printf("[2] Embalar pacotes do tipo PB\n");
    printf("[3] Embalar todos os pacotes\n");
    printf("> ");
    int opcaoEmbalagem;
    scanf("%d", &opcaoEmbalagem);

    switch (opcaoEmbalagem)
    {
    case 1:
        embalarEEmpilharPacotes(maquinaEmbalamentoA, pilhaPA);
        break;
    case 2:
        embalarEEmpilharPacotes(maquinaEmbalamentoB, pilhaPB);
        break;
    case 3:
        embalarEEmpilharPacotes(maquinaEmbalamentoA, pilhaPA);
        embalarEEmpilharPacotes(maquinaEmbalamentoB, pilhaPB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

// Menu para imprimir a fila de enchimento, fila de embalamento ou pilha de embalagem
void menuImprimir(Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, Pilha *PilhaEmbalagemPA, Pilha *PilhaEmbalagemPB)
{
    int opcaoImpressao;
    printf("[1] Fila de enchimento\n");
    printf("[2] Fila de embalamento\n");
    printf("[3] Pilha de embalagem\n");
    printf("> ");
    scanf("%d", &opcaoImpressao);

    switch (opcaoImpressao)
    {
    case 1:
        printf("-------------------------- FILA DE ENCHIMENTO ----------------------\n");
        printf("------------------------------- PA [%d] ---------------------------\n", filaEnchimentoPA->unidades);
        imprimirFila(filaEnchimentoPA);
        printf("------------------------------- PB [%d] ---------------------------\n", filaEnchimentoPB->unidades);
        imprimirFila(filaEnchimentoPB);
        break;
    case 2:
        printf("-------------------------- FILA DE EMBALAMENTO ---------------------\n");
        printf("------------------------------- PA [%d] ---------------------------\n", filaEmbalamentoPA->unidades);
        imprimirFila(filaEmbalamentoPA);
        printf("------------------------------- PB [%d] ---------------------------\n", filaEmbalamentoPB->unidades);
        imprimirFila(filaEmbalamentoPB);
        break;
    case 3:
        printf("-------------------------- PILHA DE EMBALAGEM ----------------------\n");
        printf("------------------------------- PA [%d] ---------------------------\n", PilhaEmbalagemPA->quantidadeEmbalagens);
        imprimirPilha(PilhaEmbalagemPA);
        printf("------------------------------- PB [%d] ---------------------------\n", PilhaEmbalagemPB->quantidadeEmbalagens);
        imprimirPilha(PilhaEmbalagemPB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

// Destroi as filas, máquinas e pilhas para liberar a memória
void destruirEstruturas(Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, Maquina *maquinaEnchimentoPA, Maquina *maquinaEnchimentoPB, Maquina *maquinaEmbalamentoPA, Maquina *maquinaEmbalamentoPB, Pilha *pilhaPA, Pilha *pilhaPB)
{
    destruirFila(filaEnchimentoPA);
    destruirFila(filaEnchimentoPB);
    destruirFila(filaEmbalamentoPA);
    destruirFila(filaEmbalamentoPB);
    destruirMaquina(maquinaEnchimentoPA);
    destruirMaquina(maquinaEnchimentoPB);
    destruirMaquina(maquinaEmbalamentoPA);
    destruirMaquina(maquinaEmbalamentoPB);
    destruirPilha(pilhaPA);
    destruirPilha(pilhaPB);
}

// Gera o relatório da simulação
void gerarRelatorio(Pilha *pilhaEmbalamentoPA, Pilha *pilhaEmbalamentoPB, int descartadosPA, int descartadosPB)
{
    FILE *ficheiro;

    int totalEmbaladoPA = pilhaEmbalamentoPA->quantidadePacotes;
    int totalEmbaladoPB = pilhaEmbalamentoPB->quantidadePacotes;
    int totalDescartadoPA = descartadosPA;
    int totalDescartadoPB = descartadosPB;
    int pacotesPerdidosTotal = totalDescartadoPA + totalDescartadoPB;

    float precoVendaPA = 1100.0;
    float custoProducaoPA = 250.0;
    float precoVendaPB = 1700.0;
    float custoProducaoPB = 220.0;

    float totalVendaPA = totalEmbaladoPA * precoVendaPA;
    float totalCustoPA = (totalEmbaladoPA + totalDescartadoPA) * custoProducaoPA;
    float lucroTotalPA = totalVendaPA - totalCustoPA > 0 ? totalVendaPA - totalCustoPA : 0;
    float prejuizoTotalPA = totalVendaPA - totalCustoPA < 0 ? totalCustoPA - totalVendaPA : 0;

    float totalVendaPB = totalEmbaladoPB * precoVendaPB;
    float totalCustoPB = (totalEmbaladoPB + totalDescartadoPB) * custoProducaoPB;
    float lucroTotalPB = totalVendaPB - totalCustoPB > 0 ? totalVendaPB - totalCustoPB : 0;
    float prejuizoTotalPB = totalVendaPB - totalCustoPB < 0 ? totalCustoPB - totalVendaPB : 0;

    // Cria a pasta "relatorios" se ela não existir
    CreateDirectory("relatorios", NULL);

    // Obtém a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char nomeFicheiro[100];
    sprintf(nomeFicheiro, "relatorios/relatorio_simulacao_%04d-%02d-%02d_%02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Abre o ficheiro para escrita
    ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL)
    {
        printf("Erro ao criar o ficheiro de relatorio!\n");
        return;
    }

    fprintf(ficheiro, "Relatorio da Simulacao\n");
    fprintf(ficheiro, "=========================\n");

    fprintf(ficheiro, "Produtos PA (200ml):\n");
    fprintf(ficheiro, " - Total embalado: %d\n", totalEmbaladoPA);
    fprintf(ficheiro, " - Total descartado: %d\n", totalDescartadoPA);
    fprintf(ficheiro, " - Total de vendas: %.2f kz\n", totalVendaPA);
    fprintf(ficheiro, " - Total de custo: %.2f kz\n", totalCustoPA);
    fprintf(ficheiro, " - Lucro total: %.2f kz\n", lucroTotalPA);
    fprintf(ficheiro, " - Prejuizo total: %.2f kz\n", prejuizoTotalPA);

    fprintf(ficheiro, "\nProdutos PB (1L):\n");
    fprintf(ficheiro, " - Total embalado: %d\n", totalEmbaladoPB);
    fprintf(ficheiro, " - Total descartado: %d\n", totalDescartadoPB);
    fprintf(ficheiro, " - Total de vendas: %.2f kz\n", totalVendaPB);
    fprintf(ficheiro, " - Total de custo: %.2f kz\n", totalCustoPB);
    fprintf(ficheiro, " - Lucro total: %.2f kz\n", lucroTotalPB);
    fprintf(ficheiro, " - Prejuizo total: %.2f kz\n", prejuizoTotalPB);

    fprintf(ficheiro, "\nResumo Geral:\n");
    fprintf(ficheiro, " - Total de produtos embalados: %d\n", totalEmbaladoPA + totalEmbaladoPB);
    fprintf(ficheiro, " - Total de produtos descartados: %d\n", totalDescartadoPA + totalDescartadoPB);
    fprintf(ficheiro, " - Pacotes perdidos total: %d\n", pacotesPerdidosTotal);
    fprintf(ficheiro, " -> Lucro geral: %.2f kz\n", lucroTotalPA + lucroTotalPB);
    fprintf(ficheiro, " -> Prejuizo geral: %.2f kz\n", prejuizoTotalPA + prejuizoTotalPB);

    fclose(ficheiro);
    printf("Relatorio da simulacao gerado com sucesso.\n");
}

int main()
{
    system("cls");

    srand(time(NULL)); // Inicializa a seed do gerador de números aleatórios

    Fila *filaEnchimentoPA, *filaEnchimentoPB, *filaEmbalamentoPA, *filaEmbalamentoPB;
    Maquina *maquinaEnchimentoPA, *maquinaEnchimentoPB, *maquinaEmbalamentoPA, *maquinaEmbalamentoPB;
    Pilha *pilhaEmbalamentoPA, *pilhaEmbalamentoPB;

    inicializarEstruturas(&filaEnchimentoPA, &filaEnchimentoPB, &maquinaEnchimentoPA, &maquinaEnchimentoPB, &filaEmbalamentoPA, &filaEmbalamentoPB, &maquinaEmbalamentoPA, &maquinaEmbalamentoPB, &pilhaEmbalamentoPA, &pilhaEmbalamentoPB);

    int descartadosPA = 0;
    int descartadosPB = 0;

    char opcao[2];

    do
    {
        menuPrincipal(0);
        printf("> ");
        scanf("%s", opcao);

        if (strcmp(opcao, "1") == 0) // Inserir pacotes
        {
            system("cls");
            menuPrincipal(1);
            menuInserirPacote(filaEnchimentoPA, filaEnchimentoPB);
        }
        else if (strcmp(opcao, "2") == 0) // Encher pacotes
        {
            system("cls");
            menuPrincipal(2);
            menuEncherPacotes(maquinaEnchimentoPA, maquinaEnchimentoPB, filaEnchimentoPA, filaEnchimentoPB, filaEmbalamentoPA, filaEmbalamentoPB);
        }
        else if (strcmp(opcao, "3") == 0) // Validar Produtos
        {
            system("cls");
            menuPrincipal(3);
            menuValidarProduto(filaEmbalamentoPA, filaEmbalamentoPB, &descartadosPA, &descartadosPB);
        }
        else if (strcmp(opcao, "4") == 0) // Encaminhar Pacotes para Maquina de Embalamento
        {
            system("cls");
            menuPrincipal(4);
            menuEncaminharPacotes(filaEmbalamentoPA, filaEmbalamentoPB, maquinaEmbalamentoPA, maquinaEmbalamentoPB);
        }
        else if (strcmp(opcao, "5") == 0) // Embalar & Empilhar
        {
            system("cls");
            menuPrincipal(5);
            menuEmbalagem(maquinaEmbalamentoPA, maquinaEmbalamentoPB, pilhaEmbalamentoPA, pilhaEmbalamentoPB);
        }
        else if (strcmp(opcao, "6") == 0) // Imprimir
        {
            system("cls");
            menuPrincipal(6);
            menuImprimir(filaEnchimentoPA, filaEnchimentoPB, filaEmbalamentoPA, filaEmbalamentoPB, pilhaEmbalamentoPA, pilhaEmbalamentoPB);
        }
        else if (strcmp(opcao, "7") == 0) // Terminar Simulação
        {
            system("cls");
            menuPrincipal(7);
            gerarRelatorio(pilhaEmbalamentoPA, pilhaEmbalamentoPB, descartadosPA, descartadosPB);
            destruirEstruturas(filaEnchimentoPA, filaEnchimentoPB, filaEmbalamentoPA, filaEmbalamentoPB, maquinaEnchimentoPA, maquinaEnchimentoPB, maquinaEmbalamentoPA, maquinaEmbalamentoPB, pilhaEmbalamentoPA, pilhaEmbalamentoPB);
            printf("Simulacao encerrada. Deseja iniciar uma nova simulacao? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                system("cls");
                inicializarEstruturas(&filaEnchimentoPA, &filaEnchimentoPB, &maquinaEnchimentoPA, &maquinaEnchimentoPB, &filaEmbalamentoPA, &filaEmbalamentoPB, &maquinaEmbalamentoPA, &maquinaEmbalamentoPB, &pilhaEmbalamentoPA, &pilhaEmbalamentoPB);
                descartadosPA = 0;
                descartadosPB = 0;
            }
            else
            {
                printf("Encerrando programa.\n");
                return 0;
            }
        }
        else
            printf("Opcao invalida!\n");

        pressioneEnter(opcao);

    } while (1);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

#include "Fila.h"
#include "Fila.c"
#include "Maquina.h"
#include "Maquina.c"
#include "Pilha.h"
#include "Pilha.c"

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void printMenu(int selectedOption)
{
    setColor(14); // Amarelo
    printf("\n%*s\n", 66, "|--------------------------------------------------------------------|");
    printf("%*s\n", 66, "|                        Fabrica de Sumos                            |");
    printf("%*s\n", 66, "|--------------------------------------------------------------------|");
    setColor(7); // Branco

    if (selectedOption == 1)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [1] Inserir Pacote                                                 |");
    setColor(7); // Branco

    if (selectedOption == 2)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [2] Encher Pacotes                                                 |");
    setColor(7); // Branco

    if (selectedOption == 3)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [3] Validar Produto                                                |");
    setColor(7); // Branco

    if (selectedOption == 4)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [4] Encaminhar Pacotes para Maquina de Embalamento                 |");
    setColor(7); // Branco

    if (selectedOption == 5)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [5] Embalar & Empilhar                                             |");
    setColor(7); // Branco

    if (selectedOption == 6)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [6] Imprimir                                                       |");
    setColor(7); // Branco

    if (selectedOption == 7)
        setColor(12); // Vermelho
    printf("%*s\n", 66, "| [7] Terminar Simulacao                                             |");
    setColor(14); // Amarelo
    printf("%*s\n", 66, "|--------------------------------------------------------------------|");
    printf("Escolha uma opcao do menu usando o seu teclado [1, 2, 3, 4, 5, 6, 7] : \n");
    setColor(7); // Branco
}

void MenuInserirPacote(Fila *filaPA, Fila *filaPB)
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
void MenuEncherPacotes(Maquina *maquinaEnchimentoA, Maquina *maquinaEnchimentoB, Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB)
{
    printf("[1] Encher pacotes do tipo A\n");
    printf("[2] Encher pacotes do tipo B\n");
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

void MenuValidarProduto(Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, int *descartadosA, int *descartadosB)
{
    printf("[1] Validar pacotes do tipo A\n");
    printf("[2] Validar pacotes do tipo B\n");
    printf("[3] Validar todos os pacotes\n");
    printf("> ");
    int opcaoValidacao;
    scanf("%d", &opcaoValidacao);

    switch (opcaoValidacao)
    {
    case 1:
        validarPacotes(filaEmbalamentoPA, descartadosA);
        break;
    case 2:
        validarPacotes(filaEmbalamentoPB, descartadosB);
        break;
    case 3:
        validarPacotes(filaEmbalamentoPA, descartadosA);
        validarPacotes(filaEmbalamentoPB, descartadosB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

void MenuEncaminharPacotes(Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, Maquina *maquinaEmbalamentoA, Maquina *maquinaEmbalamentoB)
{
    printf("[1] Encaminhar pacotes do tipo A\n");
    printf("[2] Encaminhar pacotes do tipo B\n");
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

void MenuEmbalagem(Maquina *maquinaEmbalamentoA, Maquina *maquinaEmbalamentoB, Pilha *pilhaPA, Pilha *pilhaPB)
{
    printf("[1] Embalar pacotes do tipo A\n");
    printf("[2] Embalar pacotes do tipo B\n");
    printf("[3] Embalar todos os pacotes\n");
    printf("> ");
    int opcaoEmbalagem;
    scanf("%d", &opcaoEmbalagem);

    switch (opcaoEmbalagem)
    {
    case 1:
        embalarPacotes(maquinaEmbalamentoA, pilhaPA, 6, 1);
        break;
    case 2:
        embalarPacotes(maquinaEmbalamentoB, pilhaPB, 4, 1);
        break;
    case 3:
        embalarPacotes(maquinaEmbalamentoA, pilhaPA, 6, 1);
        embalarPacotes(maquinaEmbalamentoB, pilhaPB, 4, 1);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

void imprimir(Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, Pilha *PilhaEmbalagemPA, Pilha *PilhaEmbalagemPB)
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
        printf("---------------- FILA DE ENCHIMENTO ----------------\n");
        printf("--------------------- PA [%d] ----------------------\n", filaEnchimentoPA->tamanho);
        imprimirFila(filaEnchimentoPA);
        printf("--------------------- PB [%d] ----------------------\n", filaEnchimentoPB->tamanho);
        imprimirFila(filaEnchimentoPB);
        break;
    case 2:
        printf("---------------- FILA DE EMBALAMENTO ----------------\n");
        printf("--------------------- PA [%d] ----------------------\n", filaEmbalamentoPA->tamanho);
        imprimirFila(filaEmbalamentoPA);
        printf("--------------------- PB [%d] ----------------------\n", filaEmbalamentoPB->tamanho);
        imprimirFila(filaEmbalamentoPB);
        break;
    case 3:
        printf("---------------- PILHA DE EMBALAGEM ----------------\n");
        printf("--------------------- PA [%d] ----------------------\n", PilhaEmbalagemPA->tamanho);
        imprimirPilha(PilhaEmbalagemPA);
        printf("--------------------- PB [%d] ----------------------\n", PilhaEmbalagemPB->tamanho);
        imprimirPilha(PilhaEmbalagemPB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

int main()
{
    system("cls");
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    Fila *filaEnchimentoPA = criarFila();
    Fila *filaEnchimentoPB = criarFila();
    Maquina *maquinaEnchimentoPA = criarMaquina("Maquina de Enchimento PA", "Enchimento", 1, 1);
    Maquina *maquinaEnchimentoPB = criarMaquina("Maquina de Enchimento PB", "Enchimento", 1, 1);

    Fila *filaEmbalamentoPA = criarFila();
    Fila *filaEmbalamentoPB = criarFila();
    Maquina *maquinaEmbalamentoPA = criarMaquina("Maquina de Embalamento PA", "Embalamento", 1, 6);
    Maquina *maquinaEmbalamentoPB = criarMaquina("Maquina de Embalamento PB", "Embalamento", 1, 4);

    Pilha *pilhaPA = criarPilha();
    Pilha *pilhaPB = criarPilha();

    int opcao;
    int descartadosA = 0, descartadosB = 0, processadosA = 0, processadosB = 0;

    do
    {
        printMenu(0);
        printf("> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Inserir pacaote
            system("cls");
            printMenu(1);
            MenuInserirPacote(filaEnchimentoPA, filaEnchimentoPB);
            break;
        case 2: // Encher pacotes
            system("cls");
            printMenu(2);
            MenuEncherPacotes(maquinaEnchimentoPA, maquinaEnchimentoPB, filaEnchimentoPA, filaEnchimentoPB, filaEmbalamentoPA, filaEmbalamentoPB);
            break;
        case 3: // Validar Produto
            system("cls");
            printMenu(3);
            MenuValidarProduto(filaEmbalamentoPA, filaEmbalamentoPB, &descartadosA, &descartadosB);
            break;
        case 4: // Encaminhar Pacotes para Maquina de Embalamento
            system("cls");
            printMenu(4);
            MenuEncaminharPacotes(filaEmbalamentoPA, filaEmbalamentoPB, maquinaEmbalamentoPA, maquinaEmbalamentoPB);
            break;
        case 5: // Embalar & Empilhar
            system("cls");
            printMenu(5);
            MenuEmbalagem(maquinaEmbalamentoPA, maquinaEmbalamentoPB, pilhaPA, pilhaPB);
            break;
        case 6: // Imprimir
            system("cls");
            printMenu(6);
            imprimir(filaEnchimentoPA, filaEnchimentoPB, filaEmbalamentoPA, filaEmbalamentoPB, pilhaPA, pilhaPB);
            break;
        case 7: // Terminar Simulação
            system("cls");
            printMenu(7);
            imprimirRelatorios(filaEnchimentoPA, filaEnchimentoPB, descartadosA, descartadosB, processadosA, processadosB);
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
            printf("Simulacao encerrada. Deseja iniciar uma nova simulacao? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                system("cls");
                filaEnchimentoPA = criarFila();
                filaEnchimentoPB = criarFila();
                filaEmbalamentoPA = criarFila();
                filaEmbalamentoPB = criarFila();
                pilhaPA = criarPilha();
                pilhaPB = criarPilha();
                maquinaEmbalamentoPA = criarMaquina("Maquina de Embalamento PA", "Embalamento", 1, 6);
                maquinaEmbalamentoPB = criarMaquina("Maquina de Embalamento PB", "Embalamento", 1, 4);
                maquinaEnchimentoPA = criarMaquina("Maquina de Enchimento PA", "Enchimento", 1, 1);
                maquinaEnchimentoPB = criarMaquina("Maquina de Enchimento PB", "Enchimento", 1, 1);
                descartadosA = 0;
                descartadosB = 0;
                processadosA = 0;
                processadosB = 0;
            }
            else
            {
                printf("Encerrando programa.\n");
                return 0;
            }
            break;
        default:
            printf("Opcao invalida!\n");
        }

        if (opcao != 7)
        {
            printf("\nPressione Enter para continuar...\n");

            getchar(); // Le o '\n' pendente do scanf.
            while (getchar() != '\n'); // Garante que o buffer esta limpo.
            system("cls");
        }

    } while (1);
    return 0;
}
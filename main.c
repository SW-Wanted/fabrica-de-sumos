#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#include "Fila.h"
#include "Fila.c"
#include "JuicyFactory.h"
#include "JuicyFactory.c"
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
    printf("\n%*s\n", 66, "|------------------------------------------------------------------|");
    printf("%*s\n", 66, "|                        Fabrica de Sumos                          |");
    printf("%*s\n", 66, "|------------------------------------------------------------------|");
    setColor(7); // Branco

    if (selectedOption == 1)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [1] Inserir Pacote                                               |");
    setColor(7); // Branco

    if (selectedOption == 2)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [2] Encher Pacotes                                               |");
    setColor(7); // Branco

    if (selectedOption == 3)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [3] Encaminhar Pacotes para Maquina de Embalamento               |");
    setColor(7); // Branco

    if (selectedOption == 4)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [4] Embalar & Empilhar                                           |");
    setColor(7); // Branco

    if (selectedOption == 5)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [5] Imprimir                                                     |");
    setColor(7); // Branco

    if (selectedOption == 6)
        setColor(12); // Vermelho
    printf("%*s\n", 66, "| [6] Terminar Simulacao                                           |");
    setColor(14); // Amarelo
    printf("%*s\n", 66, "|------------------------------------------------------------------|");
    printf("Escolha uma opcao do menu usando o seu teclado [1, 2, 3, 4, 5, 6] : \n");
    setColor(7); // Branco
}

void inserirPacote(Fila *filaPA, Fila *filaPB)
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

void imprimirOpcoes(Fila *filaEnchimentoPA, Fila *filaEnchimentoPB, Fila *filaEmbalamentoPA, Fila *filaEmbalamentoPB, Pilha *PilhaEmbalagemPA, Pilha *PilhaEmbalagemPB)
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
    setlocale(LC_ALL, "Portuguese");

    Fila *filaEnchimentoPA = criarFila();
    Fila *filaEnchimentoPB = criarFila();

    Fila *filaEmbalamentoPA = criarFila();
    Fila *filaEmbalamentoPB = criarFila();

    Pilha *pilhaPA = criarPilha();
    Pilha *pilhaPB = criarPilha();

    int opcao;
    int descartadosA = 0, descartadosB = 0, processadosA = 0, processadosB = 0;

    do
    {
        printMenu(0);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Inserir pacaote
            system("cls");
            printMenu(1);
            inserirPacote(filaEnchimentoPA, filaEnchimentoPB);
            break;
        case 2: // Encher pacotes
            system("cls");
            printMenu(2);
            printf("[1] Encher pacotes do tipo A\n");
            printf("[2] Encher pacotes do tipo B\n");
            printf("[3] Encher todos os pacotes\n");
            printf("> ");
            int opcaoEnchimento;
            scanf("%d", &opcaoEnchimento);

            switch (opcaoEnchimento)
            {
            case 1:
                encherPacotes(filaEnchimentoPA, filaEmbalamentoPA, 2); // Exemplo: 2 segundos para encher cada pacote
                break;
            case 2:
                encherPacotes(filaEnchimentoPB, filaEmbalamentoPB, 2); // Exemplo: 2 segundos para encher cada pacote
                break;
            case 3:
                encherPacotes(filaEnchimentoPA, filaEmbalamentoPA, 2); // Exemplo: 2 segundos para encher cada pacote
                encherPacotes(filaEnchimentoPB, filaEmbalamentoPB, 2); // Exemplo: 2 segundos para encher cada pacote
                break;
            default:
                printf("Opcao invalida!\n");
            }
            break;
        case 3: // Encaminhar Pacotes para Maquina de Embalamento
            system("cls");
            printMenu(3);
            printf("Em fase de desenvolvimento!");
            break;
        case 4: // Embalar & Empilhar
            system("cls");
            printMenu(4);
            Fila *embalagemPA = embalarPacotes(filaEmbalamentoPA, 6, 2);
            Fila *embalagemPB = embalarPacotes(filaEmbalamentoPB, 4, 2);
            empilharEmbalagem(pilhaPA, embalagemPA);
            empilharEmbalagem(pilhaPB, embalagemPB);
            break;
        case 5: // Imprimir
            system("cls");
            printMenu(5);
            imprimirOpcoes(filaEnchimentoPA, filaEnchimentoPB, filaEmbalamentoPA, filaEmbalamentoPB, pilhaPA, pilhaPB);
            break;
        case 6: // Terminar Simulação
            system("cls");
            printMenu(6);
            imprimirRelatorios(filaEnchimentoPA, filaEnchimentoPB, descartadosA, descartadosB, processadosA, processadosB);
            destruirFila(filaEnchimentoPA);
            destruirFila(filaEnchimentoPB);
            printf("Simulacao encerrada. Deseja iniciar uma nova simulacao? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                system("cls");
                filaEnchimentoPA = criarFila();
                filaEnchimentoPB = criarFila();
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

        printf("\nPressione Enter para continuar...\n");

        getchar(); // Le o '\n' pendente do scanf.
        while (getchar() != '\n')
            ; // Garante que o buffer esta limpo.

        if (opcao != 8)
        {
            system("cls");
        }

    } while (1); // Loop infinito para garantir que o programa so termina quando o usuario nao quiser mais uma simulacao
    destruirFila(filaEnchimentoPA);
    destruirFila(filaEnchimentoPB);
    return 0;
}

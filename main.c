#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#include "Fila.h"
#include "Fila.c"
#include "JuicyFactory.h"
#include "JuicyFactory.c"

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
    printf("%*s\n", 66, "| [1] Inserir pacote                                               |");
    setColor(7); // Branco

    if (selectedOption == 2)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [2] Validar pacotes                                              |");
    setColor(7); // Branco

    if (selectedOption == 3)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [3] Processar fila de enchimento                                 |");
    setColor(7); // Branco

    if (selectedOption == 4)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [4] Imprimir filas                                               |");
    setColor(7); // Branco

    if (selectedOption == 5)
        setColor(10); // Verde
    printf("%*s\n", 66, "| [5] Relatorios                                                   |");
    setColor(7); // Branco

    if (selectedOption == 6)
        setColor(12); // Vermelho
    printf("%*s\n", 66, "| [6] Sair                                                         |");
    setColor(14); // Amarelo
    printf("%*s\n", 66, "|------------------------------------------------------------------|");
    printf("Escolha uma opcao do menu usando o seu teclado [1, 2, 3, 4, 5, 6] : \n");
    setColor(7); // Branco
}

void inserirPacote(Fila *filaPA, Fila *filaPB)
{
    int opcaoInsercao;
    printf("Escolha o metodo de insercao de pacotes:\n");
    printf("[1] Manual\n");
    printf("[2] Automatico\n");
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

void imprimirOpcoes(Fila *filaPA, Fila *filaPB)
{
    int opcaoImpressao;
    printf("Escolha a fila para imprimir:\n");
    printf("[1] Fila de enchimento (PA)\n");
    printf("[2] Fila de enchimento (PB)\n");
    printf("[3] Fila de embalamento (PA)\n");
    printf("[4] Fila de embalamento (PB)\n");
    scanf("%d", &opcaoImpressao);

    switch (opcaoImpressao)
    {
    case 1:
        printf("Fila de enchimento (PA):\n");
        imprimirFila(filaPA);
        break;
    case 2:
        printf("Fila de enchimento (PB):\n");
        imprimirFila(filaPB);
        break;
    case 3:
        printf("Fila de embalamento (PA):\n");
        imprimirFila(filaPA);
        break;
    case 4:
        printf("Fila de embalamento (PB):\n");
        imprimirFila(filaPB);
        break;
    default:
        printf("Opcao invalida!\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Fila *filaPA = criarFila();
    Fila *filaPB = criarFila();

    int opcao;
    int descartadosA = 0, descartadosB = 0, processadosA = 0, processadosB = 0;

    do
    {
        printMenu(0);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            printMenu(1);
            inserirPacote(filaPA, filaPB);
            break;
        case 2:
            system("cls");
            printMenu(2);
            validarFila(filaPA, 'A');
            validarFila(filaPB, 'B');
            break;
        case 3:
            system("cls");
            printMenu(3);
            printf("Escolha a fila para processar (A ou B): ");
            char filaEscolhida;
            scanf(" %c", &filaEscolhida);
            if (filaEscolhida == 'A')
            {
                encherPacotes(filaPA, filaPB, 2); // Exemplo: 2 segundos para encher cada pacote
            }
            else if (filaEscolhida == 'B')
            {
                encherPacotes(filaPB, filaPA, 2); // Exemplo: 2 segundos para encher cada pacote
            }
            else
            {
                printf("Fila invalida!\n");
            }
            break;
        case 4:
            system("cls");
            printMenu(4);
            imprimirOpcoes(filaPA, filaPB);
            break;
        case 5:
            system("cls");
            printMenu(5);
            imprimirRelatorios(filaPA, filaPB, descartadosA, descartadosB, processadosA, processadosB);
            break;
        case 6:
            system("cls");
            printMenu(6);
            imprimirRelatorios(filaPA, filaPB, descartadosA, descartadosB, processadosA, processadosB);
            destruirFila(filaPA);
            destruirFila(filaPB);
            printf("Simulacao encerrada. Deseja iniciar uma nova simulacao? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                system("cls");
                filaPA = criarFila();
                filaPB = criarFila();
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

        if (opcao != 6)
        {
            system("cls");
        }

    } while (1); // Loop infinito para garantir que o programa so termina quando o usuario nao quiser mais uma simulacao
    destruirFila(filaPA);
    destruirFila(filaPB);
    return 0;
}

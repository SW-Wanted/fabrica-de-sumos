#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#include "Lista.h"
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

void printMenu()
{
    setColor(14); // Amarelo
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                         Fábrica de Sumos                    ║\n");
    printf("╠═════════════════════════════════════════════════════════════╣\n");
    setColor(10); // Verde
    printf("║ [1] Inserir pacote                                          ║\n");
    setColor(11); // Azul claro
    printf("║ [2] Validar pacotes                                         ║\n");
    setColor(12); // Vermelho
    printf("║ [3] Processar fila de enchimento                            ║\n");
    setColor(13); // Rosa
    printf("║ [4] Imprimir filas                                          ║\n");
    setColor(9); // Azul
    printf("║ [5] Relatórios                                              ║\n");
    setColor(12); // Vermelho
    printf("║ [6] Sair                                                    ║\n");
    setColor(7); // Branco
    printf("╚═════════════════════════════════════════════════════════════╝\n");
    setColor(14); // Amarelo
    printf("Escolha uma opção do menu usando o seu teclado [1, 2, 3, 4, 5, 6] : \n");
    setColor(7); // Branco
}

void inserirPacote(Fila *filaPA, Fila *filaPB)
{
    int subOpcao;
    printf("\nEscolha o método de inserção:\n");
    printf("[1] Manual\n");
    printf("[2] Automático\n");
    printf("Opção: ");
    scanf("%d", &subOpcao);

    switch (subOpcao)
    {
    case 1:
        inserirPacoteManual(filaPA, filaPB);
        break;
    case 2:
    {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile("*.txt", &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            printf("Nenhum ficheiro .txt encontrado.\n");
        }
        else
        {
            printf("Ficheiros .txt disponíveis:\n");
            do
            {
                printf("%s\n", findFileData.cFileName);
            } while (FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);

            char nomeFicheiro[100];
            printf("Digite o nome do ficheiro: ");
            scanf("%s", nomeFicheiro);
            inserirPacoteAutomatico(filaPA, filaPB, nomeFicheiro);
        }
        break;
    }
    default:
        printf("Opção inválida!\n");
    }
}

int main()
{
    setlocale(LC_ALL, ""); // Configurar a localidade para UTF-8

    Fila *filaPA = criarFila();
    Fila *filaPB = criarFila();

    Pilha *pilhaPA = criarPilha();
    Pilha *pilhaPB = criarPilha();

    int opcao;
    int descartadosA = 0, descartadosB = 0, processadosA = 0, processadosB = 0;

    do
    {
        printMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirPacote(filaPA, filaPB);
            break;
        case 2:
            validarFila(filaPA, 'A');
            validarFila(filaPB, 'B');
            break;
        case 3:
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
                printf("Fila inválida!\n");
            }
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
            imprimirRelatorios(filaPA, filaPB, descartadosA, descartadosB, processadosA, processadosB);
            destruirFila(filaPA);
            destruirFila(filaPB);
            destruirPilha(pilhaPA);
            destruirPilha(pilhaPB);
            printf("Simulação encerrada. Deseja iniciar uma nova simulação? (s/n): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                filaPA = criarFila();
                filaPB = criarFila();
                pilhaPA = criarPilha();
                pilhaPB = criarPilha();
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
        case 7:
            embalarEmpilhar(filaPA, filaPB, pilhaPA, pilhaPB);
            break;
        default:
            printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar...\n");

        getchar(); // Lê o '\n' pendente do scanf.
        while (getchar() != '\n')
            ; // Garante que o buffer está limpo.

        if (opcao != 6)
        {
            system("cls");
        }

    } while (1); // Loop infinito para garantir que o programa só termina quando o usuário não quiser mais uma simulação
    destruirFila(filaPA);
    destruirFila(filaPB);
    destruirPilha(pilhaPA);
    destruirPilha(pilhaPB);
    return 0;
}

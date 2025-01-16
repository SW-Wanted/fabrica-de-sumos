#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include "Fila.h"
#include "Fila.c"
#include "JuicyFactory.h"
#include "JuicyFactory.c"

int main() {
	setlocale(LC_ALL, "");
	
	Fila * filaPA = criarFila();
    Fila * filaPB = criarFila();
    
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
            // processarFilaEnchimento(filaPA, filaPB, filaPA->tamanho >= 6 ? 6 : 4);
            // Na verdade, aonde está 'filaPB' deve ir a fila de enchimento
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

    printf("\nPressione Enter para continuar...\n");

    getchar(); // Lê o '\n' pendente do scanf.
    while (getchar() != '\n'); // Garante que o buffer está limpo.

    if (opcao != 6) {
        system("cls");
    }

} while (opcao != 6);


    destruirFila(filaPA);
    destruirFila(filaPB);
    
    return 0;
}

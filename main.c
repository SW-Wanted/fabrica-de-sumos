#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include "JuicyFactory.c"
#include "JuicyFactory.h"

int main() {
	setlocale(LC_ALL, "");
	
    Fila * filaPA = criarFila();
    Fila * filaPB = criarFila();
    menu(filaPA, filaPB);

    destruirFila(filaPA);
    destruirFila(filaPB);
    return 0;
}

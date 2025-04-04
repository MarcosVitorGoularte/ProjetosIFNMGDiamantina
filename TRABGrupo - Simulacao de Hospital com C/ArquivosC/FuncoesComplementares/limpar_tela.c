#include <stdio.h>
#include <stdlib.h>

// A declaracao da funcao LimparTela esta em CabecalhosC/FuncoesComplementares/limpar_tela.h

void LimparTela() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #else
        printf("Sistema operacional não suportado para limpar a tela.\n");
    #endif
}

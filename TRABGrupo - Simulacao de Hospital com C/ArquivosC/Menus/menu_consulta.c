#include <stdio.h>
#include "../../CabecalhosC/Menus/menu_consultas.h"
#include "../../CabecalhosC/Consultas/consultas.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"

// A declaracao da funcao MenuConsultas esta em CabecalhosC/Menus/menu_consultas.h
// O corpo da funcao LimparTela esta em ArquivosC/Funcoes/limpar_tela.c
// O corpo das funcoes Inserir, ListarPorMedico, ListarPorPaciente, ListarPorData estao em ArquivosC/Consultas/consultas.c

void MenuConsultas() {
    int loop = 1;
    while (loop) {
        int opcao;
        printf("\nMenu Consultas\n");
        printf("\n[1] Inserir nova consulta\n");
        printf("[2] Listar consultas por medico\n");
        printf("[3] Listar consultas por paciente\n");
        printf("[4] Listar consultas por data\n");
        printf("[0] Sair do menu de consultas\n");
        printf("> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                InserirNovaConsulta();
                break;
            case 2:
                ListarConsultasPorMedico();
                break;
            case 3:
                ListarConsultasPorPaciente();
                break;
            case 4:
                ListarConsultasPorData();
                break;
            case 0:
                LimparTela();
                printf("\nSaindo...\n");
                loop = 0;
                break;
            default:
                LimparTela();
                printf("\n[Opcao invalida! Tente novamente...]\n");
        }
    }
}

#include <stdio.h>
#include "../../CabecalhosC/Menus/menu_medicos.h"
#include "../../CabecalhosC/Medicos/medicos.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"

// A declaracao da funcao MenuMedicos esta em CabecalhosC/Menus/menu_medicos.h
// O corpo funcao LimparTela esta em ArquivosC/Funcoes/limpar_tela.c
// O corpo das funcoes Inserir,Buscar,Listar,Alterar estao em ArquivosC/Medicos/medicos.c

void MenuMedicos(){
  int loop = 1;
  while(loop){
    int opcao;
    printf("\nMenu Medicos\n");
    printf("\n[1] Inserir novo medico\n");
    printf("[2] Buscar medico por nome\n");
    printf("[3] Listar medicos por especialidade\n");
    printf("[4] Alterar dados de um medico\n");
    printf("[0] Sair do menu de medicos\n");
    printf("> ");
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        InserirNovoMedico();
        break;
      case 2:
        BuscarMedicoPorNome();
        break;
      case 3:
        ListarMedicosPorEspecialidade();
        break;
      case 4:
        AlterarDadosMedico();
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

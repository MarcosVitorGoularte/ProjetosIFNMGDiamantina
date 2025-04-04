#include <stdio.h>
#include "../../CabecalhosC/Menus/menu_login.h"
#include "../../CabecalhosC/Menus/menu_medicos.h"
#include "../../CabecalhosC/Menus/menu_pacientes.h"
#include "../../CabecalhosC/Menus/menu_consultas.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"

// A declaracao da funcao MenuLogin esta em CabecalhosC/Menus/menu_login.h
// O corpo funcao LimparTela esta em ArquivosC/Funcoes/limpar_tela.c
// O corpo funcao MenuMedicos esta em ArquivosC/Menus/menu_medicos.c

void MenuLogin(){
  int loop = 1;
  while(loop){
    int opcao;
    printf("\nMenu Login\n");
    printf("\n[1] Pacientes\n");
    printf("[2] Medicos\n");
    printf("[3] Consultas\n");
    printf("[0] Sair do menu de login\n");
    printf("> ");
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        LimparTela();
        MenuPacientes();
        break;
      case 2:
        LimparTela();
        MenuMedicos();
        break;
      case 3:
        LimparTela();
        MenuConsultas();
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

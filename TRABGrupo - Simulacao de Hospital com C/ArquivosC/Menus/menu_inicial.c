#include <stdio.h>
#include "../../CabecalhosC/Menus/menu_inicial.h"
#include "../../CabecalhosC/Menus/menu_login.h"
#include "../../CabecalhosC/Usuarios/login.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"

// Corpo das funcoes de cadastro e verificar login estao em ArquivosC/Usuarios/login.c
// A declaracao da funcao esta em CabecalhosC/Menus/menu_inicial.h

void MenuPrincipal(){
  int loop = 1;
  while(loop){
    int opcao;
    printf("\nMenu Inicial\n");
    printf("\nOla usuario, escolha uma das opcoes: \n\n");
    printf("[1] Efetuar login \n");
    printf("[2] Efetuar cadastro \n");
    printf("[0] Encerrar \n");
    printf("> ");
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        if(VerificarLogin()){
          MenuLogin();
        }
        else{
          loop = 0;
        }
        break;
      case 2:
        CadastrarNovoUsuario();
        break;
      case 0:
        printf("\n[Programa sendo encerrado...]\n");
        loop = 0;
        break;
      default:
        LimparTela();
        printf("\n[Opcao invalida! Tente novamente...]\n");
    }
  }
}

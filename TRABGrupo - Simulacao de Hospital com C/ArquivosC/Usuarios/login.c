#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../CabecalhosC/Usuarios/login.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"

// A declaracao das funcoes e struct esta em CabecalhosC/Usuarios/login.h
// O corpo funcao LimparTela esta em ArquivosC/Funcoes/limpar_tela.c


int VerificarLogin(){

  char *arquivo = {"ArquivosBinarios/login.bin"};
  login user;
  int encontrado = 0;
  int tentativas = 1;
  LimparTela();

  while(tentativas <= 3){

    FILE *file = fopen(arquivo, "rb");

    if(file){

      char nome[20], senha[10];
      printf("\nArea de Login\n");
      printf("Digite o nome de usuario: ");
      scanf("\n%19[^\n]", nome);
      printf("Digite a senha do usuario: ");
      scanf("\n%9[^\n]", senha);

      //Loop para ver se o usuario e senha informados pelo usuario existem
      while(fread(&user, sizeof(login), 1, file)){
        if(strcmp(user.usuario, nome) == 0 && strcmp(user.senha, senha) == 0){
            encontrado = 1;
            break;
        }
      }

      if(encontrado){
        LimparTela();
        fclose(file);
        printf("\n[Login bem-sucedido]\n");
        return 1;
      }
      else{
        fclose(file);
        printf("\nLogin ou senha incorretos! Tente novamente(%d tentativa(s) restante(s))\n", 3-tentativas);
        tentativas++;
      }

    }
    else{
      LimparTela();
      printf("\nErro ao abrir o arquivo...\n");
      return 0;
    }

  }

  LimparTela();
  printf("\n[Muitas tentativas. Encerrando programa...]\n");
  return 0;
}

void CadastrarNovoUsuario(){

  LimparTela();

  //Loop para ver se o usuario quer prosseguir com o cadastro ou nao
  while(1){

    char opcao[4];
    printf("\nDeseja prosseguir com o cadastro (s/n)? ");
    scanf("\n%3[^\n]", opcao);

    if(strcmp(opcao, "sim") == 0 || strcmp(opcao, "s") == 0){

      char *arquivo = {"ArquivosBinarios/login.bin"};
      login user;
      int encontrado = 0;
      FILE *file = fopen(arquivo, "ab"); //Esse fopen esta aqui para criar o arquivo
      fclose(file);
      file = fopen(arquivo, "rb");

      if(file){

          LimparTela();
          char nome[20], senha[10], repetirsenha[10];
          printf("\nArea de Cadastro\n");
          printf("Digite o nome de usuario: ");
          scanf("\n%19[^\n]", nome);

          //Loop para inserir a senha e confirmar
          while(1){
            printf("Senha: ");
            scanf("\n%9[^\n]", senha);
            printf("Confirme a senha: ");
            scanf("\n%9[^\n]", repetirsenha);
            if (strcmp(senha, repetirsenha) != 0)
            {
                printf("[Senhas nao compativeis!]\n");
            }
            else{
                break;
            }
          }

          //Loop para verificar se um usuario com o mesmo nome e a mesma senha ja existe.
          while(fread(&user, sizeof(login), 1, file)){
            if(strcmp(user.usuario, nome) == 0 && strcmp(user.senha, senha) == 0){
                encontrado = 1;
                break;
            }
          }

          if(encontrado){
            fclose(file);
            LimparTela();
            printf("\nCadastro cancelado. Usuario existente.\n");
          }
          else{
            fclose(file);
            file = fopen(arquivo, "ab");
            if(file){
                strcpy(user.usuario, nome);
                strcpy(user.senha, senha);
                fwrite(&user, sizeof(login), 1, file);
                fclose(file);
                LimparTela();
                printf("\nCadastro realizado com sucesso.\n");
            }
            else{
                LimparTela();
                printf("\nErro ao abrir o arquivo\n");
            }
          }
      }
      else{
        LimparTela();
        printf("\nErro ao abrir o arquivo...\n");
      }

      break;
    }

    else{
      if(strcmp(opcao, "nao") == 0 || strcmp(opcao, "n") == 0){
        LimparTela();
        printf("\nCadastro cancelado\n");
        break;
      }
      else{
        LimparTela();
        printf("\nOpcao invalida\n");
      }
    }

  }
}

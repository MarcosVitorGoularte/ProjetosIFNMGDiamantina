#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../CabecalhosC/Medicos/medicos.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"
#include "../../CabecalhosC/FuncoesComplementares/funcoes.h"
#include "../../CabecalhosC/FuncoesComplementares/aperte_enter.h"

// A declaracao das Funcoes Inserir, Buscar, Listar e Alterar esta em Cabecalhos/Medicos/medicos.h
// O corpo funcao LimparTela esta em ArquivosC/Funcoes/limpar_tela.c
// O corpo das funcoes


void InserirNovoMedico(){

  LimparTela();
  // Cria/abre o arquivo medicos.bin
  char *arquivo = {"ArquivosBinarios/medicos.bin"};
  FILE *file = fopen(arquivo, "ab");

  if(file){

    // Muda o ponteiro do arquivo para o final para conseguir medir o seu tamanho
    fseek(file, 0, SEEK_END);

    // Se o tamanho do arquivo for menor que 1, ou seja, sem nenhum dado adicionado
    // ele entra nesse IF e chama a funcao CriarIndexacaoMedico(), que criara o
    // primeiro medico e o primeiro indexMedico junto ao seu arquivo

    if(ftell(file)/sizeof(medico) < 1){

      // O arquivo e fechado aqui, pois sera aberto novamente na funcao CriarIndexacao
      fclose(file);

      if(CriarIndexacaoMedico()){
        printf("\n[Cadastro realizado com sucesso!]\n");

        AperteEnter();

        LimparTela();
      }
      else{
        LimparTela();
        printf("\nOcorreu um erro ao abrir o arquivo. Cancelando processo...\n");
      }
    }
    else{
      // Caso o arquivo tenha um tamanho diferente de 0, ou seja, ja nao estamos mais no primeiro medico,
      // vamos utilizar a Busca Binaria para verificar se o medico existe

      medico novo_medico;
      char CRM[6];

      printf("\nArea de Cadastro de Medicos\n");
      printf("Digite o CRM do medico: ");
      scanf("\n%5[^\n]", CRM);

      // Se retornar 1, nao existe um medico com esse CRM cadastrado e se inicia o cadastro

      if(BuscaBinaria(CRM)){
        printf("Digite o nome do medico: ");
        scanf("\n%49[^\n]", novo_medico.nome);
        strcpy(novo_medico.CRM, CRM);
        printf("Digite a especialidade do medico: ");
        scanf("\n%19[^\n]", novo_medico.especialidade);
        printf("Digite a data de nascimento do medico (dd/mm/aaaa): ");
        scanf("\n%10[^\n]", novo_medico.data_de_nascimento);
        printf("Digite o valor da hora de trabalho do medico: ");
        scanf("%f", &novo_medico.valor_hora_trabalho);
        printf("Digite o telefone do medico (xx xxxxx-xxxx): ");
        scanf("\n%13[^\n]", novo_medico.telefone);

        // Funcao que cria um indexMedico no arquivos index_medicos.bin com o CRM informado nesse
        // cadastrado pelo usuario e sua posicao no arquivo medicos.bin.
        // Se tudo ocorrer de acordo, o medico e cadastrado.

        if(OrganizarIndexMedicoOrdenado(CRM)){
          fwrite(&novo_medico, sizeof(medico), 1, file);
          printf("\n[Cadastro realizado com sucesso!]\n");
          AperteEnter();
          LimparTela();
        }
        else{
          printf("\nErro ao organizar o vetor de indexacao!Cancelando Cadastro...\n");
          LimparTela();
        }

        fclose(file);

      }
      else{
        fclose(file);
        LimparTela();
        printf("\nO medico ja existe! Cancelando processo...\n");
      }
    }
  }
  else{
    LimparTela();
    printf("\nErro ao abrir o arquivo...\n");
  }
}

void BuscarMedicoPorNome(){

  FILE *file = fopen("ArquivosBinarios/medicos.bin", "rb");

  if(file){

    LimparTela();
    char nome[50];
    medico medicos;

    printf("\nDigite o nome do medico que deseja buscar: ");
    scanf("\n%49[^\n]", nome);

    printf("\n--------------------\n");
    printf("\nMedicos encontrados\n");
    printf("\n--------------------\n");
    while(fread(&medicos, sizeof(medico),1,file)){
      if(strcmp(medicos.nome, nome) == 0){
        printf("\nNome: %s\n", medicos.nome);
        printf("CRM: %s\n", medicos.CRM);
        printf("Especialidade: %s\n", medicos.especialidade);
        printf("Data de nascimento: %s\n", medicos.data_de_nascimento);
        printf("Valor por hora de trabalho: R$%.2f\n", medicos.valor_hora_trabalho);
        printf("Telefone: %s\n", medicos.telefone);
        printf("\n--------------------\n");
      }
    }

    fclose(file);

    AperteEnter();

    LimparTela();

  }
  else{
    LimparTela();
    printf("\nErro ao abrir o arquivo\n");
  }
}

void ListarMedicosPorEspecialidade(){

  FILE *file = fopen("ArquivosBinarios/medicos.bin", "rb");

  if(file){

    LimparTela();
    medico medicos;
    char especialidade[20];

    printf("\nDigite a especialidade que deseja buscar: ");
    scanf("\n%19[^\n]", especialidade);

    printf("\n--------------------\n");
    printf("\nMedicos encontrados\n");
    printf("\n--------------------\n");

    while(fread(&medicos, sizeof(medico), 1, file)){
      if(strcmp(medicos.especialidade, especialidade) == 0){
        printf("\nNome: %s\n", medicos.nome);
        printf("CRM: %s\n", medicos.CRM);
        printf("Especialidade: %s\n", medicos.especialidade);
        printf("Data de nascimento: %s\n", medicos.data_de_nascimento);
        printf("Valor por hora de trabalho: R$%.2f\n", medicos.valor_hora_trabalho);
        printf("Telefone: %s\n", medicos.telefone);
        printf("\n--------------------\n");
      }
    }

    fclose(file);

    AperteEnter();

    LimparTela();

  }
  else{
    LimparTela();
    printf("\nErro ao abrir o arquivo\n");
  }
}

void AlterarDadosMedico(){

  FILE *file = fopen("ArquivosBinarios/medicos.bin", "rb+");

  if(file){

    LimparTela();
    medico medicos;
    char CRM[6];

    printf("Digite o CRM do medico que deseja alterar: ");
    scanf("\n%5[^\n]", CRM);

    // Se retornar 0, foi encontrado um medico que pode ser alterado
    if(BuscaBinaria(CRM) == 0){

      // A funcao faz uma busca binaria com o CRM informado no arquivo index_medicos.bin, e ao encontra-lo
      // retorna a posicao que esta vinculada a ele. Que representa a posicao do medico que queremos alterar
      // em medicos.bin

      int posicao_medico = BuscaBinariaRetornaPosicaoMedico(CRM);

      if(posicao_medico == -1){

        LimparTela();
        printf("\nErro ao abrir o arquivo!Cancelando Operacao...\n");

      }
      else{

        // Muda o ponteiro do arquivo para a posicao em que o medico se encontra
        fseek(file, posicao_medico * sizeof(medico), SEEK_SET);

        fread(&medicos, sizeof(medico), 1, file);

        printf("\nMedico encontrado\n");
        printf("\n--------------------\n");
        printf("\nNome: %s\n", medicos.nome);
        printf("CRM: %s\n", medicos.CRM);
        printf("Especialidade: %s\n", medicos.especialidade);
        printf("Data de nascimento: %s\n", medicos.data_de_nascimento);
        printf("Valor por hora de trabalho: R$%.2f\n", medicos.valor_hora_trabalho);
        printf("Telefone: %s\n", medicos.telefone);
        printf("\n--------------------\n");

        // Loop de confirmar a alteracao
        while(1){

          char opcao[4];
          printf("Deseja prosseguir com a alteracao (s/n)? ");
          scanf("\n%3[^\n]", opcao);

          if(strcmp(opcao, "sim") == 0 || strcmp(opcao, "s") == 0){

            printf("\nDigite o nome do medico: ");
            scanf("\n%49[^\n]", medicos.nome);
            printf("Digite a especialidade do medico: ");
            scanf("\n%19[^\n]", medicos.especialidade);
            printf("Digite a data de nascimento do medico (dd/mm/aaaa): ");
            scanf("\n%10[^\n]", medicos.data_de_nascimento);
            printf("Digite o valor da hora de trabalho do medico: ");
            scanf("%f", &medicos.valor_hora_trabalho);
            printf("Digite o telefone do medico (xx xxxxx-xxxx): ");
            scanf("\n%13[^\n]", medicos.telefone);

            fseek(file, posicao_medico * sizeof(medico), SEEK_SET);
            fwrite(&medicos, sizeof(medico), 1, file);
            fclose(file);

            printf("\nAlteracao feita com sucesso!\n");

            AperteEnter();

            LimparTela();

            break;
          }
          else{

            if(strcmp(opcao, "nao") == 0 || strcmp(opcao, "n") == 0){
              fclose(file);
              LimparTela();
              printf("\nAlteracao cancelada...\n");
              break;
            }
            else{
              printf("\nOpcao invalida\n");
            }

          }
        }
      }
    }
    else{
      fclose(file);
      LimparTela();
      printf("\nO medico nao existe! Cancelando processo...\n");
    }
  }
  else{
    LimparTela();
    printf("\nErro ao abrir o arquivo\n");
  }
}

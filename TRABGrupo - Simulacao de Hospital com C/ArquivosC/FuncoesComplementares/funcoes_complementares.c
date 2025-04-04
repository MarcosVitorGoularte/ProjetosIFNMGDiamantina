#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../CabecalhosC/FuncoesComplementares/funcoes.h"

// As declaracoes das funcoes OrganizarIndexMedico, BusBinRetPos, BuscaBinaria, CriarIndexacao estao em CabecalhosC/FuncoesComplementares/funcoes.h

typedef struct {
char CRM[6];
char nome[50];
char especialidade[20];
char data_de_nascimento[11];
float valor_hora_trabalho;
char telefone[14];
} medico;

typedef struct{
char chave[6];
int posicao;
} indexMedico;

int OrganizarIndexMedicoOrdenado(char *busca){

  FILE *file = fopen("ArquivosBinarios/index_medicos.bin", "rb+");

  if(file){

    fseek(file, 0, SEEK_END);

    int tamanho = ftell(file)/sizeof(indexMedico);
    int inicio = 0, fim = tamanho - 1;
    int meio;

    int elemento_buscado = atoi(busca);

    indexMedico indice;

    // Busca binaria para verificar se o CRM se o CRM ja esta no vetor
    // Se nao estiver, o meio sera onde o CRM deve ser encaixado
    while(inicio<=fim){

      meio = (inicio+fim)/2;
      fseek(file, meio*sizeof(indexMedico), SEEK_SET);
      fread(&indice, sizeof(indexMedico), 1, file);

      if(atoi(indice.chave) == elemento_buscado){
        fclose(file);
        return 0;
      }
      else{
        if(atoi(indice.chave) < elemento_buscado){
          inicio = meio + 1;
        }
        else{
          fim = meio - 1;
        }
      }
    }

    indexMedico *vetor = (indexMedico *) malloc((tamanho+1)*sizeof(indexMedico));

    fseek(file, 0, SEEK_SET);

    fread(vetor, sizeof(indexMedico), tamanho, file);

    // Faz uma comparacao para ver se o CRM que esta na posicao indicada pela variavel meio e menor que o CRM que queremos adicionar
    // Se for menor, meio sera acrescido de um, pois isso significa que o CRM que queremos adicionar e maior do que o que esta nesse local
    // Por isso tendo que ser colocado na posicao seguinte

    if(atoi(vetor[meio].chave) < atoi(busca)){
        meio = meio + 1;
    }

    for (int i = tamanho; i > meio; i--){
        vetor[i] = vetor[i - 1];
    }
    strcpy(vetor[meio].chave, busca);
    vetor[meio].posicao = tamanho;

    // Volta o ponteiro para o inicio do arquivo, permitindo que os dados sejam salvos na ordem correta

    fseek(file, 0, SEEK_SET);

    if(fwrite(vetor, sizeof(indexMedico), tamanho+1, file) == tamanho+1){
        fclose(file);
        free(vetor);
        return 1;
    }
    else{
        fclose(file);
        free(vetor);
        return 0;
    }

  }
  return 0;
}

int BuscaBinariaRetornaPosicaoMedico(char *busca){

  // busca = CRM do medico
  // Abre o arquivo index_medicos para para leitura
  FILE *file = fopen("ArquivosBinarios/index_medicos.bin", "rb");

  if(file){

    // Coloca o ponteiro do arquivo para o final do arquivo
    fseek(file, 0, SEEK_END);

    // ftell diz o tamnaho em bytes do arquivo ate o ponto onde esta o ponteiro
    // Como esta na ultima posicao, retorna o tamanho total do arquivo
    // tamanho total do arquivo / tamanho de uma struct indexMedico = numero de index_medicos salvos no arquivo

    int tamanho = ftell(file)/sizeof(indexMedico);
    int inicio = 0, fim = tamanho - 1;
    int meio;

    // atoi converte uma string para numero, se for possivel
    // estamos transformando a string CRM que queremos encontrar a posicao em um numero

    int elemento_buscado = atoi(busca);

    // declara uma variavel do tipo da struct onde vamos armazenar o CRM e qual posicao o mesmo ocupa

    indexMedico indice;

    while(inicio<=fim){

      meio = (inicio+fim)/2;

      fseek(file, meio*sizeof(indexMedico), SEEK_SET);

      fread(&indice, sizeof(indexMedico), 1, file);

      if(atoi(indice.chave) == elemento_buscado){
        fclose(file);
        return indice.posicao;
      }
      else{
        if(atoi(indice.chave) < elemento_buscado){
          inicio = meio + 1;
        }
        else{
          fim = meio - 1;
        }
      }
    }

  }
  else{
    printf("\nErro ao abrir o arquivo\n");
    return -1;
  }
  return -1;
}

int BuscaBinaria(char *busca){

  // busca = CRM do medico
  FILE *file = fopen("ArquivosBinarios/index_medicos.bin", "rb");

  if(file){

    // Coloca o ponteiro do arquivo para o final do arquivo
    fseek(file, 0, SEEK_END);

    // ftell diz o tamnaho em bytes do arquivo ate o ponto onde esta o ponteiro
    int tamanho = ftell(file)/sizeof(indexMedico);
    int inicio = 0, fim = tamanho - 1;
    int meio;

    // atoi converte uma string para numero, se for possivel

    int elemento_buscado = atoi(busca);

    indexMedico indice;

    while(inicio<=fim){

      meio = (inicio+fim)/2;

      fseek(file, meio*sizeof(indexMedico), SEEK_SET);

      fread(&indice, sizeof(indexMedico), 1, file);

      if(atoi(indice.chave) == elemento_buscado){
        fclose(file);
        return 0;
      }
      else{
        if(atoi(indice.chave) < elemento_buscado){
          inicio = meio + 1;
        }
        else{
          fim = meio - 1;
        }
      }
    }

    fclose(file);
    return 1;
  }
    printf("\nErro ao abrir o arquivo\n");
    return 0;
}

int CriarIndexacaoMedico(){

  // Cria o arquivo de index_medicos e o de medicos.bin
  char *index = {"ArquivosBinarios/index_medicos.bin"};
  char *arquivo = {"ArquivosBinarios/medicos.bin"};
  FILE *arquivo_medicos = fopen(arquivo, "wb");
  FILE *arquivos_index = fopen(index, "wb");

  if(arquivos_index && arquivo_medicos){

    medico novo_medico;

    printf("\nArea de Cadastro de Medicos\n");
    printf("Digite o CRM do medico: ");
    scanf("\n%5[^\n]", novo_medico.CRM);
    printf("Digite o nome do medico: ");
    scanf("\n%49[^\n]", novo_medico.nome);
    printf("Digite a especialidade do medico: ");
    scanf("\n%19[^\n]", novo_medico.especialidade);
    printf("Digite a data de nascimento do medico (dd/mm/aaaa): ");
    scanf("\n%10[^\n]", novo_medico.data_de_nascimento);
    printf("Digite o valor da hora de trabalho do medico: ");
    scanf("%f", &novo_medico.valor_hora_trabalho);
    printf("Digite o telefone do medico (xx xxxxx-xxxx): ");
    scanf("\n%13[^\n]", novo_medico.telefone);

    indexMedico vetor[1];

    // Como e o primeiro medico, sua posicao no arquivo medicos.bin sera 0

    strcpy(vetor[0].chave, novo_medico.CRM);
    vetor[0].posicao = 0;

    // Verifica se o CRM e sua posicao vao ser salvos no arquivos_index
    if(fwrite(vetor, sizeof(indexMedico), 1, arquivos_index)){
        // Verifica se o primeiro medico foi adicionado com sucesso em medicos.bin
        if(fwrite(&novo_medico, sizeof(medico), 1, arquivo_medicos)){
            fclose(arquivo_medicos);
            fclose(arquivos_index);
            return 1;
        }
    }

    fclose(arquivo_medicos);
    fclose(arquivos_index);
    return 0;

  }
  else{
    return 0;
  }

}

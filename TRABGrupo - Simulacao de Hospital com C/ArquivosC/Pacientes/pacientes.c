#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char CPF[12];
    char nome[30];
    char data_de_nascimento[11];
    char telefone[14];
} paciente;

typedef struct{
    char chave[12];
    int posicao;
} indexPaciente;

void InserirNovoPaciente()
{
    paciente novoPaciente;
    indexPaciente novoIndex, *indices;
    FILE *arquivopacientes, *arquivoindex;
    int posicao, totalregistro = 0;

    LimparTela();

    arquivoindex = fopen("ArquivosBinarios/indexPaciente.bin", "rb");
    /*abre o arquivo index.paciente.bin no modo leitura(rb) */
    if (arquivoindex != NULL) {
        fseek(arquivoindex, 0, SEEK_END);
        totalregistro = ftell(arquivoindex) / sizeof(indexPaciente);
        fseek(arquivoindex, 0, SEEK_SET);
        /*se existir, fseek para mover o ponteiro no arquivo pro final,
        e ftell  tam. de indexPaciente retorna o total de registros no arquivo,
        fseek novamente para retornar o ponteiro para o inicio*/

        indices = (indexPaciente *)calloc(totalregistro + 1, sizeof(indexPaciente));
        /*aloca memória para armazenar os CPFs mais 1*/
        if (indices == NULL) {
            printf("\nErro na alocação de memória\n");
            fclose(arquivoindex);
            return;
        }

        fread(indices, sizeof(indexPaciente), totalregistro, arquivoindex);
        fclose(arquivoindex);
    } else {
        indices = (indexPaciente *)calloc(1, sizeof(indexPaciente));
        totalregistro = 0;
        /*fread lê os indices guardados e armazezna
        em indices,e fecha o arquivoindex*/
    }

    printf("\nCadastro do Paciente\n");
    printf("CPF do paciente: ");
    scanf("%s", novoPaciente.CPF);

    for (int i = 0; i < totalregistro; i++)
        /*verifica se existe o mesmo CPF registrado*/
        {
            if (strcmp(indices[i].chave, novoPaciente.CPF) == 0) {
                printf("\nErro: Já existe um paciente cadastrado com este CPF.\n");
                free(indices);
                return;
            }
        }

    arquivopacientes = fopen("ArquivosBinarios/paciente.bin", "ab");
    /*abre o arquivo paciente.bin no modo escrita*/
    if (arquivopacientes == NULL) {
        printf("\nO arquivo não foi aberto\n");
        return;
    }

    printf("Digite o nome do paciente: ");
    scanf(" %[^\n]", novoPaciente.nome);
    printf("Digite a data de nascimento do paciente: ");
    scanf(" %[^\n]", novoPaciente.data_de_nascimento);
    printf("Digite o numero de telefone do paciente: ");
    scanf(" %[^\n]", novoPaciente.telefone);

    fseek(arquivopacientes, 0, SEEK_END);
    posicao = ftell(arquivopacientes) / sizeof(paciente);
    fwrite(&novoPaciente, sizeof(paciente), 1, arquivopacientes);
    fclose(arquivopacientes);
    /*fseek garante que o ponteiro esteja no final,
    ftell / tam. de paceinte calcula a posição do novo paciente,
    e fwrite escreve seus dados*/

    strcpy(novoIndex.chave, novoPaciente.CPF);
    novoIndex.posicao = posicao;

    indices[totalregistro] = novoIndex;
    totalregistro++;

    for (int i = 0; i < totalregistro - 1; i++) {
        for (int j = i + 1; j < totalregistro; j++) {
            if (strcmp(indices[i].chave, indices[j].chave) > 0) {
                indexPaciente temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
                /*organiza os CPFs em modo crescente*/
            }
        }
    }

    arquivoindex = fopen("ArquivosBinarios/indexPaciente.bin", "wb");
    /*reabrir o arquivo indexPaciente.bin
    para sobrescrever com os índices ordenados */

    if (arquivoindex == NULL) {
        printf("\nO arquivo de índices não foi aberto\n");
        free(indices);
        return;
    }

    fwrite(indices, sizeof(indexPaciente), totalregistro, arquivoindex);
    fclose(arquivoindex);
    free(indices);
    /*fwrite() grava os indices ordenados,
    fclose() fecha o aquivo e free() libera a memoria.*/

    LimparTela();

    printf("Paciente cadastrado com sucesso!\n");
}

void BuscaPacientePorNome()
{
    FILE *arquivo;
    paciente p;
    char nomeb[30];
    int encontrado = 0;

    LimparTela();

    printf("Digite o nome do paciente: ");
    scanf("\n%[^\n]", nomeb);

    arquivo = fopen("ArquivosBinarios/paciente.bin", "rb");
    /*abre o arquivo apenas para leitura(rb)*/
    if (arquivo == NULL) {
        printf("O arquivo não foi aberto\n");
        return;
    }

    while (fread(&p, sizeof(paciente), 1, arquivo) != 0)
        /*fread lê um bloco de dados, e armazena em p.
        O loop não encerra enqanto houver informações para ler*/
        {
        if (strcmp(p.nome, nomeb) == 0)
        {
            LimparTela();
            printf("\n---------------------------------------------------\n");
            printf("\nPaciente encontrado\n");
            printf("CPF: %s\n", p.CPF);
            printf("Nome: %s\n", p.nome);
            printf("Data de nascimento: %s\n", p.data_de_nascimento);
            printf("Telefone: %s\n", p.telefone);
            printf("\n---------------------------------------------------\n");
            encontrado = 1;
            break;
        }
    /*compara o nome previamente inserido, com todos os registros.
    Se o nome for encontrado, será printado as informções*/
    }
    if (encontrado == 0) {
        printf("\nPaciente nao encontrado\n");
    }
    fclose(arquivo);
}

void AlterarDadosPaciente()
{
    FILE *arquivo;
    paciente p;
    char cpfbusca[12];
    int encontrado = 0, posicao = 0;

    arquivo = fopen("ArquivosBinarios/paciente.bin","r+b");
    /*abre o arquivo paciente.bin para leitura e escrita(r+b),
    sem apagar registrso pré-existentes*/
    if(arquivo == NULL)
    {
        printf("erro ao abrir o arquivo");
        return;
    }

    LimparTela();

    printf("\ndigite o CPF do paciente: \n");
    scanf("\n%[^\n]", cpfbusca);

    while(fread(&p, sizeof(paciente), 1, arquivo) != 0)
        /*fread lê um bloco de dados, e armazena em p.
        O loop não encerra enqanto houver informações para ler*/
        {
        if(strcmp(cpfbusca, p.CPF) == 0)
             /*compara o CPF previamente iinserido, com os CPFs cadastrados,
        até encontra o paciente com CPF inserido*/
        {
            encontrado = 1;
            posicao = ftell(arquivo)-sizeof(paciente);
            /*Armazena a posição do registro*/

            LimparTela();

            printf("digite o novo nome: ");
            scanf("\n%[^\n]", p.nome);
            printf("digite a nova data de nascimento: ");
            scanf("\n%[^\n]", p.data_de_nascimento);
            printf("digite o novo telefone: ");
            scanf("\n%[^\n]", p.telefone);

            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&p, sizeof(paciente), 1, arquivo);
            /*o fseek move o ponteiro do arquivo para o inicio
            da posição do paciente encontrado, e fwrite sobreescreve
            o registro antigo*/
            LimparTela();
            printf("Dados alterados com sucesso!\n");
            break;
        }
    }
    if(encontrado == 0)
            {
                printf("Paciente não encontrado\n");
            }
            fclose(arquivo);
}

void BuscarPacientesPorCPF()
{
    FILE *arquivoindex, *arquivopacientes;
    indexPaciente *indices, indice;
    paciente p;
    char buscacpf[12];
    int inicio =0, fim, meio, encontrado = 0, totalregistro = 0;

    arquivoindex = fopen("ArquivosBinarios/indexPaciente.bin", "rb");
    /*abre o arquivo de indices no modo leitura(rb)*/
    if(arquivoindex == NULL)
    {
        printf("\nArquivo nao encontrado\n");
        return;
    }

    fseek(arquivoindex, 0, SEEK_END);
    totalregistro = ftell(arquivoindex)/sizeof(indexPaciente);
    fseek(arquivoindex, 0, SEEK_SET);
    /*fseek move o ponteiro para o fim do arquivo,
    ftell / tam. indexPaciente retorna a quantidade total de registros,
    e fseek move novamente o ponteiro para início do arquivo*/

    indices = (indexPaciente*)calloc(totalregistro,sizeof(indexPaciente));
    /*Aloca memoria para armazenar os indices*/
    if(indices == NULL)
    {
        printf("\nerro na alocacao\n");
        fclose(arquivoindex);
        return;
    }

    fread(indices, sizeof(indexPaciente), totalregistro, arquivoindex);
    fclose(arquivoindex);
    /*Lê todos os registros de arquivoindex e armazena em indices*/

    LimparTela();

    printf("digite o cpf do paciente: ");
    scanf("%s", buscacpf);

    fim = totalregistro - 1;
    while(inicio <= fim)
    {
        meio = (inicio + fim)/2;

        int cmp = strcmp(indices[meio].chave, buscacpf);

        if(cmp == 0)
        {
            encontrado = 1;
            indice = indices[meio];
            break;
        }
        else
        if(cmp < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
        if(encontrado == 0)
        {
            printf("\npaciente nao encontrado\n");
            free(indices);
            return;
        }
        /*Busca binaria para encontrar o CPF do paciente nos indices*/

    arquivopacientes = fopen("ArquivosBinarios/paciente.bin", "rb");
    /*abre o arquivo paciente.bin no modo leitura(rb)*/
    if(arquivopacientes == NULL)
    {
        printf("\nArquivo nao encontrado\n");
        free(indices);
        return;
    }
    fseek(arquivopacientes, indice.posicao * sizeof(paciente), SEEK_SET);
    /*posiciona o ponteiro do arquivo na posição armazenada
    em indice.posicao * tam. de paciente*/
    if (fread(&p, sizeof(paciente), 1, arquivopacientes) != 1)
    /*Lê o paceinte na posição encontrada, e se houver algun erro,
    printa a mensagem de erro e fecha o arquivo e a libera memoria alocada*/
    {
    printf("\nErro ao ler paciente do arquivo\n");
    }
    fclose(arquivopacientes);
    free(indices);

    LimparTela();

    printf("\n---------------------------------------------------\n");
    printf("\npaciente encontrado\n");
    printf("cpf do paciente: %s\n", p.CPF);
    printf("Nome do paciente: %s\n", p.nome);
    printf("Data de nascimento do paciente: %s\n", p.data_de_nascimento);
    printf("Telefone do paciente: %s\n", p.telefone);
    printf("\n---------------------------------------------------\n");
    /*se o paciente for encontrado, printf das informações*/
}

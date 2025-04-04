/* • Para consultas:
• InserirNovaConsulta(): para cadastrar uma nova consulta.

Instituto Federal de Educação, Ciência e Tecnologia do Norte de Minas Gerais

IFNMG – Campus Montes Claros

• ListarConsultasPorMedico(): para listar todas as consultas de um determinado médico.
• ListarConsultasPorPaciente(): para listar todas as consultas de um determinado
paciente.
• ListarConsultasPorData(): para listar todas as consultas de um determinado dia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../CabecalhosC/Medicos/medicos.h"
#include "../../CabecalhosC/FuncoesComplementares/limpar_tela.h"
#include "../../CabecalhosC/FuncoesComplementares/funcoes.h"
#include "../../CabecalhosC/FuncoesComplementares/aperte_enter.h"

typedef struct {
    char crmMedico[6];
    char cpfPaciente[12];
    char data[11];
    char horario[6];
    char descricao[100];
} Consulta;

void InserirNovaConsulta() {
    LimparTela();
    FILE *file = fopen("ArquivosBinarios/consultas.bin", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Consulta novaConsulta;
    printf("Digite o CRM do médico: \n");
    scanf("\n%49[^\n]", novaConsulta.crmMedico);
    printf("Digite o CPF do paciente: \n");
    scanf("%11s", novaConsulta.cpfPaciente);
    printf("Digite a data da consulta (dd/mm/aaaa): \n");
    scanf("%10s", novaConsulta.data);
    printf("Digite o horário da consulta (hh:mm): \n");
    scanf("%5s", novaConsulta.horario);
    printf("Descrição da consulta: \n");
    scanf(" %[^\n]", novaConsulta.descricao);

    fwrite(&novaConsulta, sizeof(Consulta), 1, file);
    fclose(file);
    printf("Consulta cadastrada com sucesso!\n");
}

void ListarConsultasPorMedico() {
    FILE *file = fopen("ArquivosBinarios/consultas.bin", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char crm[6];
    printf("Digite o CRM do médico: ");
    scanf("%5s", crm);

    Consulta consulta;
    printf("\nConsultas encontradas:\n");
    while (fread(&consulta, sizeof(Consulta), 1, file)) {
        if (strcmp(consulta.crmMedico, crm) == 0) {
            printf("Data: %s, Horário: %s, Paciente: %s, Descrição: %s\n",
                   consulta.data, consulta.horario, consulta.cpfPaciente, consulta.descricao);
        }
    }

    fclose(file);
}

void ListarConsultasPorPaciente() {
    FILE *file = fopen("ArquivosBinarios/consultas.bin", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char cpf[12];
    printf("Digite o CPF do paciente: ");
    scanf("%11s", cpf);

    Consulta consulta;
    printf("\nConsultas encontradas:\n");
    while (fread(&consulta, sizeof(Consulta), 1, file)) {
        if (strcmp(consulta.cpfPaciente, cpf) == 0) {
            printf("Data: %s, Horário: %s, Médico: %s, Descrição: %s\n",
                   consulta.data, consulta.horario, consulta.crmMedico, consulta.descricao);
        }
    }

    fclose(file);
}

void ListarConsultasPorData() {
    FILE *file = fopen("ArquivosBinarios/consultas.bin", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char data[11];
    printf("Digite a data (dd/mm/aaaa): ");
    scanf("%10s", data);

    Consulta consulta;
    printf("\nConsultas encontradas:\n");
    while (fread(&consulta, sizeof(Consulta), 1, file)) {
        if (strcmp(consulta.data, data) == 0) {
            printf("Horário: %s, Médico: %s, Paciente: %s, Descrição: %s\n",
                   consulta.horario, consulta.crmMedico, consulta.cpfPaciente, consulta.descricao);
        }
    }

    fclose(file);
}

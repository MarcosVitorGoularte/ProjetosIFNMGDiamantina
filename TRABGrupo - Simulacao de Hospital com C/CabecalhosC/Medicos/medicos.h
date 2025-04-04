#ifndef MEDICOS_H_INCLUDED
#define MEDICOS_H_INCLUDED

// Medicos.c

typedef struct {
char CRM[6];
char nome[50];
char especialidade[20];
char data_de_nascimento[11];
float valor_hora_trabalho;
char telefone[14];
} medico;

void InserirNovoMedico();

void BuscarMedicoPorNome();

void ListarMedicosPorEspecialidade();

void AlterarDadosMedico();

#endif // MEDICOS_H_INCLUDED

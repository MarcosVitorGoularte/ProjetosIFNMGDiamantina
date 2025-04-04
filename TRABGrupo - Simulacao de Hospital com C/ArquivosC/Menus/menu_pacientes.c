#include <stdio.h>

void MenuPacientes()
{
    int opcao;
    do {
        printf("\nMenu Pacientes:\n");
        printf("1 - Inserir novo paciente\n");
        printf("2 - Buscar paciente por nome\n");
        printf("3 - Alterar dados pelo CPF\n");
        printf("4 - Buscar paciente por cpf\n");
        printf("0 - Sair do menu pacientes\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                InserirNovoPaciente();
                break;
            case 2:
                BuscaPacientePorNome();
                break;
            case 3:
                AlterarDadosPaciente();
                break;
            case 4:
                BuscarPacientesPorCPF();
                break;
            case 0:
                LimparTela();
                printf("\nSaindo...\n");
                break;
            default:
                LimparTela();
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

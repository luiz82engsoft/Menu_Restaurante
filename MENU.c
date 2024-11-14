
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

        // Aumente esse valor para o número máximo desejado de reservas

#define MAX_RES 10
#define DIAS 4

        // struct do cliente

typedef struct {
    char nome[70];
    int quantPessoas;
    int cpf;
    int dia;
} Cliente;

        // sub-rotina exbição menu


void exibirMenu(int *opcao) {
    printf("\n\n\t\t\tMENU\n\n");
    printf("\t1-Fazer reserva.\n\t2-Listar reservas.\n\t3-Total de pessoas por dia.\n\t4-Sair\n\n");
    scanf("%d", opcao);
    getchar();
    printf("\n");
}

        // sub-rotina reserva

void fazerReserva(Cliente reservas[], int *totaldeReservas, int reservadoDia[], int lReservasDia[]) {
    char r;
    int dia;
    bool diaValido = false;

    if (*totaldeReservas < MAX_RES) {
        do {
            printf("\t\t\tFAZER RESERVA\n\n");

            printf("Digite o nome de quem vai reservar:\n\n");
            fgets(reservas[*totaldeReservas].nome, sizeof(reservas[*totaldeReservas].nome) - 1, stdin);
            reservas[*totaldeReservas].nome[strcspn(reservas[*totaldeReservas].nome, "\n")] = '\0';

            printf("\n\nDigite o CPF do cliente:\n\n");
            scanf("%lld", &reservas[*totaldeReservas].cpf);
            printf("\n");

            printf("Digite para quantas pessoas é a reserva:\n\n");
            scanf("%d", &reservas[*totaldeReservas].quantPessoas);
            printf("\n\n");

            do {
                printf("Para qual dia é a reserva:\n\n");
                printf("1-Quinta-feira.\n2-Sexta-feira.\n3-Sábado.\n4-Domingo.\n\n");
                scanf("%d", &dia);
                printf("\n");
                getchar();

                if (dia < 1 || dia > 4) {
                    printf("\n\t\t\tOpção inválida!\n");
                } else {
                    if (reservadoDia[dia - 1] < lReservasDia[dia - 1]) {
                        reservas[*totaldeReservas].dia = dia;
                        reservadoDia[dia - 1]++;
                        (*totaldeReservas)++;
                        printf("Reserva registrada!\n\n");
                        diaValido = true;
                    } else {
                        printf("Limite de reservas excedido!\n");
                    }
                }
            } while (!diaValido);
            do {
                printf("Para continuar, digite s/n:\n\n");
                scanf(" %c", &r);
                getchar();

                if (r != 's' && r != 'S' && r != 'n' && r != 'N') {
                    printf("Entrada inválida! Por favor, tente novamente!.\n\n");

                }
            } while(r != 's' && r != 'S' && r != 'n' && r != 'N');


        } while (r == 's' || r == 'S');

    } else {
        printf("Limite de reservas excedido!\n");
    }
}

        // sub-rotina lista de reserva

void listarReservas(Cliente reservas[], int totaldeReservas) {
    printf("\t\t\t Listar reservas \n\n");

    for (int i = 0; i < totaldeReservas; i++) {
        printf("Nome: %s\n", reservas[i].nome);
        printf("Cpf: %lld\n", reservas[i].cpf);
        printf("Quantidade de pessoas: %d\n", reservas[i].quantPessoas);
        printf("Dia: ");
        switch (reservas[i].dia) {
        case 1:
            printf("1 - Quinta-Feira -\n");
            break;
        case 2:
            printf("2 - Sexta-Feira -\n");
            break;
        case 3:
            printf("3 - Sábado -\n");
            break;
        case 4:
            printf("4 - Domingo -\n");
            break;
        }
        printf("\n===================\n\n");
    }
}

        // sub-rotina contador de cliente e reserva

void totalPessoasPorDia(Cliente reservas[], int totaldeReservas, int totalPessoas[]) {
    for (int i = 0; i < DIAS; i++) {
        totalPessoas[i] = 0;
    }

    for (int i = 0; i < totaldeReservas; i++) {
        totalPessoas[reservas[i].dia - 1] += reservas[i].quantPessoas;
    }

    printf("\t\t\t Total de pessoas por dia \n\n");
    printf("Quinta-feira: %d\n", totalPessoas[0]);
    printf("Sexta-feira: %d\n", totalPessoas[1]);
    printf("Sábado: %d\n", totalPessoas[2]);
    printf("Domingo: %d\n", totalPessoas[3]);
}
        // sub-rotina finalizar programa

void sairDoPrograma(int *sair) {
    *sair = 1;
}

int main() {
    setlocale(LC_ALL,"");

    Cliente reservas[MAX_RES];
    int totalPessoas[DIAS] = {0};
    int totaldeReservas = 0;
    int reservadoDia[DIAS] = {0};
    int lReservasDia[DIAS] = {6, 6, 6, 6};
    int sair = 0, opcao;

    while (!sair) {
        exibirMenu(&opcao);

        switch (opcao) {
        case 1:
            fazerReserva(reservas, &totaldeReservas, reservadoDia, lReservasDia);
            break;

        case 2:
            listarReservas(reservas, totaldeReservas);
            break;

        case 3:
            totalPessoasPorDia(reservas, totaldeReservas, totalPessoas);
            break;

        case 4:
            sairDoPrograma(&sair);
            printf("Encerrando aplicação!...\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}

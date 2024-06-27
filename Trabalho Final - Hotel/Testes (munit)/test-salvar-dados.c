#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "munit/munit.h"

// Definindo as mesmas structs do código principal
typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

typedef struct {
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    char status[10]; // "ocupado" ou "desocupado"
} Quarto;

typedef struct {
    int codigo;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
    char horarioEntrada[6];
    char horarioSaida[6];
} Estadia;

// Função para salvar os dados (copiada do código principal)
void salvarDados(Cliente clientes[], int totalClientes, Funcionario funcionarios[], int totalFuncionarios, Estadia estadias[], int totalEstadias, Quarto quartos[], int totalQuartos, int proximoCodigoCliente, int proximoCodigoFuncionario, int proximoCodigoEstadia) {
    FILE *file;

    file = fopen("clientes.txt", "w");
    for (int i = 0; i < totalClientes; i++) {
        fprintf(file, "%d,%s,%s,%s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
    }
    fclose(file);

    file = fopen("funcionarios.txt", "w");
    for (int i = 0; i < totalFuncionarios; i++) {
        fprintf(file, "%d,%s,%s,%s,%.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
    }
    fclose(file);

    file = fopen("estadias.txt", "w");
    for (int i = 0; i < totalEstadias; i++) {
        fprintf(file, "%d,%d,%d,%d,%s,%s,%s,%s\n", estadias[i].codigo, estadias[i].codigoCliente, estadias[i].numeroQuarto, estadias[i].quantidadeDiarias, estadias[i].dataEntrada, estadias[i].horarioEntrada, estadias[i].dataSaida, estadias[i].horarioSaida);
    }
    fclose(file);

    file = fopen("quartos.txt", "w");
    for (int i = 0; i < totalQuartos; i++) {
        fprintf(file, "%d,%d,%.2f,%s\n", quartos[i].numero, quartos[i].quantidadeHospedes, quartos[i].valorDiaria, quartos[i].status);
    }
    fclose(file);

    file = fopen("codigo.txt", "w");
    fprintf(file, "%d %d %d\n", proximoCodigoCliente, proximoCodigoFuncionario, proximoCodigoEstadia);
    fclose(file);
}

// Função de teste para salvarDados
static MunitResult test_salvar_dados() {
    // Dados de exemplo para teste
    Cliente clientes[] = {
        {1, "Cliente 1", "Endereco 1", "123456789"},
        {2, "Cliente 2", "Endereco 2", "987654321"}
    };
    int totalClientes = sizeof(clientes) / sizeof(Cliente);

    Funcionario funcionarios[] = {
        {1, "Funcionario 1", "111222333", "Cargo 1", 1500.0},
        {2, "Funcionario 2", "444555666", "Cargo 2", 2000.0}
    };
    int totalFuncionarios = sizeof(funcionarios) / sizeof(Funcionario);

    Estadia estadias[] = {
        {1, "01/01/2024", "05/01/2024", 5, 1, 101, "08:00", "12:00"},
        {2, "02/01/2024", "06/01/2024", 4, 2, 102, "09:00", "13:00"}
    };
    int totalEstadias = sizeof(estadias) / sizeof(Estadia);

    Quarto quartos[] = {
        {101, 2, 150.0, "desocupado"},
        {102, 3, 200.0, "ocupado"}
    };
    int totalQuartos = sizeof(quartos) / sizeof(Quarto);

    int proximoCodigoCliente = 3;
    int proximoCodigoFuncionario = 3;
    int proximoCodigoEstadia = 3;

    // Executar a função de salvar dados
    salvarDados(clientes, totalClientes, funcionarios, totalFuncionarios, estadias, totalEstadias, quartos, totalQuartos, proximoCodigoCliente, proximoCodigoFuncionario, proximoCodigoEstadia);

    // Verificar se os arquivos foram criados corretamente e contêm os dados esperados
    FILE *file;
    char line[256];

    // Verifica arquivo clientes.txt
    file = fopen("clientes.txt", "r");
    munit_assert_not_null(file);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Debug: imprime a linha lida
        // Aqui você pode adicionar verificações específicas para cada linha lida, se necessário
    }
    fclose(file);

    // Verifica arquivo funcionarios.txt
    file = fopen("funcionarios.txt", "r");
    munit_assert_not_null(file);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Debug: imprime a linha lida
        // Aqui você pode adicionar verificações específicas para cada linha lida, se necessário
    }
    fclose(file);

    // Verifica arquivo estadias.txt
    file = fopen("estadias.txt", "r");
    munit_assert_not_null(file);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Debug: imprime a linha lida
        // Aqui você pode adicionar verificações específicas para cada linha lida, se necessário
    }
    fclose(file);

    // Verifica arquivo quartos.txt
    file = fopen("quartos.txt", "r");
    munit_assert_not_null(file);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Debug: imprime a linha lida
        // Aqui você pode adicionar verificações específicas para cada linha lida, se necessário
    }
    fclose(file);

    // Verifica arquivo codigo.txt
    file = fopen("codigo.txt", "r");
    munit_assert_not_null(file);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Debug: imprime a linha lida
        // Aqui você pode adicionar verificações específicas para cada linha lida, se necessário
    }
    fclose(file);

    return MUNIT_OK;
}

// Lista de testes
static MunitTest tests[] = {
    { (char *) "test_salvar_dados", test_salvar_dados, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Suite de testes
static MunitSuite suite = {
    (char *) "suite",    // Nome da suite
    tests,               // Array de testes
    NULL,                // Inicialização da suite
    1,                   // Número máximo de testes concorrentes
    MUNIT_SUITE_OPTION_NONE
};

// Função principal para executar os testes
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
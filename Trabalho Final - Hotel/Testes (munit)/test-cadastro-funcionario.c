#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"

// Definindo as Structs
#define MAX 100

typedef struct {
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

// Variável global para gerar códigos automaticamente
int proximoCodigoFuncionario = 1;

// Função para cadastrar Funcionário
void cadastrarFuncionario(Funcionario funcionarios[], int *totalFuncionarios, FILE* input) {
    Funcionario f;
    f.codigo = proximoCodigoFuncionario++;

    printf("Codigo do funcionario gerado automaticamente: %d\n", f.codigo);
    printf("Digite o nome do funcionario: ");
    fscanf(input, " %[^\n]", f.nome); 
    printf("Digite o telefone do funcionario: ");
    fscanf(input, " %[^\n]", f.telefone); 
    printf("Digite o cargo do funcionario: ");
    fscanf(input, " %[^\n]", f.cargo);  
    printf("Digite o salario do funcionario: ");
    fscanf(input, "%f", &f.salario);
    printf("Funcionario cadastrado com sucesso!\n");

    funcionarios[*totalFuncionarios] = f;
    (*totalFuncionarios)++;
}

// Função de setup para testes de funcionários
static void* setup_funcionarios(const MunitParameter params[], void* user_data) {
    Funcionario* funcionarios = malloc(MAX * sizeof(Funcionario));
    if (funcionarios == NULL) {
        return NULL;
    }
    int* totalFuncionarios = malloc(sizeof(int));
    if (totalFuncionarios == NULL) {
        free(funcionarios);
        return NULL;
    }
    *totalFuncionarios = 0;
    return (void*)funcionarios;
}

// Função de cleanup para testes de funcionários
static void teardown_funcionarios(void* fixture) {
    free(fixture);
}

// Função para comparar floats com uma tolerância
static int comparar_floats(float esperado, float atual, float tolerancia) {
    return fabs(esperado - atual) <= tolerancia;
}

// Teste unitário para cadastrarFuncionario
static MunitResult test_cadastrar_funcionario(const MunitParameter params[], void* fixture) {
    Funcionario* funcionarios = (Funcionario*)fixture;
    int totalFuncionarios = 0;

    // Cria um arquivo temporário para simular a entrada do usuário
    FILE* input_stream = tmpfile();
    if (input_stream == NULL) {
        return MUNIT_ERROR;
    }

    // Escreve os dados simulados no arquivo temporário
    fprintf(input_stream, "Joao da Silva\n(11) 91234-5678\nGerente\n5000.0\n");
    rewind(input_stream);

    // Passa o arquivo temporário como entrada para a função cadastrarFuncionario
    cadastrarFuncionario(funcionarios, &totalFuncionarios, input_stream);

    // Fecha o arquivo temporário
    fclose(input_stream);

    // Verifica se o funcionário foi cadastrado corretamente
    munit_assert_int(totalFuncionarios, ==, 1);
    munit_assert_int(funcionarios[0].codigo, ==, 1);
    munit_assert_string_equal(funcionarios[0].nome, "Joao da Silva");
    munit_assert_string_equal(funcionarios[0].telefone, "(11) 91234-5678");
    munit_assert_string_equal(funcionarios[0].cargo, "Gerente");
    munit_assert_true(comparar_floats(5000.0, funcionarios[0].salario, 1e-6));

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_cadastrar_funcionario", test_cadastrar_funcionario, setup_funcionarios, teardown_funcionarios, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Configuração da suite de testes
static const MunitSuite suite = {
    "/test_suite", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

// Função principal que roda os testes
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
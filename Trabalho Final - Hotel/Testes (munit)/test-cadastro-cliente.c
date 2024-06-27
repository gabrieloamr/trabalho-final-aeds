#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"

// Definindo as Structs
#define MAX 100
#define NUM_QUARTOS 10

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

// Definindo as variáveis para gerar automaticamente os códigos
int proximoCodigoCliente = 1;
int proximoCodigoFuncionario = 1;
int proximoCodigoEstadia = 1;

// Função para Cadastrar Cliente
void cadastrarCliente(Cliente clientes[], int *totalClientes, FILE* input) {
    Cliente c;
    c.codigo = proximoCodigoCliente++;

    printf("Codigo do cliente gerado automaticamente: %d\n", c.codigo);
    printf("Nome: ");
    fscanf(input, " %[^\n]", c.nome); 
    printf("Endereco: ");
    fscanf(input, " %[^\n]", c.endereco);
    printf("Telefone: ");
    fscanf(input, " %[^\n]", c.telefone);  
    printf("Cliente cadastrado com sucesso!\n");

    clientes[*totalClientes] = c;
    (*totalClientes)++;
}

// Função de setup para testes de cliente
static void* setup_clientes(const MunitParameter params[], void* user_data) {
    Cliente* clientes = malloc(MAX * sizeof(Cliente));
    if (clientes == NULL) {
        return NULL;
    }
    int* totalClientes = malloc(sizeof(int));
    if (totalClientes == NULL) {
        free(clientes);
        return NULL;
    }
    *totalClientes = 0;
    return (void*)clientes;
}

// Função de cleanup para testes de cliente
static void teardown_clientes(void* fixture) {
    free(fixture);
}

// Teste unitário para cadastrarCliente
static MunitResult test_cadastrar_cliente(const MunitParameter params[], void* fixture) {
    Cliente* clientes = (Cliente*)fixture;
    int totalClientes = 0;

    // Cria um arquivo temporário para simular a entrada do usuário
    FILE* input_stream = tmpfile();
    if (input_stream == NULL) {
        return MUNIT_ERROR;
    }

    // Escreve os dados simulados no arquivo temporário
    fprintf(input_stream, "Joao da Silva\nRua das Flores, 123\n(11) 91234-5678\n");
    rewind(input_stream);

    // Passa o arquivo temporário como entrada para a função cadastrarCliente
    cadastrarCliente(clientes, &totalClientes, input_stream);

    // Fecha o arquivo temporário
    fclose(input_stream);

    // Verificando se o cliente foi cadastrado corretamente
    munit_assert_int(totalClientes, ==, 1);
    munit_assert_int(clientes[0].codigo, ==, 1);
    munit_assert_string_equal(clientes[0].nome, "Joao da Silva");
    munit_assert_string_equal(clientes[0].endereco, "Rua das Flores, 123");
    munit_assert_string_equal(clientes[0].telefone, "(11) 91234-5678");

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_cadastrar_cliente", test_cadastrar_cliente, setup_clientes, teardown_clientes, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/test_suite", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
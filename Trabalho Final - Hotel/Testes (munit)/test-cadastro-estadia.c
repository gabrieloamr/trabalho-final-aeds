#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "munit/munit.h"

// Definições das Structs e funções relevantes
#define MAX 100
#define NUM_QUARTOS 10

typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

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

// Funções a serem testadas
void cadastrarEstadia(Estadia estadias[], int *totalEstadias, Cliente clientes[], int totalClientes, Quarto quartos[], int totalQuartos);
void calcularDataSaida(const char *dataEntrada, int quantidadeDiarias, char *dataSaida);
float calcularValorEstadia(int quantidadeDiarias, float valorDiaria);
int verificarDisponibilidade(Estadia estadias[], int totalEstadias, int numeroQuarto, const char *dataEntrada, const char *dataSaida, const char *horarioEntrada, const char *horarioSaida);
int compararDatas(const char *dataHora1, const char *dataHora2);

// Teste unitário para cadastrarEstadia
static MunitResult test_cadastrar_estadia(const MunitParameter params[], void* fixture) {
    Cliente clientes[MAX] = { { 1, "Cliente Teste", "Endereco Teste", "123456789" } };
    Quarto quartos[NUM_QUARTOS];
    for (int i = 0; i < NUM_QUARTOS; i++) {
        quartos[i].numero = i + 1;
        quartos[i].quantidadeHospedes = 2;
        quartos[i].valorDiaria = 150.0;
        strcpy(quartos[i].status, "desocupado");
    }
    Estadia estadias[MAX];
    int totalEstadias = 0;

    // Simulando entrada do usuário para o teste
    // Nesse exemplo, inserimos diretamente os valores para evitar interação manual
    Estadia entrada = {
        .codigoCliente = 1,
        .numeroQuarto = 1,
        .quantidadeDiarias = 3,
        .horarioEntrada = "08:00",
        .dataEntrada = "01/01/2024",
        .horarioSaida = "",
        .dataSaida = ""
    };

    cadastrarEstadia(estadias, &totalEstadias, clientes, 1, quartos, NUM_QUARTOS);

    // Testes usando MUnit
    munit_assert_int(totalEstadias, ==, 1);
    munit_assert_string_equal(estadias[0].dataSaida, "04/01/2024");
    munit_assert_string_equal(estadias[0].horarioEntrada, "08:00");
    munit_assert_float_equal(estadias[0].quantidadeDiarias, 3, 1e-6);
    munit_assert_int(estadias[0].codigoCliente, ==, 1);
    munit_assert_int(estadias[0].numeroQuarto, ==, 1);

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_cadastrar_estadia", test_cadastrar_estadia, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
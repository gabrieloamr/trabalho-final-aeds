#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"

// Função para calcular o valor da estadia
float calcularValorEstadia(int quantidadeDiarias, float valorDiaria) {
    return quantidadeDiarias * valorDiaria;
}

// Teste unitário para calcularValorEstadia
static MunitResult test_calcular_valor_estadia(const MunitParameter params[], void* fixture) {
    // Teste 1: Calcular valor para 5 diárias com valor diária de R$ 150,00
    float valorCalculado = calcularValorEstadia(5, 150.0);
    munit_assert_float_equal(valorCalculado, 750.0, 1e-6);

    // Teste 2: Calcular valor para 3 diárias com valor diária de R$ 200,00
    valorCalculado = calcularValorEstadia(3, 200.0);
    munit_assert_float_equal(valorCalculado, 600.0, 1e-6);

    // Teste 3: Calcular valor para 1 diária com valor diária de R$ 100,00
    valorCalculado = calcularValorEstadia(1, 100.0);
    munit_assert_float_equal(valorCalculado, 100.0, 1e-6);

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_calcular_valor_estadia", test_calcular_valor_estadia, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
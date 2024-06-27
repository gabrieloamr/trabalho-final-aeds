#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"

// Função para calcular data de saída
void calcularDataSaida(const char *dataEntrada, int quantidadeDiarias, char *dataSaida) {
    int dia, mes, ano;
    struct tm tm;
    time_t t;

    // Converter string para struct tm
    sscanf(dataEntrada, "%d/%d/%d", &dia, &mes, &ano);
    tm.tm_mday = dia;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    // Adicionar dias
    t = mktime(&tm) + quantidadeDiarias * 24 * 3600;
    tm = *localtime(&t);

    // Converter struct tm para string
    strftime(dataSaida, 11, "%d/%m/%Y", &tm);
}

// Teste unitário para calcularDataSaida
static MunitResult test_calcular_data_saida(const MunitParameter params[], void* fixture) {
    char dataSaida[11];

    // Teste 1: Calcula data de saída para entrada "01/01/2023" e 5 diárias
    calcularDataSaida("01/01/2023", 5, dataSaida);
    munit_assert_string_equal(dataSaida, "06/01/2023");

    // Teste 2: Calcula data de saída para entrada "01/12/2022" e 10 diárias
    calcularDataSaida("01/12/2022", 10, dataSaida);
    munit_assert_string_equal(dataSaida, "11/12/2022");

    // Teste 3: Calcula data de saída para entrada "28/02/2024" e 2 diárias
    calcularDataSaida("28/02/2024", 2, dataSaida);
    munit_assert_string_equal(dataSaida, "01/03/2024");

    // Teste 4: Calcula data de saída para entrada "31/12/2022" e 1 diária (ano bissexto)
    calcularDataSaida("31/12/2022", 1, dataSaida);
    munit_assert_string_equal(dataSaida, "01/01/2023");

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_calcular_data_saida", test_calcular_data_saida, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
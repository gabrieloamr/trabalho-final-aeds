#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"

// Função para comparar duas datas no formato "dd/mm/aaaa hh:mm"
int compararDatas(const char *dataHora1, const char *dataHora2) {
    struct tm tm1, tm2;
    time_t t1, t2;

    sscanf(dataHora1, "%d/%d/%d %d:%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year, &tm1.tm_hour, &tm1.tm_min);
    sscanf(dataHora2, "%d/%d/%d %d:%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year, &tm2.tm_hour, &tm2.tm_min);

    tm1.tm_mon--;
    tm1.tm_year -= 1900;
    tm1.tm_sec = 0;
    tm1.tm_isdst = -1;

    tm2.tm_mon--;
    tm2.tm_year -= 1900;
    tm2.tm_sec = 0;
    tm2.tm_isdst = -1;

    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    if (t1 < t2) return -1;
    if (t1 > t2) return 1;
    return 0;
}

// Teste unitário para compararDatas
static MunitResult test_comparar_datas(const MunitParameter params[], void* fixture) {
    const char *dataHora1 = "01/01/2023 12:00";
    const char *dataHora2 = "01/01/2023 12:30";
    const char *dataHora3 = "01/01/2023 11:00";

    // Teste 1: dataHora1 é menor que dataHora2
    munit_assert_int(compararDatas(dataHora1, dataHora2), ==, -1);

    // Teste 2: dataHora2 é maior que dataHora1
    munit_assert_int(compararDatas(dataHora2, dataHora1), ==, 1);

    // Teste 3: dataHora1 é igual a dataHora1
    munit_assert_int(compararDatas(dataHora1, dataHora1), ==, 0);

    // Teste 4: dataHora1 é menor que dataHora3
    munit_assert_int(compararDatas(dataHora1, dataHora3), ==, 1);

    // Teste 5: dataHora3 é maior que dataHora1
    munit_assert_int(compararDatas(dataHora3, dataHora1), ==, -1);

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_comparar_datas", test_comparar_datas, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
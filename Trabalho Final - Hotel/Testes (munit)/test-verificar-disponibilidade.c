#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"

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

int proximoCodigoEstadia = 1;

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

// Função para verificar a disponibilidade de um quarto
int verificarDisponibilidade(Estadia estadias[], int totalEstadias, int numeroQuarto, const char *dataEntrada, const char *dataSaida, const char *horarioEntrada, const char *horarioSaida) {
    char entrada[17], saida[17], entradaExistente[17], saidaExistente[17];

    snprintf(entrada, sizeof(entrada), "%s %s", dataEntrada, horarioEntrada);
    snprintf(saida, sizeof(saida), "%s %s", dataSaida, horarioSaida);

    for (int i = 0; i < totalEstadias; i++) {
        if (estadias[i].numeroQuarto == numeroQuarto) {
            snprintf(entradaExistente, sizeof(entradaExistente), "%s %s", estadias[i].dataEntrada, estadias[i].horarioEntrada);
            snprintf(saidaExistente, sizeof(saidaExistente), "%s %s", estadias[i].dataSaida, estadias[i].horarioSaida);

            if (!(compararDatas(saida, entradaExistente) <= 0 || compararDatas(entrada, saidaExistente) >= 0)) {
                return 0;
            }
        }
    }
    return 1;
}

// Teste unitário para verificarDisponibilidade
static MunitResult test_verificar_disponibilidade(const MunitParameter params[], void* fixture) {
    // Criar algumas estadias de exemplo
    Estadia estadias[] = {
        { 1, "01/01/2023", "05/01/2023", 5, 1, 1, "08:00", "12:00" },
        { 2, "10/01/2023", "15/01/2023", 6, 2, 2, "10:00", "14:00" },
        { 3, "20/01/2023", "25/01/2023", 6, 3, 1, "09:00", "13:00" }
    };
    int totalEstadias = sizeof(estadias) / sizeof(estadias[0]);

    // Teste 1: Verificar disponibilidade para o quarto 1, entrada "06/01/2023", saída "09/01/2023", horário entrada "08:00", horário saída "12:00"
    int disponivel = verificarDisponibilidade(estadias, totalEstadias, 1, "06/01/2023", "09/01/2023", "08:00", "12:00");
    munit_assert_int(disponivel, ==, 1);

    // Teste 2: Verificar disponibilidade para o quarto 2, entrada "12/01/2023", saída "13/01/2023", horário entrada "09:00", horário saída "10:00"
    disponivel = verificarDisponibilidade(estadias, totalEstadias, 2, "12/01/2023", "13/01/2023", "09:00", "10:00");
    munit_assert_int(disponivel, ==, 0); // Deve retornar 0 pois o quarto está ocupado neste período

    // Teste 3: Verificar disponibilidade para o quarto 3, entrada "24/01/2023", saída "27/01/2023", horário entrada "08:00", horário saída "14:00"
    disponivel = verificarDisponibilidade(estadias, totalEstadias, 3, "24/01/2023", "27/01/2023", "08:00", "14:00");
    munit_assert_int(disponivel, ==, 1);

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_verificar_disponibilidade", test_verificar_disponibilidade, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "munit/munit.h"
#include <math.h>

// Definindo as Structs
#define MAX 100
#define NUM_QUARTOS 10

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    char status[10]; // "ocupado" ou "desocupado"
} Quarto;

// Função para inicializar Quartos
void inicializarQuartos(Quarto quartos[]) {
    for (int i = 0; i < NUM_QUARTOS; i++) {
        quartos[i].numero = i + 1;
        if (i < 2) {
            quartos[i].quantidadeHospedes = 2;
            quartos[i].valorDiaria = 150.0;
        } else if (i < 5) {
            quartos[i].quantidadeHospedes = 3;
            quartos[i].valorDiaria = 225.0;
        } else if (i < 8) {
            quartos[i].quantidadeHospedes = 4;
            quartos[i].valorDiaria = 300.0;
        } else {
            quartos[i].quantidadeHospedes = 5;
            quartos[i].valorDiaria = 375.0;
        }
        strcpy(quartos[i].status, "desocupado");
    }
}

// Função auxiliar para comparar floats com uma tolerância específica
static int comparar_floats(float esperado, float atual, float tolerancia) {
    return fabs(esperado - atual) <= tolerancia;
}

// Função de setup para testes de quartos
static void* setup_quartos(const MunitParameter params[], void* user_data) {
    Quarto* quartos = malloc(NUM_QUARTOS * sizeof(Quarto));
    if (quartos == NULL) {
        return NULL;
    }
    return (void*)quartos;
}

// Função de cleanup para testes de quartos
static void teardown_quartos(void* fixture) {
    free(fixture);
}

// Teste unitário para inicializarQuartos
static MunitResult test_inicializar_quartos(const MunitParameter params[], void* fixture) {
    Quarto* quartos = (Quarto*)fixture;

    // Chama a função para inicializar os quartos
    inicializarQuartos(quartos);

    // Verifica se os quartos foram inicializados corretamente
    for (int i = 0; i < NUM_QUARTOS; i++) {
        munit_assert_int(quartos[i].numero, ==, i + 1);
        if (i < 2) {
            munit_assert_int(quartos[i].quantidadeHospedes, ==, 2);
            munit_assert_true(comparar_floats(quartos[i].valorDiaria, 150.0, 1e-6));
        } else if (i < 5) {
            munit_assert_int(quartos[i].quantidadeHospedes, ==, 3);
            munit_assert_true(comparar_floats(quartos[i].valorDiaria, 225.0, 1e-6));
        } else if (i < 8) {
            munit_assert_int(quartos[i].quantidadeHospedes, ==, 4);
            munit_assert_true(comparar_floats(quartos[i].valorDiaria, 300.0, 1e-6));
        } else {
            munit_assert_int(quartos[i].quantidadeHospedes, ==, 5);
            munit_assert_true(comparar_floats(quartos[i].valorDiaria, 375.0, 1e-6));
        }
        munit_assert_string_equal(quartos[i].status, "desocupado");
    }

    return MUNIT_OK;
}

// Definição dos testes
static MunitTest tests[] = {
    { "/test_inicializar_quartos", test_inicializar_quartos, setup_quartos, teardown_quartos, MUNIT_TEST_OPTION_NONE, NULL },
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "munit/munit.h"

// Definição das structs (copiadas do seu código principal)
typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

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

// Função para exibir reservas (copiada do seu código principal)
void exibirReservas(Estadia estadias[], int totalEstadias, Cliente clientes[], int totalClientes) {
    printf("          Reservas          \n");
    
    for (int i = 0; i < totalEstadias; i++) {
        Estadia e = estadias[i];
        Cliente c;

        // Buscar o cliente pelo código
        for (int j = 0; j < totalClientes; j++) {
            if (clientes[j].codigo == e.codigoCliente) {
                c = clientes[j];
                break;
            }
        }
        printf("----------------------------\n");
        printf("Estadia Codigo: %d\n", e.codigo);
        printf("Cliente: %s\n", c.nome);
        printf("Quarto Numero: %d\n", e.numeroQuarto);
        printf("Data de Entrada: %s %s\n", e.dataEntrada, e.horarioEntrada);
        printf("Data de Saida: %s %s\n", e.dataSaida, e.horarioSaida);
        printf("----------------------------\n");
    }
}

// Função de teste para exibirReservas
static MunitResult test_exibir_reservas() {
    // Arrays de clientes e estadias para teste
    Cliente clientes[] = {
        {1, "João", "Rua A, 123", "(11) 9999-8888"},
        {2, "Maria", "Rua B, 456", "(11) 7777-6666"}
    };
    Estadia estadias[] = {
        {1, "01/06/2024", "03/06/2024", 3, 1, 101, "14:00", "12:00"},
        {2, "02/06/2024", "04/06/2024", 2, 2, 102, "15:00", "11:00"}
    };

    int totalClientes = sizeof(clientes) / sizeof(Cliente);
    int totalEstadias = sizeof(estadias) / sizeof(Estadia);

    // Capturando a saída da função printf usando redirecionamento de fluxo
    char buffer[1024];
    FILE *stream;
    stream = freopen("test_output.txt", "w", stdout); // Redireciona a saída para um arquivo

    // Executa a função que deve imprimir as reservas
    exibirReservas(estadias, totalEstadias, clientes, totalClientes);

    // Fecha o stream para terminar o redirecionamento
    fclose(stdout);

    // Abre o arquivo e verifica se contém as saídas esperadas
    FILE *fp = fopen("test_output.txt", "r");
    munit_assert_not_null(fp);

    // Verificações detalhadas da saída
    int foundReservas = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer); // Imprime o conteúdo do arquivo de saída para debug

        // Exemplo de asserção para verificar se a saída contém informações esperadas
        if (strstr(buffer, "Estadia Codigo: 1") != NULL) {
            foundReservas = 1;
        }
    }

    fclose(fp);

    // Verifica se encontrou a string "Estadia Codigo: 1" na saída
    munit_assert_true(foundReservas);

    return MUNIT_OK;
}

// Lista de testes
static MunitTest tests[] = {
    { (char *) "test_exibir_reservas", test_exibir_reservas, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
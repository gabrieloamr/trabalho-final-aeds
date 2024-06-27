// Incluindo bibliotecas
#include "bibliotecas.h"

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
void cadastrarCliente(Cliente clientes[], int *totalClientes) {
    Cliente c;
    c.codigo = proximoCodigoCliente++;

    printf("Codigo do cliente gerado automaticamente: %d\n", c.codigo);
    printf("Nome: ");
    scanf(" %[^\n]", c.nome); 
    printf("Endereco: ");
    scanf(" %[^\n]", c.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", c.telefone);  
    printf("Cliente cadastrado com sucesso!\n");

    clientes[*totalClientes] = c;
    (*totalClientes)++;
}

// Função para Cadastrar Funcionário
void cadastrarFuncionario(Funcionario funcionarios[], int *totalFuncionarios) {
    Funcionario f;
    f.codigo = proximoCodigoFuncionario++;

    printf("Codigo do funcionario gerado automaticamente: %d\n", f.codigo);
    printf("Digite o nome do funcionario: ");
    scanf(" %[^\n]", f.nome); 
    printf("Digite o telefone do funcionario: ");
    scanf(" %[^\n]", f.telefone); 
    printf("Digite o cargo do funcionario: ");
    scanf(" %[^\n]", f.cargo);  
    printf("Digite o salario do funcionario: ");
    scanf("%f", &f.salario);
    printf("Funcionario cadastrado com sucesso!\n");

    funcionarios[*totalFuncionarios] = f;
    (*totalFuncionarios)++;
}

// Função para Inicializar Quarto
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

// Função para calcular o valor da estadia
float calcularValorEstadia(int quantidadeDiarias, float valorDiaria) {
    return quantidadeDiarias * valorDiaria;
}

// Função para Cadastrar Estadia
void cadastrarEstadia(Estadia estadias[], int *totalEstadias, Cliente clientes[], int totalClientes, Quarto quartos[], int totalQuartos) {
    Estadia e;
    e.codigo = proximoCodigoEstadia++;

    printf("Codigo da estadia gerado automaticamente: %d\n", e.codigo);
    printf("Digite o codigo do cliente: ");
    scanf("%d", &e.codigoCliente);
    printf("Digite o numero do quarto (1-10): ");
    scanf("%d", &e.numeroQuarto);

    // Verificar se o cliente existe
    int clienteEncontrado = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].codigo == e.codigoCliente) {
            clienteEncontrado = 1;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    printf("Digite a quantidade de diarias: ");
    scanf("%d", &e.quantidadeDiarias);
    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", e.dataEntrada);
    printf("Digite o horario de entrada (hh:mm): ");
    scanf("%s", e.horarioEntrada);

    // Calcular a data de saída
    calcularDataSaida(e.dataEntrada, e.quantidadeDiarias, e.dataSaida);
    strcpy(e.horarioSaida, e.horarioEntrada); // Horário de saída igual ao de entrada

    // Verificar se o quarto está disponível
    if (!verificarDisponibilidade(estadias, *totalEstadias, e.numeroQuarto, e.dataEntrada, e.dataSaida, e.horarioEntrada, e.horarioSaida)) {
        printf("Erro: Quarto nao esta disponivel no intervalo solicitado.\n");
        return;
    }

    estadias[*totalEstadias] = e;
    (*totalEstadias)++;

    // Atualizar status do quarto para ocupado
    for (int i = 0; i < totalQuartos; i++) {
        if (quartos[i].numero == e.numeroQuarto) {
            strcpy(quartos[i].status, "ocupado");
            break;
        }
    }

    // Calcular e exibir o valor da estadia
    float valorEstadia = calcularValorEstadia(e.quantidadeDiarias, quartos[e.numeroQuarto - 1].valorDiaria);

    printf("Estadia cadastrada com sucesso!\n");
    printf("Data de saida calculada automaticamente: %s\n", e.dataSaida);
    printf("Horario de entrada e saida: %s\n", e.horarioEntrada);
    printf("Valor da estadia: R$%.2f\n", valorEstadia);
}

// Função para exibir reservas
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
        printf("Data de Entrada: %s\n", e.dataEntrada);
        printf("Horario de Entrada: %s\n", e.horarioEntrada);
        printf("Data de Saida: %s\n", e.dataSaida);
        printf("Horario de Saida: %s\n", e.horarioSaida);
        printf("----------------------------\n");
    }
}

// Função para exibir os valores da diária e quantidade máxima de hóspedes por quarto
void exibirInformacoesQuartos(Quarto quartos[], int totalQuartos) {
    printf("     Informacoes dos Quartos\n");
    printf("---------------------------------\n");
    for (int i = 0; i < totalQuartos; i++) {
        printf("Quarto Numero: %d\n", quartos[i].numero);
        printf("Quantidade Maxima de Hospedes: %d\n", quartos[i].quantidadeHospedes);
        printf("Valor da Diaria: R$%.2f\n", quartos[i].valorDiaria);
        printf("---------------------------------\n");
    }
}

// Função para salvar os dados em arquivos .txt
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

// Função Principal
int main() {
    Cliente clientes[MAX];
    Funcionario funcionarios[MAX];
    Estadia estadias[MAX];
    Quarto quartos[NUM_QUARTOS];

    int totalClientes = 0, totalFuncionarios = 0, totalEstadias = 0;

    inicializarQuartos(quartos);

    int opcao;
    do {
        printf("            Menu            \n");
        printf("----------------------------\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Estadia\n");
        printf("4. Exibir Reservas\n");
        printf("5. Informacoes dos Quartos\n");
        printf("6. Sair\n");
        printf("----------------------------\n");
        printf("Escolha uma opcao:\n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, &totalClientes);
                break;
            case 2:
                cadastrarFuncionario(funcionarios, &totalFuncionarios);
                break;
            case 3:
                cadastrarEstadia(estadias, &totalEstadias, clientes, totalClientes, quartos, NUM_QUARTOS);
                break;
            case 4:
                exibirReservas(estadias, totalEstadias, clientes, totalClientes);
                break;
            case 5:
                exibirInformacoesQuartos(quartos, NUM_QUARTOS);
                break;
            case 6:
                salvarDados(clientes, totalClientes, funcionarios, totalFuncionarios, estadias, totalEstadias, quartos, NUM_QUARTOS, proximoCodigoCliente, proximoCodigoFuncionario, proximoCodigoEstadia);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
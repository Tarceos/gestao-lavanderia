#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define MAX_PEDIDOS 10
#define PEDIDO_MAXLENGTH 71
#define NOME_MAXLENGTH 51
#define NOME_ARQUIVO "PEDIDOS_LAVAGEM.txt"

// structs

struct Item {
	int tipo_tecido;
	int cuidado_especial; // 0 1
};
struct Pacote {
	float peso_kg;
	struct Item item;
};
struct PedidoLavagem {
	char cliente[NOME_MAXLENGTH];
	char data_entrega[10];
	struct Pacote pct;
} Pedidos[MAX_PEDIDOS];

void create_order();
void read_order(char cliente[], int data[3], struct Pacote P);
void update_order(char cliente[], int data[3], struct Pacote P);
void delete_order(char cliente[], int data[3], struct Pacote P);

void structAssing();
void clearConsole();
void continue_program_request();
int check_archive(); // boolean 0 1
int orderlist_length();

// Variáveis globais

FILE *pedidos_lavagem;
int nPedidos, i; // número de pedidos e contador

// Código principal

int main() {
	SetConsoleOutputCP(CP_UTF8);
	clearConsole();

	int opcao;

    pedidos_lavagem = fopen(NOME_ARQUIVO, "r");
	check_archive();
	nPedidos = orderlist_length();
	structAssing();
	fclose(pedidos_lavagem);

	printf("Gestão de Lavanderia\n");
	printf("Insira a opção desejada:\n");
	printf("1.Criar um pedido;\n2.Ver pedidos existentes;\n3.Alterar um pedido;\n4.Remover um pedido;\n5.Fechar o programa.\n");

	scanf("%d", &opcao);
	while ( getchar() != '\n' );

	switch (opcao) {
        case 1:
            clearConsole();
            printf("%d\n", nPedidos);
            printf("Opção escolhida: 1.Criar um pedido.\n");
            if (nPedidos == MAX_PEDIDOS) {
                printf("Máximo de pedidos atingido.\n");
            } else {
                //create_order();
            }
            continue_program_request();
            break;
        case 2:
            clearConsole();
            printf("Opção escolhida: 2.Ver pedidos existentes.\n");
            if ( nPedidos == 0 ) {
                printf("Nenhum pedido encontrado.\n");
            } else {

            }
            continue_program_request();
            break;
        case 3:
            clearConsole();
            printf("Opção escolhida: 3.Alterar um pedido.\n");
            continue_program_request();
            break;
        case 4:
            clearConsole();
            printf("Opção escolhida: 4.Remover um pedido.\n");
            continue_program_request();
            break;
        case 5:
            printf("Opção escolhida: 5.Fechar o programa.\n");
            printf("Programa Fechado\n");
            return 0;
            break;
        default:
            printf("OPCÂO INVÁLIDA!\n");
            continue_program_request();
	}

	return main();
}

// funções

void structAssing() {
    char bufferC;
    int order_index = 0, contVirgu = 0;

    rewind(pedidos_lavagem);
    while ((bufferC = fgetc(pedidos_lavagem)) != EOF) {
        if (bufferC ==  ',') {
            contVirgu++;
        } else if (bufferC == '\n') {
            order_index++;
            contVirgu = 0;
        }

        switch (contVirgu) {
            case 0:
                Pedidos[order_index].
                break;
            case 1:
                printf("%d\n", order_index);
                break;
            case 2:
                printf("%d\n", order_index);                break;
            case 3:
                printf("%d\n", order_index);
                break;
            default:
                break;
        }
    }


    /*for ( i = 0 ; i < nPedidos ; i ++ ) {
        printf("teste");
        while ((bufferC = fgetc(pedidos_lavagem)) {
            printf("Achei uma virgula");
            if ( bufferC == "," ) {
            }
        }
    }*/

};

void clearConsole() {
    #ifdef _WIN32 // se caso for windows
        system("cls");
    #else
        system("clear");
    #endif
}

void continue_program_request() {
    printf("Aperte qualquer tecla para continuar:\t");
    while (1) { // assim que o usuário tecla algo o código retorna a si mesmo
        if (_kbhit()) {
            char tecla = _getch();
            break;
        }
    }
}

int check_archive() { // checa se o arquivo existe
    if (pedidos_lavagem == NULL) { // se o arquivo não existir cria um novo arquivo
        pedidos_lavagem = fopen(NOME_ARQUIVO, "w");
    }
}

int orderlist_length() { // conta o número de linhas/pedidos
    char buffer[PEDIDO_MAXLENGTH] = {0}; // buffer
    int n = 0;

    rewind(pedidos_lavagem);
    while ( fgets(buffer, PEDIDO_MAXLENGTH, pedidos_lavagem) != NULL ) {
        n++;
    }

    return n;
}

/*
void create_order() {
    if (nPedidos >= 10) {
        return printf("Máximo de pedidos atingidos.\n");
    }
    // printf("%d pedidos\n", nPedidos);

    pedidos_lavagem = fopen(NOME_ARQUIVO, "a+");
    fgets(Pedidos[nPedidos-1].cliente, sizeof(Pedidos[nPedidos].cliente), stdin);
    printf("%s", Pedidos[nPedidos-1].cliente);
    fclose(pedidos_lavagem);
    /*
    if (check_archive(pedidos_lavagem) == 1) { // se o arquivo for encontrado
        if (nPedidos >= MAX_PEDIDOS) { // checa se o máximo de pedidos foi atingido
            return printf("Número máximo de pedidos atingido.\n");
        }
        printf("%d pedidos  encontrados\n", nPedidos);
        fclose(pedidos_lavagem);

        // Criação do novo pedido
        pedidos_lavagem = fopen(NOME_ARQUIVO, "a+");
        fgets(teste, PEDIDO_MAXLENGTH, stdin);
        teste[strcspn(teste, "\n")] = '\0';
        printf("%s\n", teste);

        fclose(pedidos_lavagem);
    } else {
    return fclose(pedidos_lavagem);
    }
}*/


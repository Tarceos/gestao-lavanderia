#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

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
int check_archive(); // boolean 0 1
int orderlist_length();

// Variáveis globais

FILE *pedidos_lavagem;
int nPedidos, i; // número de pedidos e contador

int main() {
	SetConsoleOutputCP(CP_UTF8);

	int opcao;

    pedidos_lavagem = fopen(NOME_ARQUIVO, "r");
	check_archive();
	nPedidos = orderlist_length();
	fclose(pedidos_lavagem);
	//structAssing();

	printf("Gestão de Lavanderia\n");
	printf("Insira a opção desejada:\n");
	printf("1.Criar um pedido;\n2.Ver pedidos existentes;\n3.Alterar um pedido;\n4.Remover um pedido.\n");

	scanf("%d", &opcao);
	getchar();

	switch (opcao) {
    case 1:
       printf("%d", nPedidos);
        //create_order();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
	}

	return 0;
}
void structAssing() {
    char buffer[PEDIDO_MAXLENGTH] = {0};

    printf("teste");

    pedidos_lavagem = fopen(NOME_ARQUIVO, "r");
    for ( i = 0 ; i < nPedidos ; i++ ) {
        while ( fgets(buffer, PEDIDO_MAXLENGTH, pedidos_lavagem) != ",") {
            strncpy(Pedidos[i].cliente, buffer, NOME_MAXLENGTH);
        }
        printf("%s\n", Pedidos[i].cliente);
    }
    fclose(pedidos_lavagem);
};

int check_archive() { // checa se o arquivo existe
    if (pedidos_lavagem == NULL) { // se o arquivo não existir cria um novo arquivo
        pedidos_lavagem = fopen(NOME_ARQUIVO, "w");
    }
}

int orderlist_length() { // conta o número de linhas/pedidos
    char c[PEDIDO_MAXLENGTH] = {0}; // buffer
    int n = 0;

    while ( fgets(c, PEDIDO_MAXLENGTH, pedidos_lavagem) != NULL ) {
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


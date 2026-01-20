#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_PEDIDOS 10
#define LINHA_MAXLENGTH 51
// esse valor é temporário
#define NOME_ARQUIVO "PEDIDOS_LAVAGEM.txt"

// structs

struct Item {
	int tipo_tecido;
	int cuidado_especial; // 0 1
};
struct Pacote {
	float peso_kg;
	struct Item;
};
struct PedidoLavagem {
	char cliente[51];
	int data_entrega[3];
	struct Pacote;
} Pedidos[MAX_PEDIDOS];

void create_order();
void read_order(char cliente[], int data[3], struct Pacote P);
void update_order(char cliente[], int data[3], struct Pacote P);
void delete_order(char cliente[], int data[3], struct Pacote P);

int check_archive(FILE *file); // boolean 0 1
int orderlist_length(FILE *file);

// Variáveis globais

FILE *pedidos_lavagem;

int main() {
	SetConsoleOutputCP(CP_UTF8);

	int opcao;

	printf("Gestão de Lavanderia\n");
	printf("Insira a opção desejada:\n");
	printf("1.Criar um pedido;\n2.Ver pedidos existentes;\n3.Alterar um pedido;\n4.Remover um pedido.\n");

	scanf("%d", &opcao);

	switch (opcao) {
    case 1:
        create_order();
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

create_order() {
    if (check_archive(pedidos_lavagem) == 1) { // se o arquivo for encontrado
        if (orderlist_length(pedidos_lavagem) > MAX_PEDIDOS) { // checa se o máximo de pedidos foi atingido
            return printf("Número máximo de pedidos atingido.\n");
        }
        printf("%d pedidos  encontrados\n", orderlist_length(pedidos_lavagem));

        // Criação do novo pedido
        // no próximo commit
    }
}

check_archive(FILE *file) { // checa se o arquivo existe
    file = fopen(NOME_ARQUIVO, "r");
    if (file == NULL) {
        printf("Arquivo não encontrado");

        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

orderlist_length(FILE *file) { // conta o número de linhas/pedidos
    int nPedidos = 0; // número de pedidos
    int c[LINHA_MAXLENGTH]; // buffer

    if (check_archive(file) == 1) { // se o arquivo for encontrado
        file = fopen(NOME_ARQUIVO, "r");
        while ( fgets(c, LINHA_MAXLENGTH, file) != NULL ) {
            nPedidos++;
        }
        fclose(file);

        return nPedidos;
    }

    return 0;
}

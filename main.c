#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_PEDIDOS 10

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

void create_order(char cliente[], int data[3], struct Pacote P);
void read_order(char cliente[], int data[3], struct Pacote P);
void update_order(char cliente[], int data[3], struct Pacote P);
void delete_order(char cliente[], int data[3], struct Pacote P);

int main() {
	SetConsoleOutputCP(CP_UTF8);

	FILE *pedidos_lavagem;
	char texto[256];
	// abre o arquivo em modo de leitura e imprime seu conteúdo na tela
	pedidos_lavagem = fopen("PEDIDOS_LAVAGEM.txt", "r");

	while ( fgets(texto , 256, pedidos_lavagem) != NULL ) {
		printf("%s", texto);
	}

	return 0;
}

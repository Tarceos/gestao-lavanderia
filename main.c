#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h> // kbhit
#include <ctype.h> // tolower()

#define MAX_PEDIDOS 10
#define PEDIDO_MAXLENGTH 71 // Número máximo de caracteres que um pedido pode possuir (contando com o '\n')
#define NOME_MAXLENGTH 51 // TAmanho máximo do nome de um cliente (50)
#define NOME_FILE "PEDIDOS_LAVAGEM.txt"

// structs

struct Item {
	char tipo_tecido;
	char cuidado_especial; // 0 1
};
struct Pacote {
	float peso_kg;
	struct Item item;
};
struct PedidoLavagem {
	char cliente[NOME_MAXLENGTH];
	char data_entrega[11];
	struct Pacote pct;
} Pedidos[MAX_PEDIDOS];

// Declaração de funções e variáveis globais

void create_order(); // Atribui uma nova struct ao array pedidos
void read_order(); // Lê cada struct da lista até nPedidos, formata e imprime visualmente
void update_order(); // Com o arquivo em branco, escreve os dados atuais de Pedidos até nPedidos
void delete_order(int order_index); // Recebe o índice+1 de um pedido e o apaga de Pedidos

void edit_order(int order_index, int value_code); // recebe o índice+1 de um pedido e um código para alterar um valor específico
void enum_order(); // mostra visualmente os pedidos de maneira mais simples

void structAssing(); // Atribui oa dados do arquivo à struct no início do código
void clearConsole(); // Limpa o console independente de ser linux ou windows
void continue_program_request(); // Ao user finalizar uma ação, captura qualquer tecla do teclado e continua o programa
int check_archive(); // Checa se o arquivo existe e, se não existir, cria um novo
int orderlist_length(); // conta quantos pedidos há no arquivo através do número de linhas

FILE *pedidos_lavagem;
int nPedidos, i; // número de pedidos e contador

// Código principal

int main() {
	SetConsoleOutputCP(CP_UTF8);

	int opcao;

    pedidos_lavagem = fopen(NOME_FILE, "r");
	check_archive(); // checa se o arquivo existe e se não existir cria um novo
	nPedidos = orderlist_length(); // conta o número de linhas ( cada linha é um pedido )
	structAssing(); // atribui cada informação de um pedido à sua respectiva struct
	fclose(pedidos_lavagem);

	while(1) { // loop infinito do menu
	    clearConsole();

        printf("Gestão de Lavanderia\n");
        printf("1.Criar um pedido;\n2.Ver pedidos existentes;\n3.Alterar um pedido;\n4.Remover um pedido;\n5.Fechar o programa.\n");
        printf("Insira a opção desejada:\n>\t");

        opcao = fgetc(stdin);
	    while(getchar() != '\n');

        switch (opcao) {
            case '1': // create
                clearConsole();

                printf("Opção escolhida: 1.Criar um pedido.\n");
                if (nPedidos == MAX_PEDIDOS) {
                    printf("Máximo de pedidos atingido.\n");
                } else {
                    create_order();
                    nPedidos++;

                    pedidos_lavagem = fopen(NOME_FILE, "w");
                    update_order();
                    fclose(pedidos_lavagem);
                }
                continue_program_request();
                break;
            case '2': // read
                clearConsole();

                printf("Opção escolhida: 2.Ver pedidos existentes.\n");
                if ( nPedidos == 0 ) {
                    printf("Nenhum pedido encontrado.\n");
                } else {
                    read_order();
                }
                continue_program_request();
                break;
            case '3': // edit ( Não existe "edit" em "crud", mas aí nós inventa o "crudE" )
                clearConsole();

                printf("Opção escolhida: 3.Alterar um pedido.\n");
                if ( nPedidos == 0 ) {
                    printf("Nenhum pedido encontrado.\n");
                } else {
                    enum_order();
                    printf("Escolha um pedido>\t");
                    while ( scanf("%d", &escolha) != 1 || escolha < 1 || escolha > nPedidos ) {
                        while ( getchar() != '\n' );
                        printf("Insira um valor válido!\n");
                    }
                    while ( getchar() != '\n' );
                    printf("C - nome do CLIENTE;\nD - DATA DE ENTREGA;\nP - PESO (EM KG);\n")
                    printf("Insira ")
                }
                continue_program_request();
                break;
            case '4': ; // delete
                int escolha;

                clearConsole();

                printf("Opção escolhida: 4.Remover um pedido.\n");
                if ( nPedidos == 0 ) {
                    printf("Nenhum pedido encontrado.\n");
                } else {
                    enum_order();
                    printf("Escolha um pedido>\t");
                    while ( scanf("%d", &escolha) != 1 || escolha < 1 || escolha > nPedidos ) {
                        while ( getchar() != '\n' );
                        printf("Insira um valor válido!\n");
                    }
                    while ( getchar() != '\n' );

                    delete_order(escolha);

                    pedidos_lavagem = fopen(NOME_FILE, "w");
                    update_order();
                    fclose(pedidos_lavagem);
                }
                continue_program_request();
                break;
            case '5':
                printf("Opção escolhida: 5.Fechar o programa.\n");
                printf("Programa Fechado\n");
                return 0;
                break;
            default:
                printf("OPCÂO INVÁLIDA!\n");
                continue_program_request();
                break;
        }
	}

	return 0;
}

// funções

void create_order() {
    // nome do cliente
    printf("Insira o NOME do cliente\n>\t");
    fgets(Pedidos[nPedidos].cliente, NOME_MAXLENGTH, stdin);
    Pedidos[nPedidos].cliente[strcspn(Pedidos[nPedidos].cliente, "\n")] = 0;
    printf("%s", Pedidos[nPedidos].cliente);

    // data de entrega
    printf("Insira a DATA DE ENTREGA\n");
    printf("(Formato dd/mm/aaaa)\n>\t");
    fgets(
          Pedidos[nPedidos].data_entrega,
          sizeof(Pedidos[nPedidos].data_entrega),
          stdin
    );
    Pedidos[nPedidos].data_entrega[strcspn(Pedidos[nPedidos].data_entrega, "\n")] = 0;
    printf("%s\n", Pedidos[nPedidos].data_entrega);

    // Peso do pedido
    printf("Insira o PESO EM KG do pedido\n>\t");
    scanf("%f", &Pedidos[nPedidos].pct.peso_kg);
    while(getchar() != '\n');
    printf("%.2f\n", Pedidos[nPedidos].pct.peso_kg);

    // tipo do tecido
    printf("Insira o TIPO DE TECIDO\n");
    printf("Insira M para moletom;\nInsira J para jeans;\nInsira P para poliéster;\nInsira A para algodão;\nInsira L para linho.\n>\t");
    Pedidos[nPedidos].pct.item.tipo_tecido = fgetc(stdin);
    while(getchar() != '\n');
    printf("%c\n", Pedidos[nPedidos].pct.item.tipo_tecido);

    // cuidado especial
    printf("Cuidado especial será nescessário?\n");
    printf("(S - sim, Qualquer outro valor - não)\t>\t");
    Pedidos[nPedidos].pct.item.cuidado_especial = fgetc(stdin);
    while(getchar() != '\n');
    printf("%c\n", Pedidos[nPedidos].pct.item.cuidado_especial);
}

void read_order() {
    for ( i = 0 ; i < nPedidos ; i++ ) {
        char tipoT[51] = "";

        printf("=== Pedido %d ===\n", i+1);
        printf("Cliente: %s;\n", Pedidos[i].cliente);
        printf("Data de entrega: %s;\n", Pedidos[i].data_entrega);
        printf("Peso: %.2f;\n", Pedidos[i].pct.peso_kg);
        switch (tolower(Pedidos[i].pct.item.tipo_tecido)) {
            case 'm':
                strcat(tipoT, "Moletom");
                break;
            case 'j':
                strcat(tipoT, "Jeans");
                break;
            case 'p':
                strcat(tipoT, "Poliéster");
                break;
            case 'a':
                strcat(tipoT, "Algodão");
                break;
            case 'l':
                strcat(tipoT, "Linho");
                break;
            default:
                strcat(tipoT, "Exótico");
                break;
        }
        printf("Tipo de tecido: %s;\n", tipoT);

        if (tolower(Pedidos[i].pct.item.cuidado_especial) == 's') {
            printf("Precisa de cuidado especial.\n");
        } else {
            printf("Não precisa de cuidado especial.\n");
        }
        printf("\n");
    }
}

void update_order() {
    for ( i = 0 ; i < nPedidos ; i++ ) {
        fprintf(pedidos_lavagem,
            "%s|%s|%.2f|%c|%c\n",
            Pedidos[i].cliente,
            Pedidos[i].data_entrega,
            Pedidos[i].pct.peso_kg,
            Pedidos[i].pct.item.tipo_tecido,
            Pedidos[i].pct.item.cuidado_especial
        );
    }
}

void delete_order(int order_index) {
    for ( i = order_index-1 ; i < nPedidos ; i++ ) {
        Pedidos[i] = Pedidos[i+1];
    }
    nPedidos--;
    memset(&Pedidos[nPedidos], 0, sizeof(Pedidos[nPedidos]));
}

void enum_order() {
    printf("Lista de pedidos:\n");
    for ( i = 0 ; i < nPedidos ; i++ ) {
        printf("=== Pedido %d ===\n", i+1);
        printf("Cliente: %s. | ", Pedidos[i].cliente);
        printf("Data de entrega: %s.\n", Pedidos[i].data_entrega);
        printf("\n");
    }
}

void structAssing() {
    char buffer[70] = {0};
    int orderCount = 0;

    rewind(pedidos_lavagem);
    while ( fgets(buffer, sizeof(buffer), pedidos_lavagem) != NULL) {
        struct PedidoLavagem p;
        sscanf(buffer,
               "%50[^|]|%10[^|]|%f|%c|%c",
               p.cliente,
               p.data_entrega,
               &p.pct.peso_kg,
               &p.pct.item.tipo_tecido,
               &p.pct.item.cuidado_especial
        );
        if ( orderCount < MAX_PEDIDOS) {
            Pedidos[orderCount] = p;
            orderCount++;
        }
    }
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
        pedidos_lavagem = fopen(NOME_FILE, "w");
        fclose(pedidos_lavagem);
        pedidos_lavagem = fopen(NOME_FILE, "r");
        return 0;
    }
    return 1;
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


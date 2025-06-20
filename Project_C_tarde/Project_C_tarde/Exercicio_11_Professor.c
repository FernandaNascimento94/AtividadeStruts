#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int id;
	char nome[30];
	float precoCompra;
	float precoVenda;
} Fruta;

typedef struct {
	int id;
	int idFruta;
	int quantidade;
	float desconto;
} Compra;

typedef struct {
	int id;
	int idFruta;
	int quantidade;
	float desconto;
} Venda;

Fruta* frutas = NULL;
Compra* compras = NULL;
Venda* vendas = NULL;

int quantidadeFrutas = 0;
int quantidadeCompras = 0;
int quantidadeVendas = 0;


void adicionarFruta()
{
	Fruta fruta;
	fruta.id = quantidadeFrutas + 1;

	printf("Digite o nome da fruta: ");					scanf_s("%s", fruta.nome, 30);
	printf("Digite o preço de compra da fruta: ");		scanf_s("%f", &fruta.precoCompra);
	printf("Digite o preço de venda da fruta: ");		scanf_s("%f", &fruta.precoVenda);

	if (quantidadeFrutas > 0)
	{
		//Realocando todas as listas em variáveis temporárias...
		//verificando as listas pra evitar tentar inserir dados em listas inválidas.		
		Fruta* bufferFrutas = (Fruta*)realloc(frutas, (quantidadeFrutas + 1) * sizeof(Fruta));
		if (bufferFrutas == NULL) { printf("Deu ruim!"); return; }
		frutas = bufferFrutas;
	}

	frutas[quantidadeFrutas] = fruta;
	quantidadeFrutas++;
}

bool frutaValida(int idFruta)
{
	for (int i = 0; i < quantidadeFrutas; i++)
	{
		if (idFruta == frutas[i].id) return true;
	}
	return false;
}

int quantidadeComprada(int idFruta)
{
	int quantidadeComprada = 0;
	for (int i = 0; i < quantidadeCompras; i++)
	{
		if (compras[i].idFruta == idFruta) quantidadeComprada += compras[i].quantidade;
	}
	return quantidadeComprada;
}

int quantidadeVendida(int idFruta)
{
	int quantidadeVendida = 0;
	for (int i = 0; i < quantidadeVendas; i++)
	{
		if (vendas[i].idFruta == idFruta) quantidadeVendida += vendas[i].quantidade;
	}
	return quantidadeVendida;
}

float lucro(int idFruta)
{
	float pc = 0;
	float pv = 0;
	for (int i = 0; i < quantidadeFrutas; i++)
	{
		if (idFruta == frutas[i].id)
		{
			pc = frutas[i].precoCompra;
			pv = frutas[i].precoVenda;
		}
	}

	int qc = quantidadeComprada(idFruta);
	int qv = quantidadeVendida(idFruta);

	float lucro = (pv * qv) - (pc * qc);
	return lucro;
}

int estoque( int idFruta)
{
	int qc = quantidadeComprada(idFruta);
	int qv = quantidadeVendida(idFruta);
	int estoque = qc - qv;
	return estoque;
}

void comprar()
{
	Compra compra;
	printf("Digite o id da fruta a ser comprada:\n");
	scanf_s("%d", &compra.idFruta);
	printf("Digite a quantidade a ser comprada:\n");
	scanf_s("%d", &compra.quantidade);
	printf("Digite o valor de desconto (ou 0 se não foi condedido desconto):\n");
	scanf_s("%f", &compra.desconto);

	if (!frutaValida(compra.idFruta)) { printf("ERRO: Não existe fruta cadastrada com o id fornecido!"); return; }
	if (compra.quantidade <= 0) { printf("ERRO: quantidade inválida.");		return; }
	if (compra.desconto < 0) { printf("ERRO: desconto inválido."); return; }

	if (quantidadeCompras > 0)
	{
		Compra* bufferCompras = realloc(compras, (quantidadeCompras + 1) * sizeof(Compra));
		if (bufferCompras == NULL) { printf("Deu ruim!"); return; }
		compras = bufferCompras;
	}

	compra.id = quantidadeCompras + 1;
	compras[quantidadeCompras] = compra;
	quantidadeCompras++;
}

void vender()
{
	Venda venda;
	printf("Digite o id da fruta a ser vendida:\n");
	scanf_s("%d", &venda.idFruta);
	printf("Digite a quantidade a ser vendida:\n");
	scanf_s("%d", &venda.quantidade);
	printf("Digite o valor de desconto (ou 0 se não foi condedido desconto):\n");
	scanf_s("%f", &venda.desconto);

	if (!frutaValida(venda.idFruta)) { printf("ERRO: Não existe fruta cadastrada com o id fornecido!"); return; }
	if (venda.quantidade <= 0) { printf("ERRO: quantidade inválida.");		return; }
	if (venda.desconto < 0) { printf("ERRO: desconto inválido."); return; }

	if (quantidadeVendas > 0)
	{
		Venda* bufferVendas = realloc(vendas, (quantidadeVendas + 1) * sizeof(Venda));
		if (bufferVendas == NULL) { printf("Deu ruim!"); return; }
		vendas = bufferVendas;
	}

	venda.id = quantidadeVendas + 1;
	vendas[quantidadeVendas] = venda;
	quantidadeVendas++;
}

void listarFrutas()
{
	printf("----------------------------------------------------------------------------------------\n");
	printf("Listando Frutas\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("               Fruta |  pCompra |  pVenda |  qtdCompra |  qtdVenda |  Estoque |  Lucro |\n");
	for (int i = 0; i < quantidadeFrutas; i++)
	{
		Fruta fruta = frutas[i];
		printf("%20s | ", fruta.nome);
		printf("%5.2f  | ", fruta.precoCompra);
		printf("%5.2f  | ", fruta.precoVenda);
		printf("     %05d  | ", quantidadeComprada(fruta.id));
		printf("    %05d  | ", quantidadeVendida(fruta.id));
		printf("   %05d  | ", estoque(fruta.id));
		printf(" %5.2f |\n", lucro(fruta.id));
	}
}

int main()
{
	frutas = (Fruta*)malloc(sizeof(Fruta));

	int rodando = 1;
	int option = 0;
	while (rodando)
	{
		printf("------------------------------------------------------------------------------------\n");
		printf("Listagem de Frutas\n");
		printf("------------------------------------------------------------------------------------\n");
		printf("1 - Adicionar Fruta\n");
		printf("2 - Comprar\n");
		printf("3 - Vender\n");
		printf("4 - Listar Frutas\n");
		printf("5 - Sair\n");

		scanf_s("%d", &option);

		if (option == 1) adicionarFruta();
		if (option == 2) comprar();
		if (option == 3) vender();
		if (option == 4) listarFrutas();
		if (option == 5) rodando = 0;
	}
	return 0;
}
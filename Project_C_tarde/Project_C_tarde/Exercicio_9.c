#include <stdio.h>
#include <stdlib.h>

char** frutas;
float* precosCompra;
float* precosVenda;
int* quantidadeCompra;
int* quantidadeVenda;

int quantidade = 0;

void adicionarFrutas()
{
	char* fruta = (char*)malloc(30);
	float precoC;
	float precoV;
	int qtdC;
	int qtdV;

	printf("Digite o nome da fruta: ");
	scanf_s("%s", fruta, 30);

	printf("Digite o preco de compra: ");
	scanf_s("%f", &precoC);

	printf("Digite o preco de venda: ");
	scanf_s("%f", &precoV);

	printf("Digite a quantidade Comprada: ");
	scanf_s("%d", &qtdC);

	printf("Digite a quantidade Vendida: ");
	scanf_s("%d", &qtdV);

	if (quantidade == 0)
	{
		frutas = (char**)malloc(sizeof(char*));
		precosCompra = (float*)malloc(sizeof(float));
		precosVenda = (float*)malloc(sizeof(float));
		quantidadeCompra = (int*)malloc(sizeof(int));
		quantidadeVenda = (int*)malloc(sizeof(int));
	}
	else
	{
		frutas = (char**)realloc(frutas, (quantidade + 1) * sizeof(char*));
		precosCompra = (float*)realloc(precosCompra, (quantidade + 1) * sizeof(float));
		precosVenda = (float*)realloc(precosVenda, (quantidade + 1) * sizeof(float));
		quantidadeCompra = (int*)realloc(quantidadeCompra, (quantidade + 1) * sizeof(int));
		quantidadeVenda = (int*)realloc(quantidadeVenda, (quantidade + 1) * sizeof(int));
	}

	if (frutas == NULL || precosCompra == NULL || precosVenda == NULL || quantidadeCompra == NULL || quantidadeVenda == NULL)
	{
		printf("Deu ruim!"); return;
	}

	frutas[quantidade] = fruta;
	precosCompra[quantidade] = precoC;
	precosVenda[quantidade] = precoV;
	quantidadeCompra[quantidade] = qtdC;
	quantidadeVenda[quantidade] = qtdV;
	quantidade++;
}

void listarFrutas()
{
	printf("--------------------Listando Frutas---------------------\n");
	for (int i = 0; i < quantidade; i++)
	{
		int estoque = quantidadeCompra[i] - quantidadeVenda[i];
		float lucro = (precosVenda[i] * quantidadeVenda[i]) - (quantidadeCompra[i] * precosCompra[i]);
		printf("Fruta: %s\n", frutas[i]);
		printf("Preco de Compra: %.2f\n", precosCompra[i]);
		printf("Preco de Venda: %.2f\n", precosVenda[i]);
		printf("Quantidade Comprada: %d\n", quantidadeCompra[i]);
		printf("Quantidade Vendida: %d\n", quantidadeVenda[i]);
		printf("Estoque Atual: %d\n", estoque);
		printf("Lucro: %.2f\n", lucro);
	}
}

void main()
{
	int rodando = 1;
	int option = 0;
	while (rodando)
	{
		printf("--------------------Listagem de Frutas------------------\n");
		printf("------------------ 1 - Adicionar Fruta------------------\n");
		printf("------------------ 2 - Listar Frutas--------------------\n");
		printf("------------------ 3 - sair-----------------------------\n");
		scanf_s("%d", &option);

		system("cls");

		if (option == 1) adicionarFrutas();
		if (option == 2) listarFrutas();
		if (option == 3) rodando = 0;
	}
}
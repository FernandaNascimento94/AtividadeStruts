#include <stdio.h>

int main()
{
	int numeros[10];

	for (int i = 0; i < 10; i++)
	{
		int numero;
		printf("Digite um numero:\n");
		scanf_s("%d", &numero);
		numeros[i] = numero;
	}

	int soma = 0;
	for (int i = 0; i < 10; i++)
	{
		printf(" %d ", numeros[i]);
		soma += numeros[i];
	}

	printf("\n Soma: %d", soma);

	float media = (float)soma / 10;
	printf("\n Media: %.2f", media);
}
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int vetorNumeros[3] = { 18,21,36 };
	vetorNumeros[0] = 18;
	vetorNumeros[1] = 21;
	vetorNumeros[2] = 36;
	printf("vetorNumeros %d %d %d\n", vetorNumeros[0], vetorNumeros[1], vetorNumeros[2]);


	int quantidadeNumeros = 3;
	int* listaNumeros = malloc(quantidadeNumeros * sizeof(int));

	listaNumeros[0] = 16;
	listaNumeros[1] = 25;
	listaNumeros[2] = 38;
	printf("listaNumeros %d %d %d\n", listaNumeros[0], listaNumeros[1], listaNumeros[2]);


	quantidadeNumeros = 4;
	listaNumeros = realloc(listaNumeros, quantidadeNumeros * sizeof(int));
	listaNumeros[3] = 68;
	printf("listaNumeros %d %d %d %d\n", listaNumeros[0], listaNumeros[1], listaNumeros[2], listaNumeros[3]);

	//limpar memoria
	free(listaNumeros);
}
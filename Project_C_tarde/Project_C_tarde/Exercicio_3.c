#include <stdio.h>
int main()
{
	int a;
	printf("Digite um numero (A):\n");
	scanf_s("%d", &a);

	int b;
	printf("Digite um numero (B):\n");
	scanf_s("%d", &b);

	int c = a + b;
	printf("A soma desses dois numeros: %d\n", c);
}
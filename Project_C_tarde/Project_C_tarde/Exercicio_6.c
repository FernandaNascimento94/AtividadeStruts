#include <stdio.h>

int main()
{
	int a = 10;
	int* b = &a;
	int c = *b;

	printf("Um inteiro ocupa %d bytes de memoria\n", sizeof(int));
	printf("Um ponteiro para inteiro ocupa %d bytes na memoria\n", sizeof(int*));
	printf("O valor de a: %d\n", a);
	printf("O valor de b: %p\n", b);
	printf("O valor de c: %d\n", c);
}
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais
int* valores = NULL;
int quantidade = 0;

// Função para adicionar valor ao vetor
int adicionar_valor(int novo_valor)
{
    int* novo_vetor;
    if (quantidade == 0) { novo_vetor = (int*)malloc(sizeof(int)); }
    else { novo_vetor = (int*)realloc(valores, (quantidade + 1) * sizeof(int)); }

    //Falha na alocação
    if (novo_vetor == NULL) { return 0; }

    valores = novo_vetor;
    valores[quantidade] = novo_valor;
    quantidade++;
    return 1; // Sucesso
}

int main()
{
    int valor = 0;
    int soma = 0;

    printf("Cadastro de valores inteiros:\n");

    char resposta = 's';
    while (tolower(resposta) == 's')
    {
        printf("Digite um valor inteiro: ");
        scanf_s("%d", &valor);

        if (!adicionar_valor(valor))
        {
            printf("Erro ao adicionar valor.\n");
            free(valores);
            return 1;
        }

        soma += valor;

        printf("Deseja inserir outro valor? (s/n): ");

        resposta = getchar();
        // Limpa o buffer e lê a resposta
        while (resposta == '\n' || resposta == ' ')
        {
            resposta = getchar();
        }
    }

    if (quantidade == 0)
    {
        printf("Nenhum valor foi inserido.\n");
        return 0;
    }

    float media;
    media = (float)soma / quantidade;
    printf("\nValores inseridos:\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("%d ", valores[i]);
    }
    printf("\nMedia dos %d valores: %.2f\n", quantidade, media);
    free(valores);
    return 0;
}
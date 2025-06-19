#include <stdio.h>
#include <stdlib.h>

int quantidade = 0;

typedef struct {
    char nome[30];
    float precoCompra;
    float precoVenda;
    int quantidadeComprada;
    int quantidadeVendida;
} Fruta;

Fruta* frutas = NULL;

void adicionarFruta() {
    Fruta fruta;
    printf("Digite o nome da fruta: ");               scanf_s("%s", fruta.nome,30);
    printf("Digite o preço de compra da fruta: ");    scanf_s("%f", &fruta.precoCompra);
    printf("Digite o preço de venda da fruta: ");     scanf_s("%f", &fruta.precoVenda);
    printf("Digite a quantidade comprada: ");         scanf_s("%d", &fruta.quantidadeComprada);
    printf("Digite a quantidade vendida: ");          scanf_s("%d", &fruta.quantidadeVendida);

    Fruta* novaLista_frutas = (Fruta*)realloc(frutas, (quantidade + 1) * sizeof(Fruta));
    if (novaLista_frutas == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    frutas[quantidade] = fruta;
    quantidade++;
}

void listarFrutas() {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Listando Frutas\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("               Fruta pCompra pVenda qtdCompra qtdVenda Estoque   Lucro\n");

    for (int i = 0; i < quantidade; i++) {
        Fruta fruta = frutas[i];
        int estoque = fruta.quantidadeComprada - fruta.quantidadeVendida;
        float lucro = (fruta.quantidadeVendida * fruta.precoVenda) - (fruta.quantidadeComprada * fruta.precoCompra);

        printf("%20s", fruta.nome);
        printf("   %5.2f ", fruta.precoCompra);
        printf("  %5.2f ", fruta.precoVenda);
        printf("     %05d ", fruta.quantidadeComprada);
        printf("    %05d ", fruta.quantidadeVendida);
        printf("   %05d ", estoque);
        printf(" %7.2f\n", lucro);
    }
}

int main() {
    int rodando = 1;
    int option = 0;

    while (rodando) {
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("Listagem de Frutas\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("1 - Adicionar Fruta\n");
        printf("2 - Listar Frutas\n");
        printf("3 - Sair\n");

        scanf_s("%d", &option);

        if (option == 1) adicionarFruta();
        if (option == 2) listarFrutas();
        if (option == 3) rodando = 0;
    }
    return 0;
}

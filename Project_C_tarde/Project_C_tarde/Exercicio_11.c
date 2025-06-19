#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strcpy

// --- Variáveis Globais para controle de IDs e contagem ---
int proximoIdFruta = 1; // Para gerar IDs únicos para as frutas
int proximoIdCompra = 1; // Para gerar IDs únicos para as compras
int proximoIdVenda = 1; // Para gerar IDs únicos para as vendas

int quantidadeFrutas = 0;
int quantidadeCompras = 0;
int quantidadeVendas = 0;

// --- Estrutura da Fruta (agora sem quantidades transacionais) ---
typedef struct {
    int id; // ID único para a fruta
    char nome[30];
    float precoCompra; // Preço unitário de compra
    float precoVenda;  // Preço unitário de venda
} Fruta;

// --- Estrutura para Compra ---
typedef struct {
    int id; // ID único da compra
    int idFruta; // ID da fruta comprada (chave estrangeira)
    int quantidade; // Quantidade de unidades compradas
    float desconto; // Desconto aplicado na compra (em valor absoluto, por exemplo)
} Compra;

// --- Estrutura para Venda ---
typedef struct {
    int id; // ID único da venda
    int idFruta; // ID da fruta vendida (chave estrangeira)
    int quantidade; // Quantidade de unidades vendidas
    float desconto; // Desconto aplicado na venda (em valor absoluto, por exemplo)
} Venda;

// --- Ponteiros Globais para as Listas Dinâmicas ---
Fruta* frutas = NULL;
Compra* compras = NULL;
Venda* vendas = NULL;

// --- Funções Auxiliares ---
// Função para encontrar uma fruta pelo ID
Fruta* encontrarFrutaPorId(int id) {
    for (int i = 0; i < quantidadeFrutas; i++) {
        if (frutas[i].id == id) {
            return &frutas[i];
        }
    }
    return NULL; // Fruta não encontrada
}

// --- Funções de Gerenciamento ---

void adicionarFruta() {
    Fruta novaFruta;
    printf("--- Adicionar Nova Fruta ---\n");
    printf("Digite o nome da fruta: ");
    scanf_s("%s", novaFruta.nome, 30);
    printf("Digite o preco unitario de compra da fruta: ");
    scanf_s("%f", &novaFruta.precoCompra);
    printf("Digite o preco unitario de venda da fruta: ");
    scanf_s("%f", &novaFruta.precoVenda);

    novaFruta.id = proximoIdFruta++; // Atribui um ID e incrementa

    Fruta* novaLista_frutas = (Fruta*)realloc(frutas, (quantidadeFrutas + 1) * sizeof(Fruta));
    if (novaLista_frutas == NULL) {
        printf("Erro ao alocar memoria para frutas!\n");
        return;
    }

    frutas = novaLista_frutas;
    frutas[quantidadeFrutas] = novaFruta;
    quantidadeFrutas++;
    printf("Fruta '%s' (ID: %d) adicionada com sucesso!\n", novaFruta.nome, novaFruta.id);
}

void listarFrutas() {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Listando Frutas Cadastradas\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-25s %-15s %-15s\n", "ID", "Nome", "Preco Compra", "Preco Venda");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    if (quantidadeFrutas == 0) {
        printf("Nenhuma fruta cadastrada ainda.\n");
        return;
    }

    for (int i = 0; i < quantidadeFrutas; i++) {
        Fruta fruta = frutas[i];
        printf("%-5d %-25s %-15.2f %-15.2f\n", fruta.id, fruta.nome, fruta.precoCompra, fruta.precoVenda);
    }
}

void registrarCompra() {
    if (quantidadeFrutas == 0) {
        printf("Nenhuma fruta cadastrada para registrar uma compra.\n");
        return;
    }

    listarFrutas(); // Mostra as frutas disponíveis
    printf("--- Registrar Nova Compra ---\n");
    printf("Digite o ID da fruta que foi comprada: ");
    int idFrutaComprada;
    scanf_s("%d", &idFrutaComprada);

    Fruta* frutaExistente = encontrarFrutaPorId(idFrutaComprada);
    if (frutaExistente == NULL) {
        printf("Erro: Fruta com ID %d não encontrada.\n", idFrutaComprada);
        return;
    }

    Compra novaCompra;
    novaCompra.idFruta = idFrutaComprada;
    printf("Digite a quantidade comprada de '%s': ", frutaExistente->nome);
    scanf_s("%d", &novaCompra.quantidade);
    printf("Digite o valor do desconto total da compra (0 se não houver): ");
    scanf_s("%f", &novaCompra.desconto);

    novaCompra.id = proximoIdCompra++; // Atribui um ID e incrementa

    Compra* novaLista_compras = (Compra*)realloc(compras, (quantidadeCompras + 1) * sizeof(Compra));
    if (novaLista_compras == NULL) {
        printf("Erro ao alocar memoria para compras!\n");
        return;
    }

    compras = novaLista_compras;
    compras[quantidadeCompras] = novaCompra;
    quantidadeCompras++;
    printf("Compra (ID: %d) de %d unidades de '%s' registrada com sucesso!\n",
        novaCompra.id, novaCompra.quantidade, frutaExistente->nome);
}

void registrarVenda() {
    if (quantidadeFrutas == 0) {
        printf("Nenhuma fruta cadastrada para registrar uma venda.\n");
        return;
    }

    listarFrutas(); // Mostra as frutas disponíveis
    printf("--- Registrar Nova Venda ---\n");
    printf("Digite o ID da fruta que foi vendida: ");
    int idFrutaVendida;
    scanf_s("%d", &idFrutaVendida);

    Fruta* frutaExistente = encontrarFrutaPorId(idFrutaVendida);
    if (frutaExistente == NULL) {
        printf("Erro: Fruta com ID %d nao encontrada.\n", idFrutaVendida);
        return;
    }

    Venda novaVenda;
    novaVenda.idFruta = idFrutaVendida;
    printf("Digite a quantidade vendida de '%s': ", frutaExistente->nome);
    scanf_s("%d", &novaVenda.quantidade);
    printf("Digite o valor do desconto total da venda (0 se não houver): ");
    scanf_s("%f", &novaVenda.desconto);

    novaVenda.id = proximoIdVenda++; // Atribui um ID e incrementa

    Venda* novaLista_vendas = (Venda*)realloc(vendas, (quantidadeVendas + 1) * sizeof(Venda));
    if (novaLista_vendas == NULL) {
        printf("Erro ao alocar memoria para vendas!\n");
        return;
    }

    vendas = novaLista_vendas;
    vendas[quantidadeVendas] = novaVenda;
    quantidadeVendas++;
    printf("Venda (ID: %d) de %d unidades de '%s' registrada com sucesso!\n",
        novaVenda.id, novaVenda.quantidade, frutaExistente->nome);
}

void listarCompras() {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Listando Compras Registradas\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-10s %-15s %-10s %-15s %-15s\n", "ID", "ID Fruta", "Nome Fruta", "Quantidade", "Desconto", "Custo Total");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    if (quantidadeCompras == 0) {
        printf("Nenhuma compra registrada ainda.\n");
        return;
    }

    for (int i = 0; i < quantidadeCompras; i++) {
        Compra compra = compras[i];
        Fruta* frutaAssociada = encontrarFrutaPorId(compra.idFruta);
        char nomeFruta[30] = "Desconhecida";
        float custoTotal = 0.0;

        if (frutaAssociada != NULL) {
            strcpy_s(nomeFruta, sizeof(nomeFruta), frutaAssociada->nome);
            custoTotal = (frutaAssociada->precoCompra * compra.quantidade) - compra.desconto;
        }

        printf("%-5d %-10d %-15s %-10d %-15.2f %-15.2f\n",
            compra.id, compra.idFruta, nomeFruta, compra.quantidade, compra.desconto, custoTotal);
    }
}

void listarVendas() {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Listando Vendas Registradas\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-10s %-15s %-10s %-15s %-15s\n", "ID", "ID Fruta", "Nome Fruta", "Quantidade", "Desconto", "Receita Total");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    if (quantidadeVendas == 0) {
        printf("Nenhuma venda registrada ainda.\n");
        return;
    }

    for (int i = 0; i < quantidadeVendas; i++) {
        Venda venda = vendas[i];
        Fruta* frutaAssociada = encontrarFrutaPorId(venda.idFruta);
        char nomeFruta[30] = "Desconhecida";
        float receitaTotal = 0.0;

        if (frutaAssociada != NULL) {
            strcpy_s(nomeFruta, sizeof(nomeFruta), frutaAssociada->nome);
            receitaTotal = (frutaAssociada->precoVenda * venda.quantidade) - venda.desconto;
        }

        printf("%-5d %-10d %-15s %-10d %-15.2f %-15.2f\n",
            venda.id, venda.idFruta, nomeFruta, venda.quantidade, venda.desconto, receitaTotal);
    }
}

void calcularEstoqueLucroGlobal() {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Resumo de Estoque e Lucro por Fruta\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-25s %-10s %-10s %-10s %-15s %-15s\n", "ID", "Nome Fruta", "Qtd Comp.", "Qtd Vend.", "Estoque", "Custo Total", "Receita Total");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    if (quantidadeFrutas == 0) {
        printf("Nenhuma fruta cadastrada para calcular estoque e lucro.\n");
        return;
    }

    for (int i = 0; i < quantidadeFrutas; i++) {
        Fruta fruta = frutas[i];
        int totalComprado = 0;
        int totalVendido = 0;
        float custoAcumulado = 0.0;
        float receitaAcumulada = 0.0;

        // Soma quantidades e custos das compras para esta fruta
        for (int j = 0; j < quantidadeCompras; j++) {
            if (compras[j].idFruta == fruta.id) {
                totalComprado += compras[j].quantidade;
                custoAcumulado += (fruta.precoCompra * compras[j].quantidade) - compras[j].desconto;
            }
        }

        // Soma quantidades e receitas das vendas para esta fruta
        for (int k = 0; k < quantidadeVendas; k++) {
            if (vendas[k].idFruta == fruta.id) {
                totalVendido += vendas[k].quantidade;
                receitaAcumulada += (fruta.precoVenda * vendas[k].quantidade) - vendas[k].desconto;
            }
        }

        int estoqueAtual = totalComprado - totalVendido;
        float lucroPrejuizo = receitaAcumulada - custoAcumulado;

        printf("%-5d %-25s %-10d %-10d %-10d %-15.2f %-15.2f\n",
            fruta.id, fruta.nome, totalComprado, totalVendido, estoqueAtual, custoAcumulado, receitaAcumulada);
    }

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Lucro/Prejuizo Liquido Global (Receita Total - Custo Total de todas as frutas)\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    float lucroLiquidoGlobal = 0.0;
    for (int i = 0; i < quantidadeFrutas; i++) {
        Fruta fruta = frutas[i];
        float custoAcumuladoFruta = 0.0;
        float receitaAcumuladaFruta = 0.0;

        for (int j = 0; j < quantidadeCompras; j++) {
            if (compras[j].idFruta == fruta.id) {
                custoAcumuladoFruta += (fruta.precoCompra * compras[j].quantidade) - compras[j].desconto;
            }
        }
        for (int k = 0; k < quantidadeVendas; k++) {
            if (vendas[k].idFruta == fruta.id) {
                receitaAcumuladaFruta += (fruta.precoVenda * vendas[k].quantidade) - vendas[k].desconto;
            }
        }
        lucroLiquidoGlobal += (receitaAcumuladaFruta - custoAcumuladoFruta);
    }
    printf("Lucro Liquido Total: %15.2f\n", lucroLiquidoGlobal);
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}


// --- Função para liberar memória alocada ---
void liberarMemoria() {
    free(frutas);
    free(compras);
    free(vendas);
    frutas = NULL;
    compras = NULL;
    vendas = NULL;
    printf("Memoria liberada.\n");
}

// --- Função Principal ---
int main() {
    int rodando = 1;
    int option = 0;

    while (rodando) {
        printf("\n------------------------------------------------------------------------------------------------------------------------\n");
        printf("Sistema de Gerenciamento de Frutas (Transacional)\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("1 - Adicionar Nova Fruta\n");
        printf("2 - Listar Frutas Cadastradas\n");
        printf("3 - Registrar Compra de Fruta\n");
        printf("4 - Registrar Venda de Fruta\n");
        printf("5 - Listar Compras Realizadas\n");
        printf("6 - Listar Vendas Realizadas\n");
        printf("7 - Calcular Estoque e Lucro por Fruta (Resumo)\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf_s("%d", &option);

        if (option == 1) adicionarFruta();
        if (option == 2) listarFrutas();
        if (option == 3) registrarCompra();
        if (option == 4) registrarVenda();
        if (option == 5) listarCompras();
        if (option == 6) listarVendas();
        if (option == 7) calcularEstoqueLucroGlobal();
        if (option == 8) rodando = 0;
    }

    liberarMemoria(); // Libera a memória antes de sair
    return 0;
}
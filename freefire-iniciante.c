#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função para inserir um item no inventário
void inserirItem(Item inventario[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\nCadastro de novo item\n");

    printf("Nome do item: ");
    scanf(" %29[^\n]", inventario[*totalItens].nome);

    printf("Tipo do item (arma, munição, cura...): ");
    scanf(" %19[^\n]", inventario[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &inventario[*totalItens].quantidade);

    (*totalItens)++;

    printf("\n✅ Item cadastrado com sucesso!\n");
}

// Função para listar todos os itens do inventário
void listarItens(Item inventario[], int totalItens) {
    if (totalItens == 0) {
        printf("\n🎒 Mochila vazia.\n");
        return;
    }

    printf("\n📦 Itens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade);
    }
}

// Função de busca sequencial por nome
void buscarItem(Item inventario[], int totalItens) {
    char nomeBusca[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para busca: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Tipo: %s\n", inventario[i].tipo);
            printf("Quantidade: %d\n", inventario[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
}

// Função para remover um item pelo nome
void removerItem(Item inventario[], int *totalItens) {
    char nomeRemover[30];
    int encontrado = 0;

    printf("\nDigite o nome do item a remover: ");
    scanf(" %29[^\n]", nomeRemover);

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            // Desloca os itens seguintes
            for (int j = i; j < *totalItens - 1; j++) {
                inventario[j] = inventario[j + 1];
            }

            (*totalItens)--;
            encontrado = 1;
            printf("\n🗑️ Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
}

int main() {
    Item inventario[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=== 🎮 INVENTÁRIO DO JOGADOR ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(inventario, &totalItens);
                listarItens(inventario, totalItens);
                break;

            case 2:
                removerItem(inventario, &totalItens);
                listarItens(inventario, totalItens);
                break;

            case 3:
                listarItens(inventario, totalItens);
                break;

            case 4:
                buscarItem(inventario, totalItens);
                break;

            case 0:
                printf("\n👋 Saindo do inventário...\n");
                break;

            default:
                printf("\n❌ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

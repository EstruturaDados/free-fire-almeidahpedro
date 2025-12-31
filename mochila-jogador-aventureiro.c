#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 20

/* =======================
   STRUCTS
   =======================*/

// Item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

/* =======================
   CONTADORES DE COMPARAÇÕES
   =======================*/
int compSeqVetor = 0;
int compBinVetor = 0;
int compLista = 0;

/* =======================
   FUNÇÕES - VETOR
   =======================*/

// Inserir item no vetor
void inserirItemVetor(Item vetor[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila (vetor) cheia.\n");
        return;
    }

    printf("Nome: ");
    scanf(" %29[^\n]", vetor[*total].nome);
    printf("Tipo: ");
    scanf(" %19[^\n]", vetor[*total].tipo);
    printf("Quantidade: ");
    scanf("%d", &vetor[*total].quantidade);

    (*total)++;
}

// Listar itens do vetor
void listarVetor(Item vetor[], int total) {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < total; i++) {
        printf("%s | %s | %d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].quantidade);
    }
}

// Remover item do vetor
void removerItemVetor(Item vetor[], int *total, char nome[]) {
    for (int i = 0; i < *total; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*total)--;
            printf("Item removido do vetor.\n");
            return;
        }
    }
    printf("Item não encontrado no vetor.\n");
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vetor[], int total, char nome[]) {
    compSeqVetor = 0;

    for (int i = 0; i < total; i++) {
        compSeqVetor++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor(Item vetor[], int total) {
    Item aux;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

// Busca binária no vetor
int buscarBinariaVetor(Item vetor[], int total, char nome[]) {
    int inicio = 0, fim = total - 1;
    compBinVetor = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        compBinVetor++;

        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/* =======================
   FUNÇÕES - LISTA ENCADEADA
   =======================*/

// Inserir item na lista
void inserirItemLista(No **inicio) {
    No *novo = (No *)malloc(sizeof(No));

    printf("Nome: ");
    scanf(" %29[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %19[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;
}

// Listar itens da lista
void listarLista(No *inicio) {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    while (inicio != NULL) {
        printf("%s | %s | %d\n",
               inicio->dados.nome,
               inicio->dados.tipo,
               inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

// Remover item da lista
void removerItemLista(No **inicio, char nome[]) {
    No *atual = *inicio;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista.\n");
}

// Busca sequencial na lista
No* buscarLista(No *inicio, char nome[]) {
    compLista = 0;

    while (inicio != NULL) {
        compLista++;
        if (strcmp(inicio->dados.nome, nome) == 0)
            return inicio;
        inicio = inicio->proximo;
    }
    return NULL;
}

// Liberar memória da lista
void liberarLista(No *inicio) {
    No *aux;
    while (inicio != NULL) {
        aux = inicio;
        inicio = inicio->proximo;
        free(aux);
    }
}

/* =======================
   MAIN
   =======================*/
int main() {
    Item vetor[MAX_ITENS];
    int totalVetor = 0;
    No *lista = NULL;

    int opcao;
    char nome[30];

    do {
        printf("\n=== MOCHILA DO JOGADOR ===\n");
        printf("1 - Inserir item (vetor)\n");
        printf("2 - Inserir item (lista)\n");
        printf("3 - Listar vetor\n");
        printf("4 - Listar lista\n");
        printf("5 - Buscar (sequencial vetor)\n");
        printf("6 - Buscar (binária vetor)\n");
        printf("7 - Buscar (lista)\n");
        printf("8 - Remover item (vetor)\n");
        printf("9 - Remover item (lista)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItemVetor(vetor, &totalVetor);
                break;

            case 2:
                inserirItemLista(&lista);
                break;

            case 3:
                listarVetor(vetor, totalVetor);
                break;

            case 4:
                listarLista(lista);
                break;

            case 5:
                printf("Nome: ");
                scanf(" %29[^\n]", nome);
                buscarSequencialVetor(vetor, totalVetor, nome);
                printf("Comparações (vetor sequencial): %d\n", compSeqVetor);
                break;

            case 6:
                ordenarVetor(vetor, totalVetor);
                printf("Nome: ");
                scanf(" %29[^\n]", nome);
                buscarBinariaVetor(vetor, totalVetor, nome);
                printf("Comparações (vetor binária): %d\n", compBinVetor);
                break;

            case 7:
                printf("Nome: ");
                scanf(" %29[^\n]", nome);
                buscarLista(lista, nome);
                printf("Comparações (lista): %d\n", compLista);
                break;

            case 8:
                printf("Nome: ");
                scanf(" %29[^\n]", nome);
                removerItemVetor(vetor, &totalVetor, nome);
                break;

            case 9:
                printf("Nome: ");
                scanf(" %29[^\n]", nome);
                removerItemLista(&lista, nome);
                break;

            case 0:
                liberarLista(lista);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

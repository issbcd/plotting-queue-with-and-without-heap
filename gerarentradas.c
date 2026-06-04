#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ============================================================
   ESTRUTURAS E FUNÇÕES — FILA SEM HEAP (lista encadeada)
   Menor valor = maior prioridade
   ============================================================ */

typedef struct node_lista 
{
    int prioridade;
    struct node_lista *next;
} node_lista;

typedef struct fila 
{
    node_lista *head;
} fila;

int eh_vazia_lista(fila *f)
{
    return f->head == NULL;
}

/* Insere em ordem crescente de prioridade. Retorna nº de comparações. */
int enqueue_lista(fila *f, int prioridade)
{
    int comparacoes = 0;

    node_lista *novo = (node_lista *)malloc(sizeof(node_lista));
    novo->prioridade = prioridade;
    novo->next = NULL;

    if (eh_vazia_lista(f)) 
    {
        f->head = novo;
        return comparacoes;
    }

    comparacoes++;
    if (prioridade < f->head->prioridade) 
    {
        novo->next = f->head;
        f->head = novo;
        return comparacoes;
    }

    node_lista *atual = f->head;
    while (atual->next != NULL) 
    {
        comparacoes++;
        if (atual->next->prioridade > prioridade)
            break;
        atual = atual->next;
    }

    novo->next = atual->next;
    atual->next = novo;

    return comparacoes;
}

int dequeue_lista(fila *f)
{
    if (eh_vazia_lista(f))
        return -1;

    node_lista *aux = f->head;
    int valor = aux->prioridade;
    f->head = f->head->next;
    free(aux);

    return valor;
}

/* ============================================================
   ESTRUTURAS E FUNÇÕES — FILA COM HEAP (min-heap via array)
   Menor valor = maior prioridade | Inserção O(log n)
   ============================================================ */

typedef struct node_heap 
{
    int prioridade;
} node_heap;

typedef struct heap 
{
    node_heap *elementos;
    int tamanho;
    int capacidade;
} heap;

heap *criarheap(int capacidade)
{
    heap *h = (heap *)malloc(sizeof(heap));
    h->elementos = (node_heap *)malloc(capacidade * sizeof(node_heap));
    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

int eh_vazia_heap(heap *h)
{
    return h->tamanho == 0;
}

void trocar(node_heap *a, node_heap *b)
{
    node_heap temp = *a;
    *a = *b;
    *b = temp;
}

/* insere no heap e sobe (heapify up). Retorna comparações. */
int enqueue_heap(heap *h, int prioridade)
{
    int comparacoes = 0;

    if (h->tamanho == h->capacidade) 
    {
        printf("Heap cheio!\n");
        return -1;
    }

    int i = h->tamanho;
    h->elementos[i].prioridade = prioridade;
    h->tamanho++;

    /* Heapify up */
    int pai = (i - 1) / 2;
    while (i != 0) 
    {
        comparacoes++;
        if (h->elementos[pai].prioridade > h->elementos[i].prioridade) 
        {
            trocar(&h->elementos[i], &h->elementos[pai]);
            i = pai;
            pai = (i - 1) / 2;
        } 
        
        else 
        {
            break;
        }
    }

    return comparacoes;
}

int dequeue_heap(heap *h)
{
    if (eh_vazia_heap(h))
    {
        return -1;
    }
        

    if (h->tamanho == 1) 
    {
        h->tamanho--;
        return h->elementos[0].prioridade;
    }

    int valor_removido = h->elementos[0].prioridade;
    h->elementos[0] = h->elementos[h->tamanho - 1];
    h->tamanho--;

    /* heapify down */
    int i = 0;
    while (1) 
    {
        int esq   = 2 * i + 1;
        int dir   = 2 * i + 2;
        int menor = i;

        if (esq < h->tamanho && h->elementos[esq].prioridade < h->elementos[menor].prioridade)
        {
            menor = esq;
        }
            
        if (dir < h->tamanho && h->elementos[dir].prioridade < h->elementos[menor].prioridade)
        {
            menor = dir;
        }
            

        if (menor != i) 
        {
            trocar(&h->elementos[i], &h->elementos[menor]);
            i = menor;
        } 
        
        else 
        {
            break;
        }
    }

    return valor_removido;
}

/* ============================================================
   MAIN — gera resultados.csv com comparações de cada abordagem
   ============================================================ */

int main()
{
    srand(time(NULL));

    FILE *arquivo = fopen("resultados.csv", "w");
    if (arquivo == NULL) 
    {
        printf("Erro ao criar o arquivo CSV!\n");
        return 1;
    }

    fprintf(arquivo, "Tamanho_Fila,Comparacoes_Sem_Heap,Comparacoes_Com_Heap\n");

    int passo = 1000;
    int max_elementos = 10000;

    printf("Gerando dados para o plot...\n");

    for (int tamanho_atual = passo; tamanho_atual <= max_elementos; tamanho_atual += passo)
    {
        /* inicializa estruturas */
        fila minha_lista;
        minha_lista.head = NULL;

        heap *meu_heap = criarheap(tamanho_atual);

        /* Sorteia os números uma única vez para ambas as estruturas */
        int *numeros_sorteados = (int *)malloc(tamanho_atual * sizeof(int));
        for (int i = 0; i < tamanho_atual; i++)
            numeros_sorteados[i] = rand() % 50000;

        int total_comp_lista = 0;
        int total_comp_heap  = 0;

        /* popula e acumula comparações */
        for (int i = 0; i < tamanho_atual; i++) 
        {
            total_comp_lista += enqueue_lista(&minha_lista, numeros_sorteados[i]);
            total_comp_heap  += enqueue_heap(meu_heap,      numeros_sorteados[i]);
        }

        fprintf(arquivo, "%d,%d,%d\n", tamanho_atual, total_comp_lista, total_comp_heap);
        printf("Tamanho: %d | Lista: %d comp. | Heap: %d comp.\n",
               tamanho_atual, total_comp_lista, total_comp_heap);

        /* limpeza de memória */
        free(numeros_sorteados);

        while (!eh_vazia_lista(&minha_lista))
            dequeue_lista(&minha_lista);

        free(meu_heap->elementos);
        free(meu_heap);
    }

    fclose(arquivo);
    printf("\nPronto! O arquivo 'resultados.csv' foi gerado.\n");

    return 0;
}
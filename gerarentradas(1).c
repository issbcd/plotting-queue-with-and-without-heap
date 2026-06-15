#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ============================================================
   ESTRUTURAS E FUNÇÕES — FILA SEM HEAP (lista encadeada)
   Menor valor = maior prioridade
   ============================================================ */

/**
 * @brief Nó da fila de prioridade sem heap (lista encadeada).
 */
typedef struct node_lista {
    int prioridade;        /**< Prioridade do elemento. */
    struct node_lista *next; /**< Ponteiro para o próximo nó. */
} node_lista;

/**
 * @brief Fila de prioridade implementada como lista encadeada ordenada.
 */
typedef struct fila {
    node_lista *head; /**< Ponteiro para o primeiro nó da fila. */
} fila;

/**
 * @brief Verifica se a fila (lista encadeada) está vazia.
 *
 * @param f Ponteiro para a fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int eh_vazia_lista(fila *f)
{
    return f->head == NULL;
}

/**
 * @brief Insere um elemento na fila em ordem crescente de prioridade.
 *
 * Percorre a lista para encontrar a posição correta e insere o novo nó,
 * mantendo a ordenação. A complexidade de inserção é O(n).
 *
 * @param f          Ponteiro para a fila onde o elemento será inserido.
 * @param prioridade Valor de prioridade do elemento (menor valor = maior prioridade).
 * @return Número de comparações realizadas durante a inserção.
 */
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

/**
 * @brief Remove e retorna o elemento de maior prioridade da fila (lista encadeada).
 *
 * Remove o primeiro nó e libera a memória alocada. A complexidade é O(1).
 *
 * @param f Ponteiro para a fila da qual o elemento será removido.
 * @return Valor de prioridade do elemento removido, ou -1 se a fila estiver vazia.
 */
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

/**
 * @brief Nó do min-heap.
 */
typedef struct node_heap {
    int prioridade; /**< Prioridade do elemento. */
} node_heap;

/**
 * @brief Fila de prioridade implementada como min-heap sobre um array.
 *
 * A relação pai-filho é definida implicitamente pelos índices:
 * pai de {@code i} em {@code (i-1)/2}; filhos em {@code 2i+1} e {@code 2i+2}.
 */
typedef struct heap {
    node_heap *elementos; /**< Array de nós que armazena o heap. */
    int tamanho;          /**< Número de elementos atualmente no heap. */
    int capacidade;       /**< Capacidade máxima do array. */
} heap;

/**
 * @brief Aloca e inicializa um heap vazio com a capacidade fornecida.
 *
 * @param capacidade Número máximo de elementos que o heap pode armazenar.
 * @return Ponteiro para o heap recém-criado.
 */
heap *criarheap(int capacidade)
{
    heap *h = (heap *)malloc(sizeof(heap));
    h->elementos = (node_heap *)malloc(capacidade * sizeof(node_heap));
    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

/**
 * @brief Verifica se o heap está vazio.
 *
 * @param h Ponteiro para o heap a ser verificado.
 * @return 1 se o heap estiver vazio, 0 caso contrário.
 */
int eh_vazia_heap(heap *h)
{
    return h->tamanho == 0;
}

/**
 * @brief Troca os valores de dois nós do heap.
 *
 * @param a Ponteiro para o primeiro nó.
 * @param b Ponteiro para o segundo nó.
 */
void trocar(node_heap *a, node_heap *b)
{
    node_heap temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Insere um elemento no heap e restaura a propriedade do min-heap (heapify up).
 *
 * O elemento é adicionado ao final do array e sobe enquanto sua prioridade
 * for menor que a do pai. A complexidade de inserção é O(log n).
 *
 * @param h          Ponteiro para o heap onde o elemento será inserido.
 * @param prioridade Valor de prioridade do elemento (menor valor = maior prioridade).
 * @return Número de comparações realizadas, ou -1 se o heap estiver cheio.
 */
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

    /* Heapify up: reposiciona o elemento recém-inserido subindo na árvore. */
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

/**
 * @brief Remove e retorna o elemento de maior prioridade do heap (heapify down).
 *
 * A raiz (menor valor) é removida; o último elemento ocupa seu lugar e desce
 * na árvore até restaurar a propriedade do min-heap. A complexidade é O(log n).
 *
 * @param h Ponteiro para o heap do qual o elemento será removido.
 * @return Valor de prioridade do elemento removido, ou -1 se o heap estiver vazio.
 */
int dequeue_heap(heap *h)
{
    if (eh_vazia_heap(h))
        return -1;

    if (h->tamanho == 1)
    {
        h->tamanho--;
        return h->elementos[0].prioridade;
    }

    int valor_removido = h->elementos[0].prioridade;
    h->elementos[0] = h->elementos[h->tamanho - 1];
    h->tamanho--;

    /* Heapify down: desce a nova raiz até sua posição correta. */
    int i = 0;
    while (1)
    {
        int esq   = 2 * i + 1;
        int dir   = 2 * i + 2;
        int menor = i;

        if (esq < h->tamanho && h->elementos[esq].prioridade < h->elementos[menor].prioridade)
            menor = esq;

        if (dir < h->tamanho && h->elementos[dir].prioridade < h->elementos[menor].prioridade)
            menor = dir;

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

/**
 * @brief Ponto de entrada do programa.
 *
 * Gera o arquivo {@code resultados.csv} com o total de comparações de cada
 * abordagem (lista encadeada e heap) para filas de 1.000 a 10.000 elementos
 * (passo de 1.000). Para cada tamanho, os mesmos números aleatórios são
 * inseridos nas duas estruturas, garantindo comparação justa.
 *
 * @return 0 em caso de sucesso, 1 se o arquivo CSV não puder ser criado.
 */
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
        /* Inicializa as estruturas para este tamanho de teste. */
        fila minha_lista;
        minha_lista.head = NULL;

        heap *meu_heap = criarheap(tamanho_atual);

        /* Sorteia os números uma única vez para uso em ambas as estruturas. */
        int *numeros_sorteados = (int *)malloc(tamanho_atual * sizeof(int));
        for (int i = 0; i < tamanho_atual; i++)
            numeros_sorteados[i] = rand() % 50000;

        int total_comp_lista = 0;
        int total_comp_heap  = 0;

        /* Popula as estruturas e acumula o total de comparações. */
        for (int i = 0; i < tamanho_atual; i++)
        {
            total_comp_lista += enqueue_lista(&minha_lista, numeros_sorteados[i]);
            total_comp_heap  += enqueue_heap(meu_heap,      numeros_sorteados[i]);
        }

        fprintf(arquivo, "%d,%d,%d\n", tamanho_atual, total_comp_lista, total_comp_heap);
        printf("Tamanho: %d | Lista: %d comp. | Heap: %d comp.\n",
               tamanho_atual, total_comp_lista, total_comp_heap);

        /* Libera a memória alocada nesta iteração. */
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

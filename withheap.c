#include <stdlib.h>

/**
 * @brief Nó do heap de prioridade.
 *
 * Representa um elemento armazenado no min-heap via array.
 * O ponteiro {@code next} é omitido pois a estrutura de árvore é
 * representada implicitamente pelo array: o pai do índice {@code i}
 * está em {@code (i-1)/2} e os filhos em {@code 2i+1} e {@code 2i+2}.
 */
typedef struct node {
    int prioridade; /**< Prioridade do elemento (menor valor = maior prioridade). */
} node;

/**
 * @brief Fila de prioridade implementada como min-heap sobre um array.
 *
 * Um heap é uma árvore binária completa que redefine a lógica de inserção,
 * reduzindo sua complexidade de O(n) para O(log n) em relação à lista
 * encadeada ordenada.
 */
typedef struct heap {
    node *elementos; /**< Array de nós que representa o heap. */
    int tamanho;     /**< Quantidade de elementos atualmente no heap. */
    int capacidade;  /**< Capacidade máxima do array. */
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
    h->elementos = (node *)malloc(capacidade * sizeof(node));
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
int eh_vazia(heap *h)
{
    return h->tamanho == 0;
}

/**
 * @brief Troca os valores de dois nós do heap.
 *
 * Função auxiliar utilizada pelo heapify up e heapify down para
 * reposicionar elementos e restaurar a propriedade do min-heap.
 *
 * @param a Ponteiro para o primeiro nó.
 * @param b Ponteiro para o segundo nó.
 */
void trocar(node *a, node *b)
{
    node temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Insere um elemento no heap e restaura a propriedade do min-heap (heapify up).
 *
 * O elemento é inserido no final do array e sobe na árvore enquanto
 * sua prioridade for menor que a do pai, garantindo a propriedade do
 * min-heap. A complexidade de inserção é O(log n).
 *
 * @param h          Ponteiro para o heap onde o elemento será inserido.
 * @param prioridade Valor de prioridade do elemento (menor valor = maior prioridade).
 * @return Número de comparações realizadas durante a inserção, ou -1 se o heap estiver cheio.
 */
int enqueue(heap *h, int prioridade)
{
    int comparacoes = 0;

    if (h->tamanho == h->capacidade)
    {
        printf("Fila cheia\n");
        return -1;
    }

    int i = h->tamanho;
    h->elementos[i].prioridade = prioridade;
    h->tamanho++;

    /* Heapify up: sobe o elemento recém-inserido até sua posição correta. */
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
 * A raiz (menor valor) é removida. O último elemento do array ocupa
 * seu lugar e desce na árvore enquanto houver filho com prioridade menor,
 * restaurando a propriedade do min-heap. A complexidade de remoção é O(log n).
 *
 * @param h Ponteiro para o heap do qual o elemento será removido.
 * @return Valor de prioridade do elemento removido, ou -1 se o heap estiver vazio.
 */
int dequeue(heap *h)
{
    if (eh_vazia(h))
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

    /* Heapify down: desce a nova raiz até sua posição correta. */
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
            break; /* Propriedade do heap restaurada. */
        }
    }

    return valor_removido;
}

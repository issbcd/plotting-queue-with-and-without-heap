#include <stdlib.h>

/**
 * @brief Nó da fila de prioridade sem heap (lista encadeada).
 *
 * Menor valor = maior prioridade.
 */
typedef struct node {
    int prioridade;    /**< Prioridade do elemento. */
    struct node *next; /**< Ponteiro para o próximo nó da fila. */
} node;

/**
 * @brief Fila de prioridade implementada como lista encadeada ordenada.
 */
typedef struct fila {
    node *head; /**< Ponteiro para o primeiro nó da fila. */
} fila;

/**
 * @brief Verifica se a fila está vazia.
 *
 * @param fila Ponteiro para a fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int eh_vazia(fila *fila)
{
    return fila->head == NULL;
}

/**
 * @brief Insere um elemento na fila mantendo a ordem crescente de prioridade.
 *
 * Percorre a lista encadeada até encontrar a posição correta de inserção,
 * garantindo que o elemento com menor valor (maior prioridade) fique na frente.
 * A complexidade de inserção é O(n).
 *
 * @param fila      Ponteiro para a fila onde o elemento será inserido.
 * @param prioridade Valor de prioridade do elemento (menor valor = maior prioridade).
 * @return Número de comparações realizadas durante a inserção.
 */
int enqueue(fila *fila, int prioridade)
{
    int comparacoes = 0;

    node *novo = (node *)malloc(sizeof(node));
    novo->prioridade = prioridade;
    novo->next = NULL;

    if (eh_vazia(fila))
    {
        fila->head = novo;
        return comparacoes;
    }

    comparacoes++; /* Comparação 1: verifica se o novo elemento tem prioridade maior que o primeiro. */
    if (prioridade < (fila->head)->prioridade)
    {
        novo->next = fila->head;
        fila->head = novo;
        return comparacoes;
    }

    node *atual = fila->head;

    while (atual->next != NULL)
    {
        comparacoes++; /* Compara com o próximo elemento. */

        if (atual->next->prioridade > prioridade)
        {
            break;
        }

        atual = atual->next;
    }

    novo->next = atual->next;
    atual->next = novo;

    return comparacoes;
}

/**
 * @brief Remove e retorna o elemento de maior prioridade da fila.
 *
 * Remove o primeiro nó da lista (menor valor de prioridade) e libera
 * a memória alocada para ele. A complexidade de remoção é O(1).
 *
 * @param fila Ponteiro para a fila da qual o elemento será removido.
 * @return Valor de prioridade do elemento removido, ou -1 se a fila estiver vazia.
 */
int dequeue(fila *fila)
{
    if (eh_vazia(fila))
    {
        return -1;
    }

    node *aux = fila->head;
    int valor_prioridade = aux->prioridade;
    fila->head = fila->head->next;

    free(aux);

    return valor_prioridade;
}

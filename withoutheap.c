#include <stdlib.h>


//meninas, nesse codigo eu considerei que o menor valor tem maior prioridade

  typedef struct node{
    int prioridade;    //guarda prioridade de cada elemento
    struct node *next; //ponteiro para o próximo nó da lista/fila
  }node;

  typedef struct fila{
    node *head; //ponteiro para o primeiro nó da fila
  }fila;

  //verifica se a fila esta vazia
  int eh_vazia(fila *fila) 
  {
    return fila->head == NULL;
  }

  /*funcao para enfileirar (menor valor tem maior prioridade) e retorna o numero de comparacoes
  
  parametros:
  fila *fila: ponteiro para o primeiro nó da fila
  int prioridade: valor da prioridade
  */
  int enqueue(fila *fila, int prioridade) 
  {
    int comparacoes = 0; //vai ser usado para contar o numero de comparacoes 

    //aloca memória para o novo nó
    node *novo = (node *)malloc(sizeof(node));
    novo->prioridade = prioridade;
    novo->next = NULL;

    if(eh_vazia(fila)) 
    {
      fila->head = novo; //se a fila estiver vazia, o novo nó se torna o primeiro
      return comparacoes;
    } 

    comparacoes++; //comparacao 1: verificao novo elemento tem prioridade maior que o primeiro
    if(prioridade < (fila->head)->prioridade)  
    {
      novo->next = fila->head; 
      fila->head = novo;
      return comparacoes;
    } 
  
    node *atual = fila->head;
    
    //percorre a fila para encontrar o local correto de inserção
    while(atual->next != NULL){
      comparacoes++; //compara com o próximo elemento  

      if(atual->next->prioridade > prioridade) 
      {
        break;        
      }

      atual = atual->next;
    }
    
    //insere o novo nó no lugar certp
    novo->next = atual->next;
    atual->next = novo;

    return comparacoes;

}

  /*função que remove o elemente e retorna a nova maior prioridade
  recebe como parametro o endereço do primeiro nó da fila, que será removido
  */

  int dequeue(fila *fila)
  {
    if (eh_vazia(fila))
    {
      return -1;
    }
    //guarda o no que vai ser removido (o primeiro da lista)
    node *aux = fila->head;
    int valor_prioridade = aux->prioridade;
    fila->head = fila->head->next; //o início da fila passa a ser o próximo elemento

    //libera a memória do nó removido
    free(aux);

    return valor_prioridade;
  }
#include <stdlib.h>


/*###### Vamos entender como funciona o heap e o que isso mudará no nosso código!!!
implementar heap costuma significar aumento da eficiencia da nossa fila. veremos isso visualmente na plotagem.
mas, afinal, o que é um heap???
heap é, essencialmente, uma árvore binária completa, que muda completamente a lógica de inserção. Com o heap, a determinação 
de pais e filhos da árvore consequentemente torna a inserção em fila O(log n), enquanto a inserção sem ele é muito mais lenta, O(n).
*/
typedef struct node
{
    int prioridade;    //guarda prioridade de cada elemento
    //o ponteiro para next some aqui, pois estaremos usando um array para demonstrar heap da melhor forma possível
} node;

/*######################### INICIO DA IMPLEMENTAÇÃO DO HEAP!! ###############################*/

typedef struct heap
{
    node *elementos; //perceba que isso também mudou!!! também porque usaremos array
    int tamanho; //tamanho total do array 
    int capacidade; //total capacidade do array 
} heap; //nosso heap será especificamente um min heap, ou seja, prioriza o menor valor

heap* criarheap (int capacidade) //funçao que inicializa nosso heap a partir da estrutura que acabamos de criar! recebe a capacidade total
{
    heap *h = (heap*) malloc(sizeof(heap)); //aqui cria o primeiro elemento heap
    h->elementos = (node *)malloc(capacidade * sizeof(node)); //aqui criamos o total de nós referente a capacidade
    h->tamanho = 0; //tamanho atual = 0
    h->capacidade = capacidade; //mantém a capacidade
    return h;
}


  //verifica se a fila esta vazia
int eh_vazia(heap *h) 
{
    return h->tamanho == 0; //isso tbm mudou pela troca de encadeamento por array
}

/* ############# NOVA FUNCAO!!!! ###########*/
void trocar(node *a, node *b) //funcao crucial no heapfy!!!!! vamos usar ela mtas vezes. basicamente troca variaveis entre si
{
    node temp = *a;
    *a = *b;
    *b = temp;
}

  /*funcao para enfileirar (menor valor tem maior prioridade) e retorna o numero de comparacoes
  
  parametros:
  fila *fila: ponteiro para o primeiro nó da fila
  int prioridade: valor da prioridade
  */

int enqueue(heap *h, int prioridade) //enfileirar COM HEAP ! recebemos a fila em si e a prioridade do elemento a ser enfileirado
{
    int comparacoes = 0; //vms retornar isso dps

    if (h->tamanho == h->capacidade) //precisamos verificar se tem lugar na fila antes de alocar algo!
    {
        printf("Fila cheia\n");
        return -1; 
    }

    int i = h->tamanho; //i = nosso indice!!
    h->elementos[i].prioridade = prioridade; //coloca a prioridade no local
    h->tamanho++; //aumenta o tamanho do nosso array

    /* ################ HEAPFY up! ##################### */
    //agora é o diferencial do heap
    int pai = (i - 1) / 2; //isso é basicamente uma fórmula. ajuda a encontrar os filhos!!!
    while (i != 0) 
    {
        comparacoes++;
        if (h->elementos[pai].prioridade > h->elementos[i].prioridade) //aqui a gente faz a troca q faz parte da alma do heap
        {
            trocar(&h->elementos[i], &h->elementos[pai]); //func trocar troca esses 2 elementos
            i = pai; //i vira o pai
            pai = (i - 1) / 2; //+ uma vez nossa fórmula de pai, agora atualizando o valor com base em i
        } 

        else 
        {
            break; 
        }

        
    }
    
    return comparacoes;
}

  /*função que remove o elemente e retorna a nova maior prioridade
  recebe como parametro o endereço do primeiro nó da fila, que será removido
  */

int dequeue(heap *h)
{
    if (eh_vazia(h)) //antes de tudo a gente ve se tem o que tirar
    {
        return -1;
    }

    if (h->tamanho == 1) //a gente tira o único que tem para tirar
    {
        h->tamanho--;
        return h->elementos[0].prioridade;
    }

    //após verificar as 2 possiveis situacoes de facil resolução, vms pra geral

    int valor_removido = h->elementos[0].prioridade;

    h->elementos[0] = h->elementos[h->tamanho - 1];
    h->tamanho--;

    /* ################ HEAPFY down! ################### */
    int i = 0;
    while (1) 
    {
        int esq = 2 * i + 1; //+ formulas!!! de pai p filhos e vice versa, esses valores sao essenciais p comparar abaixo
        int dir = 2 * i + 2;
        int menor = i; //zero por enquanto

        //verifica se o filho esquerdo é menor
        if (esq < h->tamanho && h->elementos[esq].prioridade < h->elementos[menor].prioridade) 
        {
            menor = esq;
        }

        //verifica se o filho direito é menor
        if (dir < h->tamanho && h->elementos[dir].prioridade < h->elementos[menor].prioridade) 
        {
            menor = dir;
        }

        //se o menor for um dos filhos, troca e continua descendo!
        if (menor != i) 
        {
            trocar(&h->elementos[i], &h->elementos[menor]);
            i = menor;
        } 

        else 
        {
            break; //propriedade do Heap concluida
        }
    }

    return valor_removido;
}
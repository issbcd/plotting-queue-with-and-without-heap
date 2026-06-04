#include <stdio.h>
#include <stdlib.h>
#include <time.h> //necessario p gerar numeros "aleatorios"


int main() {
    //gera numeros randomicos
    srand(time(NULL));

    //abre o arquivo CSV para gravação
    FILE *arquivo = fopen("resultados.csv", "w");
    if (arquivo == NULL) 
    {
        printf("Erro ao criar o arquivo CSV!\n");
        return 1;
    }

    //cabeçalho do CSV que será lido pelo MATLAB
    fprintf(arquivo, "Tamanho_Fila,Comparacoes_Sem_Heap,Comparacoes_Com_Heap\n");

    int passo = 1000; //de quanto em quanto a fila vai crescer
    int max_elementos = 10000; //tamanho máximo que será testado

    printf("Gerando dados para o plot...\n");

    //loop principal para testar diferentes tamanhos de dados
    for (int tamanho_atual = passo; tamanho_atual <= max_elementos; tamanho_atual += passo) 
    {
        
        //inicializa as estruturas vazias
        fila minha_lista;
        minha_lista.head = NULL;
        
        heap *meu_heap = criarheap(tamanho_atual);

        //cria um array temporário para garantir os mesmos sorteios
        int *numeros_sorteados = (int *)malloc(tamanho_atual * sizeof(int));
        for (int i = 0; i < tamanho_atual; i++) 
        {
            numeros_sorteados[i] = rand() % 50000; //sorteia prioridades de 0 a 49999
        }

        int total_comp_lista = 0;
        int total_comp_heap = 0;

        //popula as estruturas e acumula as comparações
        for (int i = 0; i < tamanho_atual; i++) 
        {
            total_comp_lista += enqueue_lista(&minha_lista, numeros_sorteados[i]);
            total_comp_heap += enqueue_heap(meu_heap, numeros_sorteados[i]);
        }

        //salva os totais no arquivo CSV
        fprintf(arquivo, "%d,%d,%d\n", tamanho_atual, total_comp_lista, total_comp_heap);
        printf("Tamanho: %d | Lista: %d comp. | Heap: %d comp.\n", tamanho_atual, total_comp_lista, total_comp_heap);

        //LIMPEZA DE MEMÓRIA (Crucial para o próximo loop não dar erro)
        free(numeros_sorteados); // Libera o array de sorteios
        
        //esvazia a lista encadeada usando a função dequeue
        while (!eh_vazia_lista(&minha_lista)) 
        {
            dequeue_lista(&minha_lista);
        }
        
        //libera o array interno do heap e o struct
        free(meu_heap->elementos);
        free(meu_heap);
    }

    fclose(arquivo);
    printf("\nPronto! O arquivo 'resultados.csv' foi gerado. Pode rodar o MATLAB!\n");

    return 0;
}
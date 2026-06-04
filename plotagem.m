% Lê os dados do arquivo CSV que você fez upload
disp('Lendo resultados.csv...');
dados = readtable('resultados.csv');

% Extrai as colunas
tamanhos = dados.Tamanho_Fila;
comp_lista = dados.Comparacoes_Sem_Heap;
comp_heap = dados.Comparacoes_Com_Heap;

% Plota o Gráfico
figure; 
hold on; 
grid on; 

% Linhas do gráfico
plot(tamanhos, comp_lista, '-ro', 'LineWidth', 2, 'MarkerSize', 6);
plot(tamanhos, comp_heap, '-bs', 'LineWidth', 2, 'MarkerSize', 6);

% Estética e legendas
title('Eficiência: Fila sem Heap vs. Fila com Heap', 'FontSize', 14);
xlabel('Quantidade de Elementos', 'FontSize', 12);
ylabel('Número de Comparações', 'FontSize', 12);
legend({'Fila Simples (O(n))', 'Heap (O(log n))'}, 'Location', 'northwest', 'FontSize', 11);

hold off;
disp('Gráfico gerado com sucesso!');

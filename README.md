# theory_of_graphs

Aluno: Renato dos Santos;

 Projeto realizado para obtenção da nota AB2 na disciplina de teoria dos grafos no curso de Ciencia da Computacao (Ufal).
 
 
 No arquivo .dat há o grafo, sendo:
  A primeira linha corresponde ao numero de arestas;
  A segunda linha corresponde ao vertice de inicio (valor real) (vertice u);
  A terceira linha corresponde ao vertice de destino (valor real) (vertice v) ao qual se deseja saber o caminho minimo;
  Nas linhas abaixo, na primeira coluna o verice A, na segunda o vertice B (o que significa que A adjacente a B, ou seja, ha uma aresta entre tais vertices) e na teceira o peso.


Na saida temos:
 -> Seja o vertice u o vertice escolhido;
 Rota de u para todos os outros vertices;
 Custo de u para todos os outros vertices;
 Custo de u(inicial) para v(final);


OBS: 
 -> O tamanho maximo de arestas foi definido como 50 (em grafo[50][50]) para evitar problemas de compilacao que estavam ocorrendo em minha maquina.
 -> Os valores das arestas devem ser inteiros e 
 -> Se o peso da aresta for 1, nao deixar em branco, colocar como no exemplo.

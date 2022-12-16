#include <bits/stdc++.h>

using namespace std;

int e, e2, peso;

struct Edge {
    int u;
    int v;
    int w;
};


struct Graph {
    int V;
    int E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;

    graph->edge = new Edge[E];
    return graph;
}


void printArr(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

void BellmanFord(struct Graph* graph, int u) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

  
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

  
    dist[u] = 0;

  
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].u;
            int v = graph->edge[j].v;
            int w = graph->edge[j].w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }


    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].u;
        int v = graph->edge[i].v;
        int w = graph->edge[i].w;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative w cycle");
            return;
        }
    }

    printArr(dist, V);

    return;
}

//funcao para transformar os valores do .dat em inteiros
int inteiro(string linha, int j, int k)
{
    int x = 0;
    float aux = 0.00, w = 0.00, z = 0.00;

    for(x = j - 1; x > k; x--, w = w + 1.00){
        aux = linha[x] - '0';
        w = roundf(w * 100) / 100;
        z = z + pow(10, w) * aux;
    }

    return z;
}


//funcao auxiliar para armazenar os valores dos inteiros do .dat
int assistant(string linha)
{
    int contador = 0, i = 0, k = 0, j = 0, mult = 1;
   

    for(i = 0, k = -1, j = 1; linha[i]; i++){
        if(linha[i] == ' '){
            if(j == 1)
                e = inteiro(linha, i, k);
            else if(j == 2)
                e2 = inteiro(linha, i, k);

            k = i;
            j++;
        }
    }
    
    if(linha[k + 1] == '-'){
        k++;
        mult = -1;
    }
    peso = inteiro(linha, i, k);
    peso = peso * mult;
}



int main() {
    string linha;
    int cont = 0, u, n, m;
    

    ifstream file;
    file.open("grafo.dat");

    
    getline(file, linha);
    
    //calcula o n a partir do .dat
    for(int i = 0; linha[i]; i++)
        cont++;
    n = inteiro(linha, cont, -1);

    //calcula o u a partie do .dat sendo u o vertice de inicio
    getline(file, linha);
    cont = 0;
    for(int i = 0; linha[i]; i++)
        cont++;
    m = inteiro(linha, cont, -1);
    
    getline(file, linha);
    cont = 0;
    for(int i = 0; linha[i]; i++)
        cont++;
    u = inteiro(linha, cont, -1);


    cont = 0;
    //coloca os pesos nas posicoes correspondentes
    struct Graph* graph = createGraph(n, m);
    for(int i = 0; !file.eof(); i++){
        getline(file, linha);
        assistant(linha);
        graph->edge[i].u = e;
        graph->edge[i].v = e2;
        graph->edge[i].w = peso;
    }

    BellmanFord(graph, u);

  return 0;
}
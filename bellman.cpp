#include <iostream>
#include <fstream>
#include <math.h>
#define MAX 50
#define INF 9999

using namespace std;

int n, m, edge, edge2, peso;
 

void BellmanFord(int graph[][MAX], int V, int E, int u)
{
    int dis[V];
    for (int i = 0; i < V; i++)
        dis[i] = INF;
 
    
    dis[u] = 0;
 

    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            if (dis[graph[j][0]] != INF && dis[graph[j][0]] + graph[j][2] <dis[graph[j][1]])
                dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
        }
    }
 
    
    for (int i = 0; i < E; i++) {
        int x = graph[i][0];
        int y = graph[i][1];
        int weight = graph[i][2];
        if (dis[x] != INF &&
                   dis[x] + weight < dis[y])
            cout << "Graph contains negative weight cycle" << endl;
    }
 
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << "\t\t" << dis[i] << endl;
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


//funcao auxiliar para saber quantos valores tem na linha
int assistant(string linha)
{
    int contador = 0, i = 0, k = 0, j = 0, mult = 1;
   

    for(i = 0, k = -1, j = 1; linha[i]; i++){
        if(linha[i] == ' '){
            if(j == 1)
                edge = inteiro(linha, i, k);
            else if(j == 2)
                edge2 = inteiro(linha, i, k);

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


// Driver program to test above functions
int main()
{
    
    string linha;
    int cont = 0, u;
    

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

    int grafo[MAX][MAX];
    int custo[MAX], rota[MAX];

    //preenche o grafo todo com 0
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < n; j++)
            grafo[i][j] = 0;
    }

    cont = 0;
    //coloca os pesos nas posicoes correspondentes
    while(!file.eof()){
        getline(file, linha);
        assistant(linha);
        grafo[edge - 1][edge2 - 1] = peso;
        grafo[edge2 - 1][edge - 1] = peso;
    }

    BellmanFord(grafo, n, m, u - 1);
    return 0;
}
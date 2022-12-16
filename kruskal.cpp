#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#define edge pair<int, int>


using namespace std;

int e, e2, peso;


class Graph {
    private:
    vector<pair<int, edge> > G;
    vector<pair<int, edge> > T;
    int *parent;
    int V;
    public:
        Graph(int V);
        void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

Graph::Graph(int V) {
    parent = new int[V];
    for (int i = 0; i < V; i++)
        parent[i] = i;

    G.clear();
    T.clear();
}


void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}


int Graph::find_set(int i) {
    if (i == parent[i])
        return i;
    else
        return find_set(parent[i]);
}


void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}


void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end());
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]);
            union_set(uRep, vRep);
        }
    }
}


void Graph::print() {
    cout << "Edge :"
        << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : "
        << T[i].first;
        cout << endl;
    }
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


    //coloca os pesos nas posicoes correspondentes
    Graph g(m);
    while(!file.eof()){
        getline(file, linha);
        assistant(linha);
        g.AddWeightedEdge(e, e2, peso);
    }

    g.kruskal();
    g.print();

    return 0;
}
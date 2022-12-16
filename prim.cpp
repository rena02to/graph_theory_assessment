#include <iostream>
#include <fstream>
#include <math.h>
#define INF 9999
#define MAX 50

using namespace std;

int n, edge, edge2, peso, m;


int print_MST(int parent[], int grafo[][MAX])
{
    int i;

    int custo = 0;
    for(i = 1; i < n; i++){
        custo = custo + grafo[i][parent[i]];
    }
    cout << "CUSTO: " << custo;
}

//funcao para imprimir o vetor desejado
void imprime_vector(int vetor[])
{
    cout << "{";
    int i;

    for(i = 0; i < n; i++)
    {
        cout << vetor[i];
        if(i < n -1)
            cout << ", ";
    }

    cout << "}";
}

int min_key(int key[], bool visited[], int y)
{
    int inf_index;
    int inf = key[y];

    for(int i = 0; i < n; i++){
        if(visited[i] == false && key[i] < inf){
            inf = key[i];
            inf_index = i;
        }
    }
    return inf_index;
}


void find_MST(int custo[][MAX], int rota[], int u)
{
    int parent[n], key[n], cust = 0, ind;
    bool visited[n];

    for(int i = 0; i < n; i++){
        key[i] = INF;
        rota[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;
    parent[0] = 0;
    
    for(int x = 1; x < n; x++)
    {
        visited[u] = true;

        for(int y = 0; y < n; y++){
            if(custo[u][y] != 0 && visited[y] == false && custo[u][y] <= key[x]){
                key[x] = custo[u][y];
                parent[x] = y + 1;
                ind = y;
            }
        }
        cust = cust + key[x];
        key[x] = cust;
        u = ind;
    }
    
    
    cout << endl;
    cout << "CAMINHO MINIMO: ";
    imprime_vector(parent);
    cout << endl;
    cout << "CUSTO TOTAL: " << cust << endl;

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

    getline(file, linha);
    cont = 0;
    for(int i = 0; linha[i]; i++)
        cont++;
    m = inteiro(linha, cont, -1);


    //calcula o u a partie do .dat sendo u o vertice de inicio
    getline(file, linha);
    cont = 0;
    for(int i = 0; linha[i]; i++)
        cont++;
    u = inteiro(linha, cont, -1);
    

    int grafo[MAX][MAX];
    int rota[MAX];

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


    find_MST(grafo, rota, u-1);

    return 0;
}
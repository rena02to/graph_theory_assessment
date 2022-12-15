#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#define INF 9999 //infinito = 9999
#define MAX 50

using namespace std;

int n, edge, edge2, peso, m;

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


//funcao de dijkstra
void dijkstra(int ordem, int s, int grafo[][MAX], int custo[MAX], int rota[MAX])
{
    int r = -1;

    bool* visited = NULL;
    visited = new bool[ordem];


    //inicializando os vetores
    for(int i = 0; i < ordem; i++){
        visited[i] = false;
    }
    for(int i = 0; i < ordem; i++){
        custo[i] = INF;
        rota[i] = -1;
    }

    custo[s] = 0;
    rota[s] = s;
    
    //loop principal
    while(true){
        r = -1;
        
        for(int i = 0; i < ordem; i++){
            if(!visited[i] && (r < 0 || custo[i] < custo[r])){
                r = i;
            }
        }

        if(r < 0)
            break;

        visited[r] = true;

        for(int i = 0; i < ordem; i++){
            if(grafo[r][i] && custo[i] > custo[r] + grafo[r][i]){
                custo[i] = custo[r] + grafo[r][i];
                rota[i] = r + 1;
            }
        }
    }

    delete [] visited;
    visited = NULL;
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
    
    //chama a funcao dijkstrta e printa o vetor desejado
    dijkstra(n, u-1, grafo, custo, rota);
    cout << "ROTA: ";
    imprime_vector(rota);
    cout << endl << "CUSTO: ";
    imprime_vector(custo);

    return 0;
}
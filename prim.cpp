#include <cstring>
#include <iostream>
#include <fstream>
#include <math.h>
#define INF 99999


using namespace std;


int n, e, e2, peso;


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
    int G[n][n];

    while(!file.eof()){
        getline(file, linha);
        assistant(linha);
        G[e - 1][e2 - 1] = peso;
        G[e2 - 1][e - 1] = peso;
    }

  int no_edge;

  
  int selected[n];

 
  memset(selected, false, sizeof(selected));


  no_edge = 0;



 
  selected[0] = true;

  int x;
  int y;

  
  cout << "Edge"
     << " : "
     << "Weight";
  cout << endl;
  while (no_edge < n - 1) {

    int min = INF;
    x = 0;
    y = 0;

    for (int i = 0; i < n; i++) {
      if (selected[i]) {
        for (int j = 0; j < n; j++) {
          if (!selected[j] && G[i][j]) {
            if (min > G[i][j]) {
              min = G[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    cout << x+1 << " - " << y+1 << " :  " << G[x][y];
    cout << endl;
    selected[y] = true;
    no_edge++;
  }

  return 0;
}
#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<vector<int> > original, traspuesto;
vector<int> scc; // scc = Strong Connected Component
int componente;
stack<int> pila;
vector<bool> visitado;

void dfs(int nodo, bool segundaPasada, vector<vector<int> >& grafo){
  visitado[nodo] = true;
  forn(i, grafo[nodo].size()){
    int vecino = grafo[nodo][i];
    if(!visitado[vecino])
      dfs(vecino, segundaPasada, grafo);
  }
  if(segundaPasada)
    scc[nodo] = componente;
  else
    pila.push(nodo);
}

void kosaraju(int A){
  componente = 0;
  pila = stack<int>();
  visitado = vector<bool>(A, false);
  scc = vector<int>(A);

  forn(i, A)
    if(!visitado[i])
      dfs(i, false, original);

  visitado = vector<bool>(A, false);

  while(!pila.empty()){
    int v = pila.top(); pila.pop();
    if (!visitado[v]) {
      dfs(v, true, traspuesto);
      componente++;
    }
  }
}

int inicializar(){
  int A, P, v, w;
  cin >> A >> P;
  original = vector<vector<int> >(A, vector<int>());
  traspuesto = vector<vector<int> >(A, vector<int>());
  forn(i, P){
    cin >> v >> w;
    v--; w--;
    original[v].push_back(w);
    traspuesto[w].push_back(v);
  }
  return A;
}

void terminar(){
  int Q, v, w;
  cin >> Q;
  forn(i, Q){
    cin >> v >> w;
    if(scc[v - 1] == scc[w - 1])
      cout << 'S' << endl;
    else
      cout << 'N' << endl;
  }
}

int main(int argc, char const *argv[]) {
  int A = inicializar();

  kosaraju(A);

  terminar();
  return 0;
}

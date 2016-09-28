#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<vector<int> > original, traspuesto;
vector<int> scc;
int componente;
stack<int> pila;
vector<bool> visited;

void dfs(int nodo, bool segundaPasada, vector<vector<int> >& grafo){
  visited[nodo] = true;
  forn(i, grafo[nodo].size()){
    int vecino = grafo[nodo][i];
    if(!visited[vecino])
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
  visited = vector<bool>(A, false);
  scc = vector<int>(A);

  forn(i, A)
    if(!visited[i])
      dfs(i, false, original);

  visited = vector<bool>(A, false);

  while(!pila.empty()){
    int v = pila.top(); pila.pop();
    if (!visited[v]) {
      dfs(v, true, traspuesto);
      componente++;
    }
  }
}

int main(int argc, char const *argv[]) {
  int A, P, Q;
  cin >> A >> P;
  original = vector<vector<int> >(A, vector<int>());
  traspuesto = vector<vector<int> >(A, vector<int>());
  int v, w;
  forn(i, P){
    cin >> v >> w;
    v--; w--;
    original[v].push_back(w);
    traspuesto[w].push_back(v);
  }

  kosaraju(A);

  cin >> Q;
  forn(i, Q){
    cin >> v >> w;
    v--; w--;
    if(scc[v] == scc[w])
      cout << 'S' << endl;
    else
      cout << 'N' << endl;
  }
  return 0;
}

#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<vector<int> > grafo;
vector<int> scc;

int indice, componente, A;
stack<int> pila;
vector<bool> apilados;
vector<pair<int, int> > dfs_traversal;

void initTarjan(){
  indice = 0, componente = 0;
  pila = stack<int>();
  apilados = vector<bool>(A, false);
  dfs_traversal = vector<pair<int, int> >(A, make_pair(-1, -1));
  scc = vector<int>(A);
}

void strongConnect(int nodo){
  dfs_traversal[nodo].first = indice;
  dfs_traversal[nodo].second = indice;
  indice++;
  pila.push(nodo);
  apilados[nodo] = true;
  forn(i, grafo[nodo].size()){
    int vecino = grafo[nodo][i];
    if(dfs_traversal[vecino].first == -1){
      strongConnect(vecino);
      dfs_traversal[nodo].second = min(dfs_traversal[nodo].second, dfs_traversal[vecino].second);
    }
    else if(apilados[vecino])
      dfs_traversal[nodo].second = min(dfs_traversal[nodo].second, dfs_traversal[vecino].first);
  }
  if(dfs_traversal[nodo].second == dfs_traversal[nodo].first){
    int vecino;
    do {
      vecino = pila.top();
      pila.pop();
      apilados[vecino] = false;
      scc[vecino] = componente;
    } while(nodo != vecino);
    componente++;
  }
}

void tarjan(){
  initTarjan();
  forn(i, A)
    if(dfs_traversal[i].first == -1)
      strongConnect(i);
}

int main(int argc, char const *argv[]) {
  int P, Q;
  cin >> A >> P;
  grafo = vector<vector<int> >(A, vector<int>());
  int v, w;
  forn(i, P){
    cin >> v >> w;
    v--; w--;
    grafo[v].push_back(w);
  }

  tarjan();

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

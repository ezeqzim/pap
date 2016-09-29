#include "../stdc++.h"

typedef long long ll;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

// guardo la lista de adyacencia y el flujo que pasa en la red residual
vector<vector<pair<nodo, int> > > grafo;
nodo fuente, sumidero;
int INF = 1e31-1;

bool hayCaminoDeAumento(vector<pair<nodo, int> >& padres){
  padres[fuente].first = -1;
  vector<bool> visitados(grafo.size(), false);
  queue<nodo> q;
  q.push(fuente);
  visitados[fuente] = true;

  while(!q.empty()){
    nodo u = q.front(); q.pop();
    forn(i, grafo[u].size()){
      nodo v = grafo[u][i].first;
      int f = grafo[u][i].second;
      if(!(visitados[v] || f == 1)){
        visitados[v] = true;
        padres[v] = make_pair(u, i);
        q.push(v);
      }
    }
  }
  return visitados[sumidero];
}

int edmondsKarp(){
  int flujo = 0, n = grafo.size();
  bool hayCamino = true;
  // El par indica de que nodo vine y que indice en la lista use
  vector<pair<nodo, int> > padres(n, make_pair(-1, -1));
  while(hayCaminoDeAumento(padres)){
    flujo++;
    nodo v = sumidero;
    while(v != fuente){
      nodo u = padres[v].first;
      int index = padres[v].second;
      grafo[u][index].second++;
      v = u;
    }
  }
  return flujo;
}

nodo in(nodo v) {
  return 2*v;
}

nodo out(nodo v) {
  return 2*v+1;
}

void armar_nodos(int n){
  char c;
  forr(i, 1, n+1){
    grafo[in(i)].push_back(make_pair(out(i), 0)); // Conecto todos los u.in con u.out
    cin >> c;
    if(c == 'A') // De la fuente voy a los alumnos
      grafo[fuente].push_back(make_pair(in(i), 0));
    else if(c == 'E') // De las escuelas voy al sumidero
      grafo[out(i)].push_back(make_pair(sumidero, 0));
  }
}

void armar_ejes(int m){
  int u,v;
  forn(i, m){
    cin >> u >> v; // Si u y v están conectados, entonces de u.out sale eje a v.in y de v.out a u.in
    grafo[out(u)].push_back(make_pair(in(v), 0));
    grafo[out(v)].push_back(make_pair(in(u), 0));
  }
}

void inicializar(){
  int n, m;
  cin >> n >> m;
  grafo = vector<vector<pair<nodo, int> > >(2*n+2);
  sumidero = 0;
  fuente = 1;
  armar_nodos(n);
  armar_ejes(m);
}

int main(int argc, char const *argv[]) {
  // Fuente = 1
  // Sumidero = 0
  // Para toda esquina i, esquina_i_in = 2i
  // Para toda esquina i, esquina_i_out = 2i+1
  inicializar();
  cout << edmondsKarp() << endl;
  return 0;
}

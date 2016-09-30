#include "../stdc++.h"

typedef long long ll;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

// guardo la lista de adyacencia y el flujo que pasa en la red residual
vector<vector<pair<nodo, int> > > grafo;
nodo fuente, sumidero;
int capacidad = 1, INF = 1e31-1;

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
      grafo[v].push_back(make_pair(u, 0));
      int index = padres[v].second;
      grafo[u][index].second++;
      v = u;
    }
  }
  return flujo;
}

nodo izq(nodo v) {
  return 2*v;
}

nodo der(nodo v) {
  return 2*v+1;
}

void obtener_precios(int a, int d, vector<vector<int> >& precios_por_dia){
  forn(i, a)
    forn(j, d)
      cin >> precios_por_dia[i][j];
}

bool puede_ir_arriba(int d, nodo i, nodo j, vector<vector<int> >& precios_por_dia) {
  forn(k, d)
    if (precios_por_dia[i][k] <= precios_por_dia[j][k])
      return false;
  return true;
}

void armar_grafo(int a, int d, vector<vector<int> >& precios_por_dia){
  forn(i, a)
    forr(j, i+1, a)
      if (puede_ir_arriba(d, i, j, precios_por_dia))
        grafo[izq(i)].push_back(make_pair(der(j), 0));
      else if (puede_ir_arriba(d, j, i, precios_por_dia))
        grafo[izq(j)].push_back(make_pair(der(i), 0));
}

void conectar_fuente_y_sumidero(int a){
  forn(i, a){
    grafo[fuente].push_back(make_pair(izq(i), 0));
    grafo[der(i)].push_back(make_pair(sumidero, 0));
  }
}

int inicializar(){
  int d, a;
  cin >> a >> d;
  grafo = vector<vector<pair<nodo, int> > >(2*a+2);
  vector<vector<int> > precios_por_dia(a, vector<int>(d, 0));
  sumidero = 2*a+1;
  fuente = 2*a;
  obtener_precios(a, d, precios_por_dia);
  armar_grafo(a, d, precios_por_dia);
  conectar_fuente_y_sumidero(a);
  return a;
}

int main(int argc, char const *argv[]) {
  // Fuente = a
  // Sumidero = a+1
  // Para toda accion i, accion_i_in = 2i
  // Para toda accion i, accion_i_out = 2i+1
  int a = inicializar();
  cout << a - edmondsKarp() << endl;
  return 0;
}

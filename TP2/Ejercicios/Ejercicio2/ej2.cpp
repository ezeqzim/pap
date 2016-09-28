#include "../stdc++.h"

typedef long long ll;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<vector<nodo> > grafo, residual;
nodo sumidero, fuente;
int capacidad = 1, INF = numeric_limits<int>::max();

int edmondsKarp(){
  int flujo = 0, n = grafo.size();
  bool hayCamino = true;
  while(hayCamino){
    vector<nodo> previous(n, -1);
    vector<nodo> pathCapacity(n, 0);
    previous[fuente] = -2;
    pathCapacity[fuente] = INF;
    queue<nodo> cola;
    cola.push(fuente);
    bool terminar = false;
    // Busco un camino de aumento
    // Almaceno el flujo maximo que puedo pasar por el mismo
    while(!cola.empty() && !terminar){
      nodo u = cola.front(); cola.pop();
      forn(i, grafo[u].size()){
        nodo v = grafo[u][i];
        if(previous[v] == -1 && capacidad - residual[u][v]){
          previous[v] = u;
          pathCapacity[v] = min(pathCapacity[u], capacidad - residual[u][v]);
          if(v != sumidero)
            cola.push(v);
          else
            terminar = true;
        }
      }
    }
    // Si no hay flujo posible, termino
    if(pathCapacity[sumidero] == 0)
      hayCamino = false;
    else{
      flujo += pathCapacity[sumidero];
      nodo v = sumidero;
      while(v != fuente){
        nodo u = previous[v];
        residual[u][v] += pathCapacity[sumidero];
        residual[v][u] -= pathCapacity[sumidero];
        v = u;
      }
    }
  }
  return flujo;
}

nodo out(nodo v) {
  return 2*v+1;
}

nodo in(nodo v) {
  return 2*v;
}

void test(int a){
  // Este test toma el grafo nuevo, osea, con fuente y sumidero y con los nodos partidos en v_in y v_out y
  // reconstruye el grafo original más fuente y sumidero. Es decir, muestra como estaban conectados los
  // nodos originales y a qué nodos se conecta la fuente. Es para ver si se armó bien, ésta función se
  // puede eliminar más adelante.
  forn(i, a+1){
    cout << "Nodo: ";
    if(i == a) cout << "Fuente" << endl;
    else cout << i+1 << endl;
    cout << "Ejes salientes a: ";
    forn(j, grafo[in(i)].size()) {
      if(grafo[in(i)][j] == fuente) cout << "fuente ";
      else if(grafo[in(i)][j] == sumidero) cout << "sumidero ";
      else cout << grafo[in(i)][j]/2 + 1 << " ";
    }
    cout << endl;
  }
}

void obtener_precios(int a, int d, vector<vector<int> >& precios_por_dia){
  forn(i, a)
    forn(j, d)
      cin >> precios_por_dia[i][j];
}

bool puede_ir_arriba(int d, nodo i, nodo j, vector<vector<int> >& precios_por_dia) {
  forn(k, d)
    if (precios_por_dia[i][k] >= precios_por_dia[j][k])
      return false;
  return true;
}

void armar_grafo(int a, int d, vector<vector<int> >& precios_por_dia){
  forn(i, a)
    forn(j, a)
      if (i != j)
        if(puede_ir_arriba(d, i, j, precios_por_dia))
          grafo[in(i)].push_back(out(j));
}

void conectar_fuente_y_sumidero(int a){
  forn(i, a){
    grafo[fuente].push_back(in(i));
    grafo[out(i)].push_back(sumidero);
  }
}

int main(int argc, char const *argv[]) {
  // Fuente = a
  // Sumidero = a+1
  // Para toda accion i, accion_i_in = 2i
  // Para toda accion i, accion_i_out = 2i+1
  int d, a;
  cin >> a >> d;
  grafo = vector<vector<nodo> >(2*a+2);
  residual = vector<vector<nodo> >(2*a+2, vector<nodo>(2*a+2, 0));
  vector<vector<int> > precios_por_dia(a, vector<int>(d, 0));
  sumidero = 2*a+1;
  fuente = 2*a;
  obtener_precios(a, d, precios_por_dia);
  armar_grafo(a, d, precios_por_dia);
  conectar_fuente_y_sumidero(a);
  cout << a - edmondsKarp() << endl;
  // test(a);
  return 0;
}

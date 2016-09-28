#include "../stdc++.h"

using namespace std;

typedef long long ll;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

vector<vector<nodo> > grafo, residual;
nodo fuente, sumidero;
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

void test(int n){
  // Este test toma el grafo nuevo, osea, con fuente y sumidero y con los nodos partidos en v_in y v_out y
  // reconstruye el grafo original más fuente y sumidero. Es decir, muestra como estaban conectados los
  // nodos originales y a qué nodos se conecta la fuente. Es para ver si se armó bien, ésta función se
  // puede eliminar más adelante.
  forn(i, n+1){
    cout << "Nodo: ";
    if(i == 0) cout << "Fuente" << endl;
    else cout << i << endl;
    cout << "Ejes salientes a: ";
    forn(j, grafo[out(i)].size()) {
      if(grafo[out(i)][j] == fuente) cout << "fuente ";
      else if(grafo[out(i)][j] == sumidero) cout << "sumidero ";
      else cout << grafo[out(i)][j]/2 << " ";
    }
    cout << endl;
  }
}

void armar_nodos(int n){
  char c;
  forr(i, 1, n+1){
    grafo[in(i)].push_back(out(i)); // Conecto todos los u.in con u.out
    cin >> c;
    if(c == 'A') // De la fuente voy a los alumnos
      grafo[fuente].push_back(in(i));
    else if(c == 'E') // De las escuelas voy al sumidero
      grafo[out(i)].push_back(sumidero);
  }
}

void armar_ejes(int m){
  int u,v;
  forn(i, m){
    cin >> u >> v; // Si u y v están conectados, entonces de u.out sale eje a v.in y de v.out a u.in
    grafo[out(u)].push_back(in(v));
    grafo[out(v)].push_back(in(u));
  }
}

int main(int argc, char const *argv[]) {
  // Fuente = 1
  // Sumidero = 0
  // Para toda esquina i, esquina_i_in = 2i
  // Para toda esquina i, esquina_i_out = 2i+1
  int n, m;
  cin >> n >> m;
  grafo = vector<vector<nodo> >(2*n+2);
  residual = vector<vector<nodo> >(2*n+2, vector<nodo>(2*n+2, 0));
  sumidero = 0;
  fuente = 1;
  armar_nodos(n);
  armar_ejes(m);
  cout << edmondsKarp() << endl;
  // test(n);
  return 0;
}

#include "../stdc++.h"

typedef long long ll;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<vector<nodo> > grafo;
nodo sumidero;
nodo fuente;

int edmondsKarp(){
  int n = grafo.size(), f = 0, capacity = 1;
  vector<int> p(n), m(n);
  vector<vector<int> > flujo(n, vector<int>(n, 0));
  while(true){
    forn(i, n)
      p[i] = -1;
    p[fuente] = -2;
    m[fuente] = 1000000000;
    m[sumidero] = 0;
    queue<nodo> q;
    q.push(fuente);
    bool b = true;
    while(!q.empty() && b){
      nodo v = q.front();
      q.pop();
      forn(i, grafo[v].size()){
        nodo vec = grafo[v][i];
        if(capacity > flujo[v][vec] && p[vec] == -1){
          p[vec] = v;
          m[vec] = min(m[v], capacity - flujo[v][vec]);
          q.push(vec);
          if(vec == sumidero){
            b = false;
            break;
          }
        }
      }
    }
    if(b)
      break;
    f += m[sumidero];
    nodo v = sumidero;
    while(v != fuente){
      flujo[p[v]][v] += m[sumidero];
      flujo[v][p[v]] -= m[sumidero];
      v = p[v];
    }
  }
  return f;
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

void obtener_precios(int a, int d, vector<vector<int> >& precios_por_dia){
  int precio;
  forn(i, a)
    forn(j, d){
      cin >> precio;
      precios_por_dia[i][j] = precio;
    }
}

bool puede_ir_arriba(int d, nodo i, nodo j, vector<vector<int> >& precios_por_dia) {
  forn(k, d)
    if (precios_por_dia[i][k] <= precios_por_dia[j][k])
      return false;
  return true;
}

void armar_grafo(int a, int d, vector<vector<int> >& precios_por_dia){
  forn(i, a)
    forn(j, a)
      if (i != j)
        if(puede_ir_arriba(d, i, j, precios_por_dia))
          grafo[out(i)].push_back(in(j));
}

void conectar_fuente_y_sumidero(int a){
  forn(i, a){
    grafo[fuente].push_back(out(i));
    grafo[in(i)].push_back(sumidero);
  }
}

int main(int argc, char const *argv[]) {
  // Fuente = n+1
  // Sumidero = n
  // Para toda accion i, accion_i_in = 2i
  // Para toda accion i, accion_i_out = 2i+1
  int d, a;
  cin >> a >> d;
  grafo = vector<vector<nodo> >(2*a+2);
  vector<vector<int> > precios_por_dia(a, vector<int>(d, 0));
  sumidero = 2*a;
  fuente = 2*a+1;
  obtener_precios(a, d, precios_por_dia);
  armar_grafo(a, d, precios_por_dia);
  conectar_fuente_y_sumidero(a);
  cout << edmondsKarp() << endl;
  test(a);
  return 0;
}

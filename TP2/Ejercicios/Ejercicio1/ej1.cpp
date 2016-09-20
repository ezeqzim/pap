#include "../stdc++.h"

typedef long long ll;
typedef std::pair<int, int> eje;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<list<nodo> > grafo;
int m, n;
char c;
nodo sumidero;
nodo fuente;


nodo out(nodo v) {
    return 2*v+1;
}

nodo in(nodo v) {
    return 2*v;
}

void test(){
    // Este test toma el grafo nuevo, osea, con fuente y sumidero y con los nodos partidos en v_in y v_out y 
    // reconstruye el grafo original más fuente y sumidero. Es decir, muestra como estaban conectados los 
    // nodos originales y a qué nodos se conecta la fuente. Es para ver si se armó bien, ésta función se
    // puede eliminar más adelante.

    forr(i,0,n+1){
        cout << "Nodo: ";
        if (i == 0) cout << "Fuente" << endl;
        else cout << i << endl;
        cout << "Ejes salientes a: ";
        for (nodo v : grafo[out(i)]) {
            if (v == fuente) cout << "fuente ";
            else if (v==sumidero) cout << "sumidero ";
            else cout << v/2 << " ";
        }
        cout << endl;
    }
}

void armar_nodos(){
	forr(i,1,n+1){
    	grafo[in(i)].push_back(out(i));   // Conecto todos los u.in con u.out
    	cin >> c;
    	if (c == 'A') {   // De la fuente voy a los alumnos
    		grafo[fuente].push_back(in(i));
    	}
    	else if (c == 'E') {  // De las escuelas voy al sumidero
    		grafo[out(i)].push_back(sumidero);
    	}
    }
}

void armar_ejes(){
	int u,v;
	forn(i,m){
    	cin >> u >> v;     // Si u y v están conectados, entonces de u.out sale eje a v.in y de v.out a u.in
    	grafo[out(u)].push_back(in(v));
    	grafo[out(v)].push_back(in(u));
    }
}


int main(int argc, char const *argv[]) {

	// Fuente = 1
	// Sumidero = 0
	// Para toda esquina i, esquina_i_in = 2i
	// Para toda esquina i, esquina_i_out = 2i+1

	cin >> n >> m;
	grafo = vector<list<nodo>>(2*n+2);
	sumidero = 0;
	fuente = 1;

	armar_nodos();
	armar_ejes();
    test();
   


    return 0;
}

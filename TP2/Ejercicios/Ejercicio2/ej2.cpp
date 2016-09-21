#include "../stdc++.h"

typedef long long ll;
typedef std::pair<int, int> eje;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<list<nodo> > grafo;
vector<vector<int> > precios_por_dia;
vector<int> dia;
int d, a;
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

    forr(i,0,a+1){
        cout << "Nodo: ";
        if (i == a) cout << "Fuente" << endl;
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

void obtener_precios(){
	int precio;
	forn(i,a) {
		forn(j,d){
			cin >> precio;
			precios_por_dia[i][j] = precio;
		}
	}
}

bool puede_ir_arriba(nodo i, nodo j) {
	forn(k,d) {
		if (precios_por_dia[i][k] <= precios_por_dia[j][k]){
			return false;
		}
	}
	return true;
}

void armar_grafo(){
	forn(i,a){
		forn(j,a){
			if (i!=j){
				if (puede_ir_arriba(i,j)){
					cout << "Holis" << endl;
					grafo[out(i)].push_back(in(j));
				}
			}
		}
	}
}

void conectar_fuente_y_sumidero(){
	forn(i,a){
		grafo[fuente].push_back(in(i));
		grafo[out(i)].push_back(sumidero);
	}
}

int main(int argc, char const *argv[]) {

	// Fuente = n+1
	// Sumidero = n
	// Para toda accion i, accion_i_in = 2i
	// Para toda accion i, accion_i_out = 2i+1

	cin >> a >> d;
	grafo = vector<list<nodo>>(2*a+2);
	dia = vector<int>(d,0);
	precios_por_dia = vector<vector<int> >(a,dia);
	sumidero = 2*a;
	fuente = 2*a+1;

	obtener_precios();
	armar_grafo();
	conectar_fuente_y_sumidero();

    test();
   


    return 0;
}

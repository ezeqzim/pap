#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int n;
int cantCiclos;
vector<int> permutacion;
vector<int> ciclos;
vector<int> cicloPorElem;
ll MODULUS = 1e9 + 7;

ll modexp(ll res, ll a, int b) {
  while(b > 0) {
    if(b % 2 == 1)
      res = (res * a) % MODULUS;
    b >>= 1;
    a = (a * a) % MODULUS;
  }
  return res;
}

void inicializar() {
  cin >> n;
  cantCiclos = 0;
  permutacion = vector<int>(n, 0);
  cicloPorElem = vector<int>(n, -1);
  ciclos = vector<int>(n, 0);
  int aux;
  forn(i, n){
    cin >> aux;
    permutacion[i] = aux - 1;
  }
}

void armarCiclos() {
  int cantActual;
  int elemActual;
  int cicloActual = 0;
  forn(i, n) {
    //Si el elemento no está marcado como adentro de un ciclo
    if (cicloPorElem[i] == -1) {
      cantCiclos++;
      cantActual = 0;
      elemActual = i;
      do {
        cantActual++;
        cicloPorElem[elemActual] = cicloActual;
        elemActual = permutacion[elemActual];
        ciclos[cicloActual]++;
      } while (elemActual != i);
      cicloActual++;
    }
  }
}

int mcd(int a, int b){
  if(b == 0)
    return a;
  else
    return mcd(b, a % b);
}

ll calcularResultadosPosibles() {
  ll res = 1LL;
  forn(i, cantCiclos)
    res = modexp(res, 2, ciclos[i] / 2);
  forn(i, cantCiclos)
    forr(j, i + 1, cantCiclos)
      res = modexp(res, 2, mcd(ciclos[i], ciclos[j]));
  return res;
}

bool hayCiclosPares() {
  forn(i, cantCiclos)
    if ((ciclos[i] % 2) == 0) return true;
  return false;
}

int main(int argc, char const *argv[]) {
  inicializar();
  armarCiclos();
  if(hayCiclosPares()) cout << 0 << endl;
  else cout << calcularResultadosPosibles() << endl;
    return 0;
}

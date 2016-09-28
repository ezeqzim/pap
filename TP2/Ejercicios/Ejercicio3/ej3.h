#define forr(i,a,b) for(int i = a; i < b; ++i)
#define forn(i,n) forr(i, 0, n)
typedef unsigned int nodo;
typedef unsigned int eje;
typedef std::pair<eje, nodo> infoEje;

using namespace std;

void init();
infoEje info(eje, nodo);
void calcularPuentes();
int dfs(nodo, int, nodo, vector<int>&, vector<int>&);
void calcularComponentesK2();
void nodosEnComponente(nodo, list<nodo>&, vector<bool>&);
void A();
void B();
void C();
int encontrar(nodo, nodo, int, vector<bool>&);

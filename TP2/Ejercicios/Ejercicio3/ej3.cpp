#include "../stdc++.h"

using namespace std;

typedef std::pair<int, int> eje;
typedef int nodo;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

template <class T>
inline size_t hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return hash_combine(h1, h2);
    }
};

vector<list<nodo> > grafo;


vector<int> nodosEnLasMismasComponente;
vector<bool> esArticulacion;
unordered_map<eje, bool, pair_hash> esPuente;
vector<eje> ejes;

unsigned int n;

vector<int> depth;
vector<int> low;
stack<eje> pila;

vector<bool> recorrido;

eje edge(nodo v, nodo w) {
    return make_pair(v, w);
}

void generarComponente(eje e, nodo v) {
    unordered_set<nodo> nodosEnComponente;

    eje w = pila.top();
    nodosEnComponente.insert(w.first);
    nodosEnComponente.insert(w.second);

    while (pila.top() != e) {
        pila.pop();
        w = pila.top();
        nodosEnComponente.insert(w.first);
        nodosEnComponente.insert(w.second);
    }

    pila.pop();

    if (nodosEnComponente.size() > 2)
        for (const nodo& n : nodosEnComponente)
            nodosEnLasMismasComponente[n - 1] += nodosEnComponente.size() - 1;

//    for (const nodo& n : nodosEnComponente)

}

int dfs(nodo v, int d, nodo padre) {
    depth[v - 1] = d;
    low[v - 1] = d;
    if (v != padre)
        pila.push(edge(padre, v));

    for (const nodo& w : grafo[v - 1]) {
        if (w != padre) {
            if (depth[w - 1] == -1) {
                low[v - 1] = min(low[v - 1], dfs(w, d + 1, v));
                if (low[w - 1] >= depth[v - 1]) {
                    esArticulacion[v - 1] = true;
                    generarComponente(edge(v, w), v);
                }
                if (low[w - 1] >= depth[w - 1]) {
                    esPuente[edge(v, w)] = true;
                    esPuente[edge(w, v)] = true;
                }
            } else {
                low[v - 1] = min(low[v - 1], depth[w - 1]);
            }
        }
    }
    return low[v - 1];
}

int encontrar(nodo v, nodo buscado, int puentesPasados) {
    if (recorrido[v - 1])
        return 0;
    recorrido[v - 1] = true;
    if (v == buscado)
        return puentesPasados;
    for (const nodo& n : grafo[v - 1]) {
        int nuevoPuente = (esPuente[edge(v, n)]) ? 1 : 0;
        int res = encontrar(n, buscado, puentesPasados + nuevoPuente);
        if (res > 0) return res;
    }
    return 0;
}

void A() {
    int e1, e2;
    cin >> e1 >> e2;
    recorrido = vector<bool>(n, false);
    cout << encontrar(e1, e2, 0) << endl;
}

void B() {
    int calle;
    cin >> calle;
    eje e = ejes[calle - 1];
    if (esPuente[e])
        cout << 1 << endl;
    else
        cout << 0 << endl;
}

void C() {
    int esquina;
    cin >> esquina;
    cout << nodosEnLasMismasComponente[esquina - 1] << endl;
}

void createGraph() {
    dfs(1, 0, 1);
}

void init() {
    unsigned int m, u, v;
    cin >> n >> m;
    depth = vector<int>(n, -1);
    low = vector<int>(n);
    esArticulacion = vector<bool>(n, false);
    nodosEnLasMismasComponente = vector<int>(n, 0);
    grafo = vector<list<int>>(n);
    ejes = vector<eje>(m);
    forn(i, m) {
        cin >> u >> v;
        ejes[i] = edge(u, v);
        grafo[u - 1].push_back(v);
        grafo[v - 1].push_back(u);
    }
}

int main(int argc, char const *argv[]) {
    int q; char t;
     std::ifstream in("./Tests/friendship.in");
     std::cin.rdbuf(in.rdbuf());

    init();
    createGraph();
    cin >> q;
    forn(i, q) {
        cin >> t;
        if (t == 'A') A();
        else if (t == 'B') B();
        else if (t == 'C') C();
    }
    return 0;
}

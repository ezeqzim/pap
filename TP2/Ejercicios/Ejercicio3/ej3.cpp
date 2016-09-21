#include "../stdc++.h"
#include "ej3.h"
#include "pair_hash.cpp"

unsigned int n;
vector<eje> ejes;
vector<list<nodo> > grafo;
unordered_map<eje, bool, pair_hash> esPuente;
vector<unsigned int> nodosEnLaMismaComponente;

int main(int argc, char const *argv[]) {
    int q; char t;
    init();
    calcularPuentes();
    calcularComponentesK2();
    cin >> q;
    forn(i, q) {
        cin >> t;
        if (t == 'A') A();
        else if (t == 'B') B();
        else if (t == 'C') C();
    }
    return 0;
}

void calcularPuentes() {
    vector<int> depth(n, -1);
    vector<int> low(n);
    dfs(1, 0, 1, depth, low);
}

void calcularComponentesK2() {
    nodosEnLaMismaComponente = vector<unsigned int>(n, 0);
    vector<bool> visitado(n, false);
    forr (i, 1, n + 1) {
        list<nodo> nodosEnComp;
        nodosEnComponente(i, nodosEnComp, visitado);
        for (const nodo& v : nodosEnComp) {
            nodosEnLaMismaComponente[v - 1] = nodosEnComp.size() - 1;
        }
    }
}

void A() {
    int e1, e2;
    cin >> e1 >> e2;
    vector<bool>visitado (n, false);
    cout << encontrar(e1, e2, 0, visitado) << endl;
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
    cout << nodosEnLaMismaComponente[esquina - 1] << endl;
}

// ** AUXILIARES ** //

void init() {
    unsigned int m, u, v;
    cin >> n >> m;
    grafo = vector<list<nodo> >(n);
    ejes = vector<eje>(m);
    forn(i, m) {
        cin >> u >> v;
        ejes[i] = edge(u, v);
        grafo[u - 1].push_back(v);
        grafo[v - 1].push_back(u);
    }
}

int dfs(nodo v, int d, nodo padre, vector<int>& depth, vector<int>& low) {
    depth[v - 1] = d;
    low[v - 1] = d;
    for (const nodo& w : grafo[v - 1]) {
        if (w != padre) {
            if (depth[w - 1] == -1) {
                low[v - 1] = min(low[v - 1], dfs(w, d + 1, v, depth, low));
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

void nodosEnComponente(nodo v, list<nodo>& nodosEnComp, vector<bool>& visitado) {
    if (!visitado[v - 1]) {
        visitado[v - 1] = true;
        nodosEnComp.push_back(v);
        for (const nodo& w : grafo[v - 1]) {
            if (!esPuente[edge(v, w)]) {
                nodosEnComponente(w, nodosEnComp, visitado);
            }
        }
    }
}

int encontrar(nodo v, nodo buscado, int puentesPasados, vector<bool>& visitado) {
    if (visitado[v - 1])
        return 0;
    visitado[v - 1] = true;
    if (v == buscado)
        return puentesPasados;
    for (const nodo& n : grafo[v - 1]) {
        int nuevoPuente = (esPuente[edge(v, n)]) ? 1 : 0;
        int res = encontrar(n, buscado, puentesPasados + nuevoPuente, visitado);
        if (res > 0) return res;
    }
    return 0;
}

eje edge(nodo v, nodo w) {
    return make_pair(v, w);
}

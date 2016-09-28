#include "../stdc++.h"
#include "ej3.h"
#include "pair_hash.cpp"

unsigned int n;
vector<list<infoEje> > grafo;
vector<eje> esPuente;
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
    if (esPuente[calle - 1])
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
    grafo = vector<list<infoEje> >(n);
    esPuente = vector<eje>(m, false);
    forr(i, 1, m + 1) {
        cin >> u >> v;
        grafo[u - 1].push_back(info(i, v));
        grafo[v - 1].push_back(info(i, u));
    }
}

int dfs(nodo v, int d, nodo padre, vector<int>& depth, vector<int>& low) {
    depth[v - 1] = d;
    low[v - 1] = d;
    for (const infoEje& info : grafo[v - 1]) {
        eje e = info.first;
        nodo w = info.second;
        if (w != padre) {
            if (depth[w - 1] == -1) {
                low[v - 1] = min(low[v - 1], dfs(w, d + 1, v, depth, low));
                if (low[w - 1] >= depth[w - 1]) {
                    esPuente[e - 1] = true;
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
        for (const infoEje& info : grafo[v - 1]) {
            eje e = info.first;
            nodo w = info.second;
            if (!esPuente[e - 1]) {
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
    for (const infoEje& info : grafo[v - 1]) {
        eje e = info.first;
        nodo w = info.second;
        int nuevoPuente = (esPuente[e - 1]) ? 1 : 0;
        int res = encontrar(w, buscado, puentesPasados + nuevoPuente, visitado);
        if (res > 0) return res;
    }
    return 0;
}

infoEje info(eje e, nodo v) {
    return make_pair(e, v);
}

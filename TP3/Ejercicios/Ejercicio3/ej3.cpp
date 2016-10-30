#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int c, a, q;
vector<vector<ll> > memo;

void inicializar() {
  cin >> c >> a >> q;
  memo = vector<vector<ll> >(c + 1, vector<ll>(a + 1, 0));
}

void armar_memo() {
  ll val;
  forr(i, 1, c + 1) {
    forr(j, 1, a + 1) {
      cin >> val;
      memo[i][j] = val + memo[i - 1][j] + memo[i][j - 1] - memo[i - 1][j - 1];
    }
  }
}

void resolver_queries(){
  int c1, a1, c2, a2;
  forn(i, q) {
    cin >> c1 >> a1 >> c2 >> a2;
    ll res = memo[c2][a2] + memo[c1][a1] - memo[c2][a1] - memo[c1][a2];
    cout << res << endl;
  }
}

int main(int argc, char const *argv[]) {
  inicializar();
  armar_memo();
  resolver_queries();
  return 0;
}

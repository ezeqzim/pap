#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int c, a, q;
int c1, a1, c2, a2;
int res;
vector<vector<int> > memo;

void inicializar() {
  cin >> c >> a >> q;
  memo = vector<vector<int> >(c+1, vector<int>(a+1, 0));
}

void armar_memo() {
  forr(i, 1, c+1) {
    forr(j, 1, a+1) {
      int val;
      cin >> val;
      memo[i][j] = val + memo[i - 1][j] + memo[i][j - 1] - memo[i - 1][j - 1];
    }
  }
}

void resolver_queries(){
  forn(i, q) {
    cin >> c1 >> a1 >> c2 >> a2;
    res = memo[c2][a2] + memo[c1][a1] - memo[c2][a1] - memo[c1][a2];
    cout << res << endl;
  }
}

int main(int argc, char const *argv[]) {
  inicializar();
  armar_memo();
  resolver_queries();
  return 0;
}

#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

#define LEFT(n) (2*(n))
#define RIGHT(n) (2*(n)+1)
#define NEUTRO pair<int, int>(0, 0)

using namespace std;

int D;
vector<pair<int, int> > segTree;

pair<int, int> best2OutOf4(pair<int, int> a, pair<int, int> b) {
  vector<int> vec = { a.first, a.second, b.first, b.second };
  sort(vec.begin(), vec.end());
  return make_pair(vec[2], vec[3]);
}

void initSegTree() {
  for(int i = D - 1; i >= 1; i--)
    segTree[i] = best2OutOf4(segTree[LEFT(i)], segTree[RIGHT(i)]);
}

pair<int, int> query(int node, int left, int right, int a, int b) {
  if(a <= left && right <= b)
    return segTree[node];
  else if(b <= left || a >= right)
    return NEUTRO;
  int middle = (left + right) / 2;
  return best2OutOf4(query(LEFT(node), left, middle, a, b), query(RIGHT(node), middle, right, a, b));
}

int queryInterval(int a, int b) {
  pair<int, int> q = query(1, 0, D, a, b);
  return q.first + q.second;
}

int calculateCloserPow() {
  int log2D = log2(D);
  int closerPow = 1 << log2D;

  // Si D no era potencia de 2, closerPow quedó más chico que D.
  // Entonces lo multiplico por 2.
  if(D != closerPow)
    closerPow *= 2;

  return closerPow;
}

void initialize() {
  int closerPow = calculateCloserPow();

  // Multiplico closerPow * 2 para dejar espacio
  // para los nodos de construcción de intervalos
  segTree = vector<pair<int, int> >(closerPow * 2, make_pair(0, 0));

  forn(i, D)
    cin >> segTree[i + closerPow].first;

  D = closerPow;
}

void readQueries(int R) {
  int a, b;
  forn(i, R) {
    cin >> a >> b;
    cout << queryInterval(a, b) << endl;
  }
}

int main(int argc, char const *argv[]) {
  int R;
  cin >> D >> R;
  initialize();
  initSegTree();
  readQueries(R);
  return 0;
}

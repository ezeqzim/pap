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

pair<int, int> best2out4(pair<int, int> a, pair<int, int> b){
  vector<int> vec = { a.first, a.second, b.first, b.second };
  sort(vec.begin(), vec.end());
  return make_pair(vec[2], vec[3]);
}

void initSegTree(){
  for(int i = D-1; i >= 1; i--)
    segTree[i] = best2out4(segTree[LEFT(i)], segTree[RIGHT(i)]);
}

pair<int, int> query(int node, int left, int right, int a, int b) {
  if(a <= left && b >= right)
    return segTree[node];
  if(b <= left || a >= right)
    return NEUTRO;
  int middle = (left+right)/2;
  return best2out4(query(LEFT(node), left, middle, a, b), query(RIGHT(node), middle, right, a, b));
}

int queryInterval(int a, int b){
  pair<int, int> q = query(1, 0, D, a, b);
  return q.first + q.second;
}

int initialize(int R){
  int log2D = log2(D);
  int closerPow2 = 1 << log2D;
  // Si D es potencia de 2, no malgasto el espacio
  if(D % closerPow2 != 0)
    closerPow2 <<= 1;
  // Redondee para abajo...
  closerPow2 <<= 1;
  segTree = vector<pair<int, int> >(closerPow2, make_pair(0, 0));
  forn(i, D)
    cin >> segTree[i + closerPow2 / 2].first;
  return closerPow2 / 2;
}

void finish(int R){
  int a, b;
  forn(i, R){
    cin >> a >> b;
    cout << queryInterval(a, b) << endl;
  }
}

int main(int argc, char const *argv[]) {
  int R;
  cin >> D >> R;
  D = initialize(R);
  initSegTree();
  finish(R);
  return 0;
}

#include <bits/stdc++.h>
#include "matriz.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

int main(int argc, char const *argv[]) {
  int N, L;
  cin >> N >> L;
  Matriz res;
  cin >> res;
  vector<Matriz> matrices(N);
  forn(i, N)
    cin >> matrices[i];

  // fuerza bruta, cuadratica
  int posibles = N - L + 1;
  vector<Matriz> tmps(posibles);
  forn(i, posibles){
    tmps[i] = matrices[i];
    forr(j, 1, L)
      tmps[i] *= matrices[i + j];
    if(tmps[i] == res){
      cout << "SI" << endl;
      return 0;
    }
  }
  cout << "NO" << endl;
  return 0;
}

/*
3 2
1 0 0 0 1 0 0 0 1
2 0 0 0 1 0 0 0 3
1 1 1 2 2 2 3 3 3
0 1 0 1 0 0 0 0 1

NO

4 2
30 24 18 84 69 54 138 114 90
1 0 0 0 1 0 0 0 1
1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1
2 0 1 1 2 0 0 1 2

SI

4 3
1 0 0 0 1 0 0 0 1
5 0 0 0 5 0 0 0 5
1 0 0 0 1 0 0 0 1
4003 0 0 0 4003 0 0 0 4003
1 0 0 0 1 0 0 0 1

SI

4 2
30 24 18 84 69 54 138 114 90
1 2 3 4 5 6 7 8 9
1 0 0 0 1 0 0 0 1
9 8 7 6 5 4 3 2 1
2 0 1 1 2 0 0 1 2

NO
*/

#include <bits/stdc++.h>

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

vector<vector<int> > matrix;
vector<pair<bool, int> > fun;

int setToScore(int N, int mask){
  int sum = 0;
  forn(i, N)
    if((1<<i) == (mask&(1<<i)))
      forr(j, i+1, N)
        if((1<<j) == (mask&(1<<j)))
          sum += matrix[i][j];
  return sum;
}

int funScore(int N, int mask){
  if(fun[mask].first)
    return fun[mask].second;
  int res = 0;
  for(int i = mask&(mask-1); i != 0; i = mask&(i-1))
    res = max(res, max(funScore(N, mask^i) + funScore(N, i), setToScore(N, mask)));
  fun[mask] = pair<bool, int>(true, res);
  return res;
}

int main(int argc, char const *argv[]) {
  int N;
  cin >> N;
  matrix.resize(N, vector<int>(N));
  forn(i, N)
    forn(j, N)
      cin >> matrix[i][j];

  fun.resize(1<<N, pair<bool, int>(false, 0));
  fun[0] = pair<bool, int>(true, 0);
  cout << funScore(N, (1<<N) - 1) << endl;
  return 0;
}

/*
3
0 -1 1
-1 0 -1
1 -1 0

1

4
0 2 -1 0
2 0 0 -1
-1 0 0 2
0 -1 2 0

4

4
0 2 2 -1
2 0 0 2
2 0 0 2
-1 2 2 0

7
*/

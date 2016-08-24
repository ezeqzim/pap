#include <bits/stdc++.h>
#include "matriz.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

const int LEFT = -1;
const int RIGHT = 1;

using namespace std;

void linearSave(vector<Matriz>& memo, vector<Matriz>& matrices, int init, int end, int dir){
  if(dir == LEFT){
    memo.push_back(matrices[end]);
    int j = 0;
    for(int i = end-1; i >= init; --i){
      memo.push_back(matrices[i] * memo[j++]);
    }
  }
  else{
    memo.push_back(matrices[init]);
    int j = 0;
    for(int i = init+1; i <= end; ++i){
      memo.push_back(matrices[i] * memo[j++]);
    }
  }
}

pair<bool, vector<Matriz> > divideAndConquer(vector<Matriz>& matrices, int L, Matriz& M, int init, int end, int dir){
  if((end-init)+1 <= L){
    vector<Matriz> memo;
    linearSave(memo, matrices, init, end, dir);
    if((end-init)+1 == L)
      if(M == memo[L-1])
        return pair<bool, vector<Matriz> >(true, memo);
    return pair<bool, vector<Matriz> >(false, memo);
  }
  int half = (init+end)/2;
  pair<bool, vector<Matriz> > firstHalf = divideAndConquer(matrices, L, M, init, half, LEFT);
  if(firstHalf.first)
    return firstHalf;
  pair<bool, vector<Matriz> > secondHalf = divideAndConquer(matrices, L, M, half+1, end, RIGHT);
  if(secondHalf.first)
    return secondHalf;
  int size = min(firstHalf.second.size(), secondHalf.second.size());
  int i = 0, j = size-1;
  while(i+j+2 < L)
    i++;
  for(; i<size; ++i, --j)
    if(M == firstHalf.second[i] * secondHalf.second[i])
      return pair<bool, vector<Matriz> >(true, firstHalf.second);
  return firstHalf;
}

int main(int argc, char const *argv[]) {
  int N, L;
  cin >> N >> L;
  Matriz M;
  cin >> M;
  vector<Matriz> matrices(N);
  forn(i, N)
    cin >> matrices[i];
  if(divideAndConquer(matrices, L, M, 0, N-1, RIGHT).first)
    cout << "SI" << endl;
  else
    cout << "NO" << endl;

  // // fuerza bruta, cuadratica
  // int posibles = N - L + 1;
  // vector<Matriz> tmps(posibles);
  // forn(i, posibles){
  //   tmps[i] = id();
  //   forn(j, L)
  //     tmps[i] *= matrices[i + j];
  //   if(tmps[i] == M){
  //     cout << "SI" << endl;
  //     return 0;
  //   }
  // }
  // cout << "NO" << endl;
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

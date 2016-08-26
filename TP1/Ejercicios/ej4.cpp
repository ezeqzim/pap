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

bool divideAndConquer(vector<Matriz>& matrices, int L, Matriz& M, int init, int end, int dir, vector<Matriz>& memo){
  if((end-init)+1 <= L){
    linearSave(memo, matrices, init, end, dir);
    if((end-init)+1 == L)
      if(M == memo[L-1])
        return true;
    return false;
  }
  int half = (init+end)/2;
  vector<Matriz> firstHalfMemo;
  bool firstHalf = divideAndConquer(matrices, L, M, init, half, LEFT, firstHalfMemo);
  if(firstHalf)
    return firstHalf;
  vector<Matriz> secondHalfMemo;
  bool secondHalf = divideAndConquer(matrices, L, M, half+1, end, RIGHT, secondHalfMemo);
  if(secondHalf)
    return secondHalf;
  int size = min(firstHalfMemo.size(), secondHalfMemo.size());
  int i = 0, j = size-1;
  while(i+j+2 < L)
    i++;
  for(; i<size; ++i, --j)
    if(M == firstHalfMemo[i] * secondHalfMemo[i])
      return true;
  return false;
}

int main(int argc, char const *argv[]) {
  int N, L;
  cin >> N >> L;
  Matriz M;
  cin >> M;
  vector<Matriz> matrices(N);
  forn(i, N)
    cin >> matrices[i];
  vector<Matriz> memo;
  if(divideAndConquer(matrices, L, M, 0, N-1, RIGHT, memo))
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

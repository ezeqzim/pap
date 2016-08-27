#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

int main(int argc, char const *argv[]) {
  int N, val;
  cin >> N;

  int maximum = 0, tmp = 0;
  forn(i, N){
    cin >> val;
    tmp = max(val, tmp + val);
    if(maximum < tmp)
      maximum = tmp;
  }

  cout << maximum << endl;
  return 0;
}

/*
3
2 -1 2

3

4
-1 -1 -1 -1

0

14
1 2 3 4 5 -1 -2 -3 -4 -5 1 2 3 4

15

*/

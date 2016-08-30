#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

int main(int argc, char const *argv[]) {
  int N;
  ll val;
  cin >> N;

  ll maximum = 0, tmp = 0;
  forn(i, N){
    cin >> val;
    tmp = max(val, tmp + val);
    if(maximum < tmp)
      maximum = tmp;
  }

  cout << maximum << endl;
  return 0;
}

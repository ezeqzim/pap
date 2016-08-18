#include <bits/stdc++.h>

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

int main(int argc, char const *argv[]) {
  int N, val;
  cin >> N >> val;

  int maximum = 0, tmp = max(0, val);
  forr(i, 1, N){
    cin >> val;
    tmp = max(0, max(val, tmp + val));
    if(maximum < tmp)
      maximum = tmp;
  }

  cout << maximum << endl;
  return 0;
}

#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int contains(const string& S, const string& W){
	int ssize = S.size();
	int wsize = W.size();
	if(ssize < wsize) return false;
	vector<int> borders(wsize,0);
	borders[0] = -1;
	int pos = 2;
	int cnd = 0;
  while(pos < wsize){
    if(W[pos-1] == W[cnd]){
      borders[pos] = cnd + 1;
      cnd++;
      pos++;
    }
    else if(cnd > 0)
      cnd = borders[cnd];
    else {
      borders[pos] = 0;
      pos++;
    }
  }
	int i = 0;
	int m = 0;
	while(m + i < ssize){
    if(W[i] == S[m + i]){
      if(i == wsize - 1)
        return m;
      i++;
    }
    else
      if(borders[i] > -1){
        m += i - borders[i];
        i = borders[i];
      }
      else{
        m++;
        i = 0;
      }
  }
  return -1;
}

int main(int argc, char const *argv[]) {
  string nombre, apodo;
  cin >> nombre >> apodo;
  if(contains(nombre, apodo) > 0)
  	cout << "S";
  else
  	cout << "N";
  cout << endl;
  return 0;
}

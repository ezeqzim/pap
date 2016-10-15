#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int c, a, q;
int c1,a1,c2,a2;
int res;
vector<vector<int> > memo;
vector<vector<int> > m;

void inicializar(){
	cin >> c >> a >> q;
	m = vector<vector<int> >(c, vector<int>(a,0));
	memo = vector<vector<int> >(c+1, vector<int>(a+1,0));
}

void armar_matriz(){
	int val;
	forn(i,c){
		forn(j,a){
			cin >> val;
			m[i][j] = val;
		}
	}
}

void armar_memo(){
	forr(i,1,c+1){
		forr(j,1,a+1){
			memo[i][j] = m[i-1][j-1] + memo[i-1][j] + memo[i][j-1] - memo[i-1][j-1];
		}
	}
}

void resolver_queries(){
	forn(i,q){
		cin >> c1 >> a1 >> c2 >> a2;
		res = memo[c2][a2]+memo[c1][a1]-memo[c2][a1]-memo[c1][a2];
		cout << res << endl;
	}
}

int main(int argc, char const *argv[]) {
	inicializar();
	armar_matriz();
	armar_memo();
	resolver_queries();
	return 0;
}

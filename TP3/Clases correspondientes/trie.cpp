#include <bits/stdc++.h>

using namespace std;

class Trie{
	map<char,Trie*> hijos;
	bool final;	
public:
	Trie() {
		hijos.clear();
		final = false;
	}
	Trie(string &s, int pos) {
		hijos.clear();
		if(pos == s.size()) {
			final = true;
			return;
		}
		final = false;
		hijos[s[pos]] = new Trie(s,pos+1);
	}
	void insert(string &s, int pos = 0) {
		if(pos == s.size()) {
			final = true;
		} else if(hijos.find(s[pos]) == hijos.end()) {
			hijos[s[pos]] = new Trie(s,pos+1);
		} else {
			hijos[s[pos]]->insert(s,pos+1);
		}
		return;
	}
	bool find(string &s, int pos = 0) {
		if(pos == s.size()) {
			return final;
		} else if(hijos.find(s[pos]) == hijos.end()) {
			return false;
		} else {
			return hijos[s[pos]]->find(s,pos+1);
		}
	}
};

int main() {
	int n;
	cin >> n;
	Trie t;
	char c;
	string s;
	for(int i=0;i<n;i++) {
		cin >> c >> s;
		if(c == 'I') {
			//insertar
			t.insert(s);
		} else {
			//buscar
			if(t.find(s)) {
				cout << "SI" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
	}	
}
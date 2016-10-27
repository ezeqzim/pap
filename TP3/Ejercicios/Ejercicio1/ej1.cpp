#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

vector<int> borders;

void calculate_borders(const string& pattern){
	int size = pattern.size();
	borders.resize(size, 0);
	borders[0] = 0;
	int longest = 0;
	for(int index = 1; index < size; index++){
		while(longest > 0 && pattern[index] != pattern[longest])
			longest = borders[longest - 1];
		if(pattern[longest] == pattern[index])
			longest++;
		borders[index] = longest;
	}
}

bool matchs(const string& word, const string& pattern){
	int wordSize = word.size();
	int patternSize = pattern.size();
	int matched = 0;
	for(int i = 0; i < wordSize; i++){
		while(matched > 0 && pattern[matched] != word[i])
			matched = borders[matched - 1];
		if(pattern[matched] == word[i])
			matched++;
		if(matched == patternSize)
			return true;
	}
	return false;
}

int main(int argc, char const *argv[]) {
  string name, nickname;
  cin >> name >> nickname;
  calculate_borders(nickname);
  if(matchs(name, nickname))
  	cout << "S";
  else
  	cout << "N";
  cout << endl;
  return 0;
}

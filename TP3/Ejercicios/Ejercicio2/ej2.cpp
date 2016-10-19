#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

struct Node{
	//bool endOfWord;
	int maxAmountOfWords;
	map<char,Node> next;
	Node() : /*endOfWord(false), */maxAmountOfWords(0), next() {};
	/*bool*/void addWord(string& s, int index, int size){
		if(index == size){
		//	if(endOfWord) return false;
		//	else{
		//		endOfWord = true;
		//		return endOfWord;
		//	}
			return;
		}
		//else{

			map<char,Node>::iterator it;
			it = next.find(s[index]);
			//bool res;
			if(it != next.end()){
				/*res = */(*it).second.addWord(s,index+1,size);		
			}
			else{
				Node nextNode;
				/*res = */nextNode.addWord(s,index+1,size);
				next.insert(pair<char,Node>(s[index],nextNode));
			}
			//if(res){
				maxAmountOfWords++;
			//}
			//return res;
		//}
	};
	int getMaxAmountOfWords(){
		return maxAmountOfWords;
	};
};

class Trie{
	public:
		Trie() : next(), maxAmountOfWords(0) {}
		void updateMaxAmountOfWords(Node& n){
			maxAmountOfWords = max(n.getMaxAmountOfWords(), maxAmountOfWords);
		}
		void addWord(string& s, int index, int size){
			map<char,Node>::iterator it;
			it = next.find(s[index]);
			if(it != next.end()){
				(*it).second.addWord(s,index+1,size);
				updateMaxAmountOfWords((*it).second);
			}
			else{
				Node nextNode;
				nextNode.addWord(s,index+1,size);
				next.insert(pair<char,Node>(s[index],nextNode));
				updateMaxAmountOfWords(nextNode);
			}
		}
		int getMaxAmountOfWords(){
			return maxAmountOfWords;
		}
	private:
		map<char,Node> next;
		int maxAmountOfWords;
};

int main(int argc, char const *argv[]) {
	int students;
	cin >> students;
	Trie diccionary;
	for(int i = 0; i < students; i++){
		string mail;
		int prefix;
		cin >> mail >> prefix;
		diccionary.addWord(mail,0,prefix);
	}
	cout << diccionary.getMaxAmountOfWords() << endl;
	return 0;
}

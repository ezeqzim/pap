#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

struct Node{
	public:
		Node() : maxAmountOfWords(0), next() {};

		void addWord(string& s, int size, int index = 0){
			if(index != size){
				if(index == size-1)
					finished = true;
				map<char, Node>::iterator it = next.find(s[index]);
				if(it != next.end())
					it->second.addWord(s, size, index + 1);
				else{
					Node nextNode;
					nextNode.addWord(s, size, index + 1);
					next.insert(pair<char,Node>(s[index], nextNode));
				}
			}
			maxAmountOfWords++;
		};

		int getMaxAmountOfWordsFromPrefix(){
			int maximum = 0;
			for(map<char, Node>::iterator it = next.begin(); it != next.end(); ++it){
				if(finished)
					maximum = max(maximum, it->second.maxAmountOfWords);
				maximum = max(maximum, it->second.getMaxAmountOfWordsFromPrefix());
			}
			return maximum;
		};

	private:
		int maxAmountOfWords;
		bool finished = false;
		map<char, Node> next;
};

class Trie{
	public:
		Trie() : root() {};

		void addWord(string& s, int size){
			root.addWord(s, size);
		}

		int getMaxAmountOfWordsFromPrefix(){
			root.getMaxAmountOfWordsFromPrefix();
		}

	private:
		Node root;
};


void initialize(Trie& dictionary){
	int students;
	cin >> students;
	for(int i = 0; i < students; i++){
		string mail;
		int prefix;
		cin >> mail >> prefix;
		dictionary.addWord(mail, prefix);
	}
}

int main(int argc, char const *argv[]) {
	Trie dictionary;
	initialize(dictionary);
	cout << dictionary.getMaxAmountOfWordsFromPrefix() << endl;
	return 0;
}

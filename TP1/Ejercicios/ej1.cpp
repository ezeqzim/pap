#include <bits/stdc++.h>

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

void generateParts(vector<int>& v, int num){
  int size = v.size();
  v.push_back(num);
  forn(i, size){
     v.push_back(num+v[i]);
  }
}

int getMax(vector<int>& first, vector<int>& second, int limit){
  int max = 0, sum;
  int j = second.size()-1;
  forn(i, first.size()){
    while(first[i] + second[j] > limit && j > 0) j--;
    sum = first[i]+second[j];
    if(sum > limit) return max;
    if(sum > max) max = sum;
  }
  return max;
}

int main() {
  int P, N;
  cin >> P >> N;
  int half = N/2;
  vector<int> fpacks;
  vector<int> spacks;
  int num;
  forn(i, N){
    cin >> num;
    if(i < half)
      generateParts(fpacks, num);
    else
      generateParts(spacks, num);
  }
  fpacks.push_back(0);
  spacks.push_back(0);
  sort(fpacks.begin(), fpacks.end());
  sort(spacks.begin(), spacks.end());
  cout << getMax(fpacks, spacks, P) << endl;
  return 0;
}

/*
10 4
3 3 3 3

9

12 5
1 2 3 4 5

12
*/

#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

void generateParts(vector<ll>& v, int num, int iter){
  //La posicion donde agregar el nuevo elemento
  //(o sea, desde 0..size esta todo lo que fui calculando)
  int size = (1<<iter)-1;
  v[size] = num;
  //Recorre todo lo que ya calcule
  forn(i, size){
    //Y lo guarda en las posiciones siguientes
    v[size+i+1] = num+v[i];
  }
}

//OLD GENERATEPARTS
//void generateParts(vector<ll>& v, int num){
//  int size = v.size();
//  v.push_back(num);
//  forn(i, size){
//    v.push_back(num+v[i]);
//  }
//}

int getMax(vector<ll>& first, vector<ll>& second, int limit){
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
  //Guarda 2^(n/2) en cada arreglo, para guardar las partes
  vector<ll> firstHalf((1<<half)+1);
  vector<ll> secondHalf((1<<(N-half))+1);
  int num;
  forn(i, N){
    cin >> num;
    if(i < half)
      //Pasa el i como parametro para saber en que iteracion esta
      generateParts(firstHalf, num, i);
    else
      generateParts(secondHalf, num, i-half);
  }
  firstHalf[1<<half] = 0;
  secondHalf[1<<(N-half)] = 0;
  sort(firstHalf.begin(), firstHalf.end());
  sort(secondHalf.begin(), secondHalf.end());
  cout << getMax(firstHalf, secondHalf, P) << endl;
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

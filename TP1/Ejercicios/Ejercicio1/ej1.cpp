#include "../stdc++.h"

typedef long long ll;
#define forr(i,a,b) for(int i=(a); i<(b); ++i)
#define forn(i,n) forr(i,0,n)

using namespace std;

void generateParts(vector<ll>& v, int num, int iter){
  int size = (1<<iter)-1; //La posicion donde agregar el nuevo elemento (o sea, desde 0..size esta todo lo que fui calculando)
  v[size] = num;
  forn(i, size){ //Recorro todo lo que ya calcule
     v[size+i+1] = num+v[i]; //Y lo guardo en las posiciones siguientes
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
  vector<ll> fpacks(1<<half); //Me guardo 2^(n/2) en cada arreglo, para guardar las partes
  vector<ll> spacks(1<<(N-half));
  int num;
  forn(i, N){
    cin >> num;
    if(i < half)
      generateParts(fpacks, num, i);//Paso el i como parametro para saber en que iteracion estoy
    else
      generateParts(spacks, num, i-half);
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

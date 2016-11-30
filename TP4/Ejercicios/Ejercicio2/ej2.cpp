#include "../stdc++.h"
//#include <algorithm>

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int n;
vector<int> arr;
vector<int> mins;
vector<double> p;
vector<vector<double> > chanchimatriz;
vector<double> numeroDePasos;

void inicializar(){
	cin >> n;
	arr = vector<int>(n,0);
	mins = vector<int>(n,0);
	p = vector<double>(n,0);
	numeroDePasos = vector<double>(n,0);
	chanchimatriz = vector<vector<double> >(n, vector<double>(n, 0));
	forn(i,n){
		cin >> arr[i];
	}
}

void calcularMins(){
	int last = arr[n-1];
	mins[n-1] = 1;
	for(int i = n-2; i>=0; i--){
		if(arr[i] == last){
			mins[i] = mins[i+1]+1;
		}
		else{
			mins[i]=1;
			last=arr[i];
		}
	}
}

void calcularPs(){
	forn(i,n){
		p[i] = (float) mins[i]/ (float)(n-i);
	}	
}

void armarChanchiMatriz(){
	double chanchivalor = 1;
	for(int i=n-1; i>=0; i--){
		for(int j=n-1; j>=i;j--){
			chanchivalor = 1;
			for(int z=i;z<=j-1;z++){         // Esto es O(N) y debería ser O(1)
				chanchivalor*= p[z];
			}
			if (j!= n-1) chanchivalor*=(1-p[j]);
			chanchimatriz[i][j] = chanchivalor;
		}
	}
}

void armarChanchiMatriz2(){
	double chanchivalor = 1;
	for(int i=n-1; i>=0; i--){
		for(int j=i; j<=n-1;j++){
			if (j==i)chanchimatriz[i][j] = 1-p[i];
			else {
				double proba = (p[j-1] == 1 ? 1 : (1-p[j-1]));
				if (j==n-1)
					chanchimatriz[i][j] = ((chanchimatriz[i][j-1]) / proba)*p[j-1];
				else
					chanchimatriz[i][j] = ((chanchimatriz[i][j-1]) / proba)*p[j-1]*(1-p[j]);
			}
		}
	}
	chanchimatriz[n-1][n-1]=1;
}

double obtenerEsperanza(){
	for(int i=n-2; i>=0; i--){
		double row = 0;
		for(int j=i+1; j<=n-1;j++){
			row += numeroDePasos[j]*chanchimatriz[i][j];
		}
		numeroDePasos[i] = (row+1) / p[i];
	}
	return numeroDePasos[0];
}

int main(int argc, char const *argv[]) {

	inicializar();
	if (n == 1){
		cout << 1 << endl;
		return 0;
	}
	sort(arr.begin(), arr.end()); // Ordenar el array (NlogN)
	calcularMins(); // Calcular la cantidad de minimos en cada paso (hacer caso borde si el arreglo tiene un elem) (N)
	calcularPs(); 	// Calcular P_is para todos los i (N)
	armarChanchiMatriz2(); // Armar chanchimatriz (N^3) :(      (quizas tengamos que hacer una tabla aditiva)
	//resolverSistema();  // Resuelve el sistema M*E = E - 1

	forn(i,n){
		forn(j,n){
			cout << chanchimatriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << fixed << setprecision(6) << obtenerEsperanza() << endl;

  return 0;
}
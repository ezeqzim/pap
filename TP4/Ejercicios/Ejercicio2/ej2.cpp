#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

int n;
vector<int> arr;
vector<int> mins;
vector<double> p;
vector<vector<double> > probabilidades;
vector<double> numeroDePasos;

void inicializar() {
  cin >> n;
  arr = vector<int>(n, 0);
  mins = vector<int>(n, 0);
  p = vector<double>(n, 0);
  numeroDePasos = vector<double>(n, 0);
  probabilidades = vector<vector<double> >(n, vector<double>(n, 0));
  forn(i, n)
    cin >> arr[i];
}

void calcularMins() {
  int last = arr[n - 1];
  mins[n - 1] = 1;
  for(int i = n - 2; i >= 0; --i) {
    if(arr[i] == last)
      mins[i] = mins[i + 1] + 1;
    else {
      mins[i] = 1;
      last = arr[i];
    }
  }
}

void calcularPs() {
  forn(i, n)
    p[i] = (float)mins[i]/ (float)(n - i);
}

void generarProbabilidades() {
  probabilidades[n-1][n-1] = 1;
  for(int i = n - 2; i >= 0; --i) {
    forr(j, i, n) {
      if (j == i)
        probabilidades[i][j] = 1 - p[i];
      else
        probabilidades[i][j] = p[i] * probabilidades[i+1][j];
    }
  }
}

double obtenerEsperanza() {
  for(int i = n - 2; i >= 0; --i) {
    double row = 0;
    forr(j, i + 1, n)
      row += numeroDePasos[j]*probabilidades[i][j];
    numeroDePasos[i] = (row + 1) / p[i];
  }
  return numeroDePasos[0];
}

int main(int argc, char const *argv[]) {

  inicializar();
  if (n == 1) {
    cout << fixed << setprecision(6) << 1.0 << endl;
    return 0;
  }
  sort(arr.begin(), arr.end());
  calcularMins();
  calcularPs();
  generarProbabilidades();
  cout << fixed << setprecision(6) << obtenerEsperanza() << endl;

  return 0;
}

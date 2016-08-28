#include <vector>
#include "matriz.h"

typedef long long ll;
#define forr(i, a, b) for(int i = a; i < b; ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

const int LEFT = -1;
const int RIGHT = 1;

int N, L;
vector<Matriz> matrices;
Matriz M;

// TODO: SACAR LOS PUSH_BACK

void linearSave(vector<Matriz>& memo, int init, int end, int dir) {
    if (dir == LEFT) {
        memo.push_back(matrices[end]);
        for (int j = 0; end - j - 1 >= init; j++)
            memo.push_back(matrices[end - j - 1] * memo[j]);
    } else {
        memo.push_back(matrices[init]);
        for (int j = 0; init + j + 1 <= end; j++)
            memo.push_back(memo[j] * matrices[init + j + 1]);
    }
}

bool divideAndConquer(int init, int end, int dir, vector<Matriz>& memo) {
    if(end - init <= L - 1) {
        linearSave(memo, init, end, dir);
        return end - init == L - 1 && M == memo[L - 1];
    }

    int half = (init + end) / 2;

    vector<Matriz> firstHalfMemo;
    if (divideAndConquer(init, half, LEFT, firstHalfMemo))
        return true;

    vector<Matriz> secondHalfMemo;
    if (divideAndConquer(half + 1, end, RIGHT, secondHalfMemo))
        return true;

    int size = min(firstHalfMemo.size(), secondHalfMemo.size());
    for (int i = L - size - 1, j = size - 1; i < size; i++, j--)
        if (M == firstHalfMemo[i] * secondHalfMemo[j])
            return true;

    return false;
}

void init() {
    cin >> N >> L;
    cin >> M;
    matrices = vector<Matriz>(N);
    forn(i, N)
        cin >> matrices[i];
}

int main(int argc, char const *argv[]) {
    init();
    vector<Matriz> memo;
    if (divideAndConquer(0, N - 1, RIGHT, memo))
        cout << "SI" << endl;
    else
        cout << "NO" << endl;
    return 0;
}

  // // fuerza bruta, cuadratica
  // int posibles = N - L + 1;
  // vector<Matriz> tmps(posibles);
  // forn(i, posibles){
  //   tmps[i] = id();
  //   forn(j, L)
  //     tmps[i] *= matrices[i + j];
  //   if(tmps[i] == M){
  //     cout << "SI" << endl;
  //     return 0;
  //   }
  // }
  // cout << "NO" << endl;

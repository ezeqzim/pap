#include "matriz.h"

#define forr(i, a, b) for(int i = a; i < b; ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

const int LEFT = -1;
const int RIGHT = 1;

int N, L;
vector<Matriz> matrices;
Matriz M;

void linearSave(int init, int end, int dir, vector<Matriz>& memo) {
    if (dir == LEFT) {
        memo.push_back(matrices[end]);
        for (int j = 0; j < L && end - j - 1 >= init; j++)
            memo.push_back(matrices[end - j - 1] * memo[j]);
    } else {
        memo.push_back(matrices[init]);
        for (int j = 0; j < L && init + j + 1 <= end; j++)
            memo.push_back(memo[j] * matrices[init + j + 1]);
    }
}

bool divideAndConquer(int init, int end, int dir, vector<Matriz>& memo) {
    linearSave(init, end, dir, memo);
    if (end - init < L - 1)
        return false;
    else if (end - init == L - 1)
        return M == memo[L - 1];

    int half = (init + end) / 2;
    vector<Matriz> firstHalfMemo, secondHalfMemo;

    if (divideAndConquer(init, half, LEFT, firstHalfMemo) || divideAndConquer(half + 1, end, RIGHT, secondHalfMemo))
        return true;

    int size = min(firstHalfMemo.size(), secondHalfMemo.size());
    int start, finish;
    if (L <= size) {
        // Si L es menor que el tamaño, me aseguro de no pasarme de L.
        start = 0;
        finish = L - 1;
    } else {
        // Si L es mayor que el tamaño, entonces no sirve empezar en 0
        // y tengo que terminar en size. Si me paso de size, falla.
        start = L - size - 1;
        finish = size;
    }

    for (int i = start; finish - (i + 1) >= 0; i++)
        if (M == firstHalfMemo[finish - (i + 1)] * secondHalfMemo[i])
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

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
        memo.push_back(matrices.at(end));
        for (int j = 0; j < L && end - j - 1 >= init; j++)
            memo.push_back(matrices.at(end - j - 1) * memo.at(j));
    } else {
        memo.push_back(matrices.at(init));
        for (int j = 0; j < L && init + j + 1 <= end; j++)
            memo.push_back(memo.at(j) * matrices.at(init + j + 1));
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

    for (int i = L - size, j = size - 1; i < size; i++, j--)
        if (M == firstHalfMemo.at(i) * secondHalfMemo.at(j))
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

#include <iostream>
#include <vector>
using namespace std;
/*
완전탐색문제 -> 순열인지 조합인지 확인하기!!
행렬 cache 히트율 고려하여 for문 수행하기
*/
int N, M, H;
int ladder[11][31];

bool check() {
    for (int i = 1; i <= N; i++) {
        int pos = i;
        for (int j = 1; j <= H; j++) {
            if (ladder[pos][j] == 1)
                pos++;
            else if (pos != 0 && ladder[pos - 1][j] == 1)
                pos--;
        }
        if (pos != i)
            return false;
    }
    return true;
}

bool solve(int cnt, int x, int y) {
    if (cnt == 0) {
        return check();
    }
    for (int i = x; i <= H; i++) {
        for (int j = y; j < N; j++) {
            if (ladder[j][i] == 0 && ladder[j - 1][i] == 0 && ladder[j + 1][i] == 0) {
                ladder[j][i] = 1;
                if (solve(cnt - 1, i, j + 2))
                    return true;
                ladder[j][i] = 0;
            }
        }
        y = 1;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> H;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        ladder[b][a] = 1;
    }

    for (int i = 0; i <= 3; i++) {
        if (solve(i, 1, 1)) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';

    return 0;
}
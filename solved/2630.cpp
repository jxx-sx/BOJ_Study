#include <iostream>

using namespace std;

int N, white = 0, blue = 0;
bool **arr;

bool check(int a, int b, int n) {
    bool tmp = arr[a][b];
    for (int i = a; i < a + n; i++) {
        for (int j = b; j < b + n; j++) {
            if (tmp != arr[i][j]) {
                return true;
            }
        }
    }
    if (tmp) {
        blue += 1;
    } else {
        white += 1;
    }
    return false;
}

void solve(int a, int b, int n) {
    if (check(a, b, n)) {
        solve(a, b, n / 2);
        solve(a + n / 2, b, n / 2);
        solve(a, b + n / 2, n / 2);
        solve(a + n / 2, b + n / 2, n / 2);
    }
}

void init() {
    int tmp;
    cin >> N;
    arr = new bool *[N];
    for (int i = 0; i < N; i++) {
        arr[i] = new bool[N];
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve(0, 0, N);
    cout << white << '\n' << blue;
}
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[8][31];
int n;

void init() {
    arr[3][1] = arr[6][1] = arr[7][0] = 1;
    cin >> n;
}

void solve() {
    for (int i = 2; i <= n; i++) {
        arr[1][i] = arr[6][i - 1];
        arr[2][i] = arr[5][i - 1];
        arr[3][i] = arr[7][i - 1] + arr[4][i - 1];
        arr[4][i] = arr[3][i - 1];
        arr[5][i] = arr[2][i - 1];
        arr[6][i] = arr[7][i - 1] + arr[1][i - 1];
        arr[7][i] = arr[7][i - 2] + arr[6][i - 1] + arr[3][i - 1];
    }
    cout << arr[7][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
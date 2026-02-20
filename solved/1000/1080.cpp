#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m, cnt;
char arr[50][50], brr[50][50];

void c(int x, int y) {
    for (int i = x; i < x + 3; i++)
        for (int j = y; j < y + 3; j++)
            arr[i][j] ^= 1;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> brr[i][j];
}

void solve() {
    for (int i = 0; i < n - 2; i++)
        for (int j = 0; j < m - 2; j++)
            if (arr[i][j] != brr[i][j])
                c(i, j), cnt++;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (arr[i][j] != brr[i][j]) {
                cout << -1;
                return;
            }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}
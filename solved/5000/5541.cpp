#include <iostream>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[5002][5002];
int n, m;

void init() {
    int a, b, x;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> x;
        arr[a][b] = max(arr[a][b], x + 1);
    }
}

void solve() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (arr[i][j]) {
                cnt++;
                arr[i + 1][j] = max(arr[i][j] - 1, arr[i + 1][j]);
                arr[i + 1][j + 1] = max(arr[i][j] - 1, arr[i + 1][j + 1]);
            }
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
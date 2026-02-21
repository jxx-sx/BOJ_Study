#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[21][10001], coins[21];
int tc, n, m;

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> coins[i];
    cin >> m;
}

void solve() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            arr[i][j] = arr[i - 1][j];
            for (int k = 1; j - k * coins[i] >= 0; k++)
                arr[i][j] += arr[i - 1][j - k * coins[i]];
        }
    cout << arr[n][m] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    for (int i = 0; i < 21; i++)
        arr[i][0] = 1;
    cin >> tc;
    while (tc--)
        init(), solve();

    return 0;
}
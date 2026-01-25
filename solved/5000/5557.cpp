#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, x;
long long dp[21][100];

void init() {
    cin >> n;
    cin >> x;
    dp[x][0] = 1;
}

void solve() {
    for (int i = 1; i < n - 1; i++) {
        cin >> x;
        for (int j = 0; j < 21 - x; j++)
            dp[j][i] += dp[j + x][i - 1];
        for (int j = x; j < 21; j++)
            dp[j][i] += dp[j - x][i - 1];
    }
    cin >> x;
    cout << dp[x][n - 2];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
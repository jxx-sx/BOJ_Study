#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

long long dp[4][100001];
int tc, n;

void init() { dp[1][1] = dp[2][2] = dp[1][0] = 1; }

void solve() {
    for (int i = 3; i < 100001; i++) {
        dp[1][i] = (dp[2][i - 1] + dp[3][i - 1]) % 1000000009;
        dp[2][i] = (dp[1][i - 2] + dp[3][i - 2]) % 1000000009;
        dp[3][i] = (dp[1][i - 3] + dp[2][i - 3]) % 1000000009;
    }
    cin >> tc;
    while (tc--) {
        cin >> n;
        cout << (dp[1][n] + dp[2][n] + dp[3][n]) % 1000000009 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
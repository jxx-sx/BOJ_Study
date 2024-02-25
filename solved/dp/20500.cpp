#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dp[1516][15];
int n;

void init() {
    dp[1][5] = dp[1][1] = 1;
    cin >> n;
}

void solve() {
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 15; j++) {
            for (auto a : {1, 5}) {
                dp[i][(j * 10 + a) % 15] += dp[i - 1][j];
                dp[i][(j * 10 + a) % 15] %= 1000000007;
            }
        }
    }
    cout << dp[n][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
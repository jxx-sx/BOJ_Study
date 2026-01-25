#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dp[10001];
int tc, n;

void init() {
    for (int i = 0; i <= 10000; i++)
        dp[i] = 1;
}

void solve() {
    for (int i = 2; i <= 10000; i++)
        dp[i] += dp[i - 2];
    for (int i = 3; i <= 10000; i++)
        dp[i] += dp[i - 3];
    cin >> tc;
    while (tc--) {
        cin >> n;
        cout << dp[n] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <iostream>

using namespace std;

int dp[46][2];
int n;

void init() {
    dp[0][0] = 1;
    for (int i = 1; i < 46; i++) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
    }
    cin >> n;
}

void solve() { cout << dp[n][0] << ' ' << dp[n][1]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
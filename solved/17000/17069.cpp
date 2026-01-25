#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[33][33];
long long dp[3][33][33];
int n;
void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> arr[i][j];
    dp[0][1][2] = 1;
}

void solve() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (!arr[i][j]) {
                dp[0][i][j] += dp[0][i][j - 1] + dp[1][i][j - 1];
                dp[2][i][j] += dp[1][i - 1][j] + dp[2][i - 1][j];
            }
            if (!(arr[i][j] | arr[i - 1][j] | arr[i][j - 1]))
                dp[1][i][j] += dp[0][i - 1][j - 1] + dp[1][i - 1][j - 1] + dp[2][i - 1][j - 1];
        }
    cout << dp[0][n][n] + dp[1][n][n] + dp[2][n][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
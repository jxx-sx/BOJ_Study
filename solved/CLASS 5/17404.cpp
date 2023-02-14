#include <iostream>

using namespace std;

int n;
int r, g, b;
int dp[1000][3][3];

void dp_solve(int k) {
    cin >> r >> g >> b;
    for (int i = 0; i < 3; i++) {
        dp[k][0][i] = min(dp[k - 1][1][i], dp[k - 1][2][i]) + r;
        dp[k][1][i] = min(dp[k - 1][0][i], dp[k - 1][2][i]) + g;
        dp[k][2][i] = min(dp[k - 1][0][i], dp[k - 1][1][i]) + b;
    }
}

void solve() {
    for (int i = 1; i < n; i++)
        dp_solve(i);
    int ans = 1000001;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i != j)
                ans = min(ans, dp[n - 1][i][j]);
    cout << ans;
}

void init() {
    cin >> n;
    cin >> r >> g >> b;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            dp[0][i][j] = 1000001;

    dp[0][0][0] = r;
    dp[0][1][1] = g;
    dp[0][2][2] = b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}
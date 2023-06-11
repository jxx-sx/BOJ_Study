#include <iostream>

using namespace std;

int n;
int dp[101][10][10];
void init() {
    cin >> n;
    for (int i = 1; i < 10; i++)
        dp[1][i][i] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 1; k < 10; k++)
                dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k - 1]) % 1000000000;
            for (int k = 0; k < 9; k++)
                dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k + 1]) % 1000000000;
        }
    }
}

void solve() {
    int ans = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            ans = (ans + dp[n][i][j]) % 1000000000;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
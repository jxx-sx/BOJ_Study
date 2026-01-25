#include <iostream>

using namespace std;

int t, w;
int dp[1001][31];

void init() { cin >> t >> w; }

void solve() {
    int tree;
    for (int i = 1; i <= t; i++) {
        cin >> tree;
        dp[i][0] = dp[i - 1][0] + (tree & 1);
        for (int j = 1; j <= min(w, i); j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + ((tree & 1) ^ (j & 1));
        }
    }
    int ans = 0;
    for (int i = 0; i <= w; i++)
        ans = max(ans, dp[t][i]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
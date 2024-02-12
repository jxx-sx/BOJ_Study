#include <cassert>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m, ans;
pair<int, int> arr[101];
int dp[101][10001];

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].first;
        ans += arr[i].first;
    }
    for (int i = 1; i <= n; i++)
        cin >> arr[i].second;
}

void solve() {
    for (int i = 0; i < 10001; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[j - 1][i];
            if
                7579.cpp(i > 0) dp[j][i] = max(dp[j][i], dp[j][i - 1]);
            if (i >= arr[j].second)
                dp[j][i] = max(dp[j][i], dp[j - 1][i - arr[j].second] + arr[j].first);
            if (dp[j][i] >= m) {
                cout << i;
                return;
            }
        }
    }
    // cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
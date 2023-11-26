#include <iostream>

#define N 1500002

using namespace std;
int n;
int t[N];
int p[N];
int dp[N];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i] >> p[i];
}

void solve() {
    for (int i = 1; i <= n + 1; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
        if (i + t[i] < n + 2)
            dp[i + t[i]] = max(dp[i + t[i]], dp[i] + p[i]);
    }
    cout << dp[n + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
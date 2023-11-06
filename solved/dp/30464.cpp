#include <iostream>

using namespace std;

long long arr[202020];
long long dp[3][202020];
int n;

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
}

void solve() {
    dp[0][1] = 1;
    for (int i = 1; i < n; i++) {
        if (!dp[0][i])
            continue;
        if (i + arr[i] <= n)
            dp[0][i + arr[i]] = max(dp[0][i + arr[i]], dp[0][i] + 1);
        if (i != n and i - arr[i] > 0)
            dp[1][i - arr[i]] = max(dp[1][i - arr[i]], dp[0][i] + 1);
    }

    for (int i = n - 1; i > 0; i--) {
        if (!dp[1][i])
            continue;
        if (i - arr[i] > 0)
            dp[1][i - arr[i]] = max(dp[1][i - arr[i]], dp[1][i] + 1);
        if (i + arr[i] <= n)
            dp[2][i + arr[i]] = max(dp[2][i + arr[i]], dp[1][i] + 1);
    }

    for (int i = 1; i < n; i++) {
        if (!dp[2][i])
            continue;
        if (i + arr[i] <= n)
            dp[2][i + arr[i]] = max(dp[2][i + arr[i]], dp[2][i] + 1);
    }

    cout << max(dp[0][n], dp[2][n]) - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
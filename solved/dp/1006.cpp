#include <iostream>

#define N 10001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, w;
int arr[2][N], dp[3][N];

void init() {
    cin >> n >> w;
    for (int i = 1; i <= n; i++)
        cin >> arr[0][i];
    for (int i = 1; i <= n; i++)
        cin >> arr[1][i];
    arr[0][0] = arr[1][0] = w;
}

int get_dp() {
    dp[0][0] = arr[0][0] + arr[1][0] <= w ? 1 : 2;
    dp[1][0] = dp[2][0] = 1;

    dp[0][1] = dp[0][0] + (arr[0][1] + arr[1][1] <= w ? 1 : 2);
    dp[1][1] = dp[2][1] = dp[0][0] + 1;
    if (arr[0][0] + arr[0][1] <= w) {
        dp[0][1] = min(dp[0][1], dp[2][0] + 2);
        dp[1][1] = min(dp[1][1], dp[2][0] + 1);
    }
    if (arr[1][0] + arr[1][1] <= w) {
        dp[0][1] = min(dp[0][1], dp[1][0] + 2);
        dp[2][1] = min(dp[2][1], dp[1][0] + 1);
    }
    if (arr[0][0] + arr[0][1] <= w && arr[1][0] + arr[1][1] <= w)
        dp[0][1] = min(dp[0][1], 2);

    for (int i = 2; i <= n; i++) {
        // 0
        dp[0][i] = dp[0][i - 1] + (arr[0][i] + arr[1][i] <= w ? 1 : 2);
        dp[1][i] = dp[2][i] = dp[0][i - 1] + 1;
        if (arr[0][i - 1] + arr[0][i] <= w) {
            dp[0][i] = min(dp[0][i], dp[2][i - 1] + 2);
            dp[1][i] = min(dp[1][i], dp[2][i - 1] + 1);
        }
        if (arr[1][i - 1] + arr[1][i] <= w) {
            dp[0][i] = min(dp[0][i], dp[1][i - 1] + 2);
            dp[2][i] = min(dp[2][i], dp[1][i - 1] + 1);
            if (arr[0][i - 1] + arr[0][i] <= w && arr[1][i - 1] + arr[1][i] <= w)
                dp[0][i] = min(dp[0][i], dp[0][i - 2] + 2);
        }
    }
    return dp[0][n];
}

void solve() {
    int ans = 2 * n + 2;
    ans = min(ans, get_dp());
    swap(arr[0][0], arr[0][n]);
    ans = min(ans, get_dp());
    swap(arr[1][0], arr[1][n]);
    ans = min(ans, get_dp());
    swap(arr[0][0], arr[0][n]);
    ans = min(ans, get_dp());
    cout << ans - 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--)
        init(), solve();

    return 0;
}
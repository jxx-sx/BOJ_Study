#include <algorithm>
#include <iostream>

using namespace std;

int arr[100001], dp[2][100001];
int n, mx;

void init() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
}

void solve() {
    if (arr[1] > 0)
        dp[0][1] = arr[1];
    mx = arr[1];
    for (int i = 2; i <= n; i++) {
        dp[0][i] = max(dp[0][i - 1] + arr[i], arr[i]);
        dp[1][i] = max({dp[0][i - 2] + arr[i], dp[0][i - 1], dp[1][i - 1] + arr[i]});
        mx = max({mx, dp[0][i], dp[1][i]});
    }
    cout << mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
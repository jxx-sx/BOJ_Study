#include <iostream>

using namespace std;

int n;
int arr[1000];
int dp[1000];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        dp[i] = -1;
    }
}

void solve() {
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        if (dp[i] != -1)
            for (int j = 1; j <= arr[i]; j++) {
                if (i + j >= n)
                    break;
                dp[i + j] = dp[i + j] == -1 ? dp[i] + 1 : min(dp[i] + 1, dp[i + j]);
            }
    cout << dp[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
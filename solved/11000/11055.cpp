#include <iostream>

using namespace std;

int n;
int arr[1000];
int dp[1000];
int ans;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + arr[i]);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
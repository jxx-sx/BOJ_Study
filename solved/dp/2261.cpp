#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dp[10001];
int arr[100];
int n, k;

void init() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    dp[0] = 1;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = arr[i]; j <= k; j++)
            dp[j] += dp[j - arr[i]];
    }
    cout << dp[k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
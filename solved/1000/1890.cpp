#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n;
long long arr[100][100];
long long dp[100][100];

void init() {
    dp[0][0] = 1;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
}

void solve() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (arr[i][j]) {
                if (i + arr[i][j] < n)
                    dp[i + arr[i][j]][j] += dp[i][j];
                if (j + arr[i][j] < n)
                    dp[i][j + arr[i][j]] += dp[i][j];
            }
        }
    cout << dp[n - 1][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
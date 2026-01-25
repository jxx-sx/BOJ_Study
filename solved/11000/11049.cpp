#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> v;
int arr[501];
int dp[501][501];

void solve() {
    int tmp;
    for (int j = 1; j < n; j++) {
        for (int i = 0; i + j < n; i++) {
            for (int k = i; k < i + j; k++) {
                tmp = dp[i][k] + dp[k + 1][i + j] + arr[i] * arr[k + 1] * arr[i + j + 1];
                if (dp[i][i + j] == 0)
                    dp[i][i + j] = tmp;
                dp[i][i + j] = min(dp[i][i + j], tmp);
            }
        }
    }

    cout << dp[0][n - 1];
}

void init() {
    int s, e;
    cin >> n;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;

    cin >> arr[0] >> arr[1];
    for (int i = 1; i < n; i++) {
        cin >> s >> e;
        arr[i + 1] = e;
    }

    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> v;
int arr[501];
int dp[501][501];

void solve() {
    int tmp;
    for (int j = 2; j <= n; j++) {
        for (int i = 0; i + j <= n; i++) {
            for (int k = i; k <= i + j; k++) {
                tmp = dp[i][k] + dp[k][i + j] + arr[i] * arr[k] * arr[i + j];
                if (dp[i][j] == 0)
                    dp[i][j] = tmp;
                dp[i][j] = min(dp[i][j], tmp);
            }
        }
    }
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
    cout << dp[0][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
}
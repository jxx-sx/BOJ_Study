#include <iostream>

#define INF 2147483647

using namespace std;

int cost[501][501];
int arr[501];
int n;
void init() {
    cin >> n;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++)
            cost[i][j] = INF;
        cost[i][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }
}

void solve() {
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= n - i; j++)
            for (int k = j; k < j + i; k++)
                cost[j][j + i] = min(cost[j][j + i], cost[j][k] + cost[k + 1][j + i] + arr[j + i] - arr[j - 1]);

    cout << cost[1][n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}
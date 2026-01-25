#include <iostream>

#define INF 20000000

using namespace std;

int dp[1 << 16][16];
int arr[16][16];
int n;

int tsp(int visited, int cur) {
    if (__builtin_popcount(visited) == n) {
        if (!arr[cur][0])
            return INF;
        return arr[cur][0];
    }
    if (dp[visited][cur])
        return dp[visited][cur];
    dp[visited][cur] = INF;
    for (int i = 1; i < n; i++) {
        if (visited & (1 << i))
            continue;
        if (!arr[cur][i])
            continue;
        dp[visited][cur] = min(dp[visited][cur], tsp(visited | (1 << i), i) + arr[cur][i]);
    }
    return dp[visited][cur];
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
}

void solve() { cout << tsp(1, 0); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
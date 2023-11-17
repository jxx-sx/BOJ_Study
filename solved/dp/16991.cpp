#include <cmath>
#include <iostream>

#define INF 20000000

using namespace std;

double dp[1 << 16][16];
double arr[16][16];
pair<int, int> cord[16];
int n;

double tsp(int visited, int cur) {
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
        cin >> cord[i].first >> cord[i].second;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            arr[j][i] = arr[i][j] = sqrt(pow(cord[i].first - cord[j].first, 2) + pow(cord[i].second - cord[j].second, 2));
}

void solve() {
    cout << fixed;
    cout.precision(8);
    cout << tsp(1, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
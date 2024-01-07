#include <iostream>
#include <memory.h>
#include <vector>

#define INF 101010

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int dp[10001];
vector<int> coin;
int n, k;

void init() {
    fill(dp + 1, dp + 10001, INF);
    cin >> n >> k;
    coin.resize(n);
    for (auto &a : coin)
        cin >> a;
}

void solve() {
    for (auto a : coin)
        for (int i = 0; i + a <= k; i++)
            dp[i + a] = min(dp[i + a], dp[i] + 1);
    cout << (dp[k] == INF ? -1 : dp[k]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
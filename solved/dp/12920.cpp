#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<int> v, c;
int n, m;

void init() {
    cin >> n >> m;
    int a, b, k;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> k;
        for (int j = k; j; j >>= 1) {
            int cur = j - (j >> 1);
            v.push_back(cur * a);
            c.push_back(cur * b);
        }
    }
}

void solve() {
    vector<int> dp[10001];
    for (auto &a : dp)
        a.resize(v.size() + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < v.size(); j++) {
            dp[i][j + 1] = dp[i][j];
            if (i >= v[j])
                dp[i][j + 1] = max(dp[i][j + 1], dp[i - v[j]][j] + c[j]);
        }
    }
    cout << dp[m][v.size()];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
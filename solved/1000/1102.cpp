#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[16][16];
int n, p;
int st, cur;
int dp[1 << 16];
vector<int> v[17];

int get(int a, int b) {
    int ret = 40;
    for (int i = 0; i < n; i++) {
        if (1 << i & a)
            ret = min(ret, arr[i][b]);
    }
    return ret;
}

void dfs(int c = 0, int cnt = 0, int d = 0) {
    if (d == n) {
        v[cnt].push_back(c);
        return;
    }
    dfs(c | (1 << d), cnt + 1, d + 1);
    dfs(c, cnt, d + 1);
}

void init() {
    cin >> n;
    dfs();
    for (int i = 0; i < (1 << 16); i++)
        dp[i] = 600;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'Y') {
            st |= 1 << i;
            cur++;
        }
    }
    cin >> p;
}

void solve() {
    if (p <= cur) {
        cout << 0;
        return;
    }
    if (!st) {
        cout << -1;
        return;
    }
    dp[st] = 0;
    for (; cur < p; cur++) {
        for (auto a : v[cur]) {
            for (int i = 0; i < n; i++) {
                if ((a | (1 << i)) != a)
                    dp[a | (1 << i)] = min(dp[a | (1 << i)], dp[a] + get(a, i));
            }
        }
    }
    int ans = 600;
    for (auto a : v[p])
        ans = min(ans, dp[a]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
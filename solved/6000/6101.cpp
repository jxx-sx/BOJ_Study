#include <iostream>

#define N 40001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m;
int tree[N << 2];
int p[N], dp[N], arr[N];

void update(int k, int d, int s = 0, int e = n, int i = 1) {
    tree[i] += d;
    if (s == e)
        return;
    if ((s + e) / 2 < k)
        update(k, d, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, d, s, (s + e) / 2, i << 1);
}

int kth(int k, int s = 0, int e = n, int i = 1) {
    if (s == e)
        return s;
    if (tree[i << 1] < k)
        return kth(k - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
    return kth(k, s, (s + e) / 2, i << 1);
}

void init() { cin >> n >> m; }

void solve() {
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (p[arr[i]])
            update(p[arr[i]], -1);
        update(i, 1);
        p[arr[i]] = i;
        dp[i] = dp[i - 1] + 1;

        for (int j = 1; j * j <= i; j++)
            dp[i] = min(dp[i], dp[kth(tree[1] - j)] + j * j);
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}
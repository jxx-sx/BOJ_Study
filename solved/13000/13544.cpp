#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
vector<int> tree[400000];
int n;
int la = 0;

void tree_init(int s, int e, int i) {
    if (s == e) {
        int inp;
        cin >> inp;
        tree[i].push_back(inp);
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    int l = 0, r = 0;
    while (l != tree[i << 1].size() and r != tree[i << 1 | 1].size()) {
        tree[i].push_back(min(tree[i << 1][l], tree[i << 1 | 1][r]));
        tree[i << 1][l] < tree[i << 1 | 1][r] ? l++ : r++;
    }

    while (l != tree[i << 1].size()) {
        tree[i].push_back(tree[i << 1][l]);
        l++;
    }

    while (r != tree[i << 1 | 1].size()) {
        tree[i].push_back(tree[i << 1 | 1][r]);
        r++;
    }
}

int query(int l, int r, int k, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].size() - (upper_bound(tree[i].begin(), tree[i].end(), k) - tree[i].begin());
    return query(l, r, k, s, (s + e) / 2, i << 1) + query(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n;
    tree_init(1, n, 1);

    return;
}

void solve() {
    int a, b, c, m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        a ^= la;
        b ^= la;
        c ^= la;
        la = query(a, b, c, 1, n, 1);
        cout << la << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
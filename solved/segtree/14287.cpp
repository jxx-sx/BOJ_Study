#include <iostream>
#include <vector>

using namespace std;

int n, m, ord, in[100001], out[100001];
vector<int> v[100001];

struct seg {
    int tree[400000];

    void update(int k, int w, int s, int e, int i) {
        tree[i] += w;
        if (s == e)
            return;
        if ((s + e) / 2 < k)
            update(k, w, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, w, s, (s + e) / 2, i << 1);
    }

    int range_query(int l, int r, int s, int e, int i) {
        if (e < l or r < s)
            return 0;
        if (l <= s and e <= r)
            return tree[i];
        return range_query(l, r, s, (s + e) / 2, i << 1) + range_query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    }
} tree;

void dfs(int x) {
    in[x] = ++ord;
    for (auto a : v[x])
        if (!in[a])
            dfs(a);
    out[x] = ord;
}

void init() {
    int p;
    cin >> n >> m;
    cin >> p;
    for (int i = 2; i <= n; i++) {
        cin >> p;
        v[p].push_back(i);
    }
    dfs(1);
}

void solve() {
    int op, i, w;
    while (m--) {
        cin >> op >> i;
        if (op == 1) {
            cin >> w;
            tree.update(in[i], w, 1, n, 1);
        } else
            cout << tree.range_query(in[i], out[i], 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
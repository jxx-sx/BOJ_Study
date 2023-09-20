#include <iostream>
#include <vector>

using namespace std;

int n, m, ord, in[100001], out[100001];
vector<int> v[100001];

struct seg {
    int tree[400000];
    int lazy[400000];

    void init(int s, int e, int i) {
        tree[i] = e - s + 1;
        if (s == e)
            return;
        init(s, (s + e) / 2, i << 1);
        init((s + e) / 2 + 1, e, i << 1 | 1);
    }

    void push(int x, int s, int e) {
        if (!lazy[x])
            return;
        tree[x << 1] = lazy[x] == 1 ? (s + e) / 2 - s + 1 : 0;
        tree[x << 1 | 1] = lazy[x] == 1 ? e - (s + e) / 2 : 0;
        lazy[x << 1 | 1] = lazy[x << 1] = lazy[x];
        lazy[x] = 0;
    }

    void update(int l, int r, int d, int s, int e, int i) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            tree[i] = d == 1 ? e - s + 1 : 0;
            lazy[i] = d;
            return;
        }
        push(i, s, e);
        update(l, r, d, s, (s + e) / 2, i << 1);
        update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    int query(int l, int r, int s, int e, int i) {
        if (e < l or r < s)
            return 0;
        if (l <= s and e <= r)
            return tree[i];
        push(i, s, e);
        return query(l, r, s, (s + e) / 2, i << 1) + query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    }
} tree;

void dfs(int x) {
    ord++;
    in[x] = ord;
    for (auto a : v[x])
        dfs(a);
    out[x] = ord;
}

void init() {
    int tmp;
    cin >> n >> tmp;
    for (int i = 2; i <= n; i++) {
        cin >> tmp;
        v[tmp].push_back(i);
    }
    cin >> m;
    dfs(1);
    tree.init(1, n, 1);
}

void solve() {
    int op, i;
    while (m--) {
        cin >> op >> i;
        if (op == 3) {
            cout << (in[i] == out[i] ? 0 : tree.query(in[i] + 1, out[i], 1, n, 1)) << '\n';
            continue;
        }
        if (in[i] != out[i])
            tree.update(in[i] + 1, out[i], op, 1, n, 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
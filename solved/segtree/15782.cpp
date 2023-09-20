#include <iostream>
#include <vector>
#define N 100001
#define pb push_back

using namespace std;

int n, m, ord;
int in[N], out[N];
vector<int> v[N];

struct seg {
    int tree[N << 2];
    int lazy[N << 2];

    void push(int s, int e, int i) {
        if (!lazy[i])
            return;
        if (((s + e) / 2 - s + 1) & 1)
            tree[i << 1] ^= lazy[i];
        if ((e - (s + e) / 2) & 1)
            tree[i << 1 | 1] ^= lazy[i];
        lazy[i << 1] ^= lazy[i];
        lazy[i << 1 | 1] ^= lazy[i];
        lazy[i] = 0;
    }

    void update(int l, int r, int d, int s, int e, int i) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            if ((e - s + 1) & 1)
                tree[i] ^= d;
            lazy[i] ^= d;
            return;
        }
        push(s, e, i);
        update(l, r, d, s, (s + e) / 2, i << 1);
        update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
        tree[i] = tree[i << 1] ^ tree[i << 1 | 1];
    }

    int query(int l, int r, int s, int e, int i) {
        if (e < l or r < s)
            return 0;
        if (l <= s and e <= r)
            return tree[i];
        push(s, e, i);
        return query(l, r, s, (s + e) / 2, i << 1) ^ query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
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
    int a, b;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cin >> a;
        tree.update(in[i], in[i], a, 1, n, 1);
    }
}

void solve() {
    int op, x, y;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> x;
            cout << tree.query(in[x], out[x], 1, n, 1) << '\n';
        } else {
            cin >> x >> y;
            tree.update(in[x], out[x], y, 1, n, 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
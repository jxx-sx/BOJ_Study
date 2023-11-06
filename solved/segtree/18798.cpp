#include <iostream>

#define N 250000

using namespace std;

int n, k, m;

struct Fenwick {
    int tree[N + 1];

    void update(int x, int d) {
        while (x <= n) {
            tree[x] += d;
            x += x & -x;
        }
    }

    int sum(int x) {
        int ret = 0;
        while (x) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }

    int get(int l, int r) { return sum(r) - sum(l - 1); }
} query;

struct Seg {
    int tree[N << 2];
    void init(int s, int e, int i) {
        if (s == e) {
            cin >> tree[i];
            if (tree[i] == k)
                query.update(s, 1);
            return;
        }
        init(s, (s + e) / 2, i << 1);
        init((s + e) / 2 + 1, e, i << 1 | 1);
        tree[i] = tree[i << 1] & tree[i << 1 | 1];
    }

    void update(int l, int r, int x, int s, int e, int i) {
        if (e < l or r < s)
            return;
        if ((tree[i] & x) == x)
            return;
        if (s == e) {
            if (tree[i] == k)
                query.update(s, -1);
            tree[i] |= x;
            if (tree[i] == k)
                query.update(s, 1);
            return;
        }
        update(l, r, x, s, (s + e) / 2, i << 1);
        update(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
        tree[i] = tree[i << 1] & tree[i << 1 | 1];
    }
} tree;

void init() {
    cin >> n >> k;
    tree.init(1, n, 1);
    cin >> m;
}

void solve() {
    int q, l, r, x;
    while (m--) {
        cin >> q >> l >> r;
        if (q == 1) {
            cin >> x;
            tree.update(l, r, x, 1, n, 1);
        } else
            cout << query.get(l, r) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
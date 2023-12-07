#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    int l, r, d;
};

struct PST {
    Node node[4200000];
    int cur;

    int newNode() { return ++cur; }

    void init(int s, int e, int i) {
        if (s == e)
            return;
        node[i].l = newNode();
        node[i].r = newNode();
        init(s, (s + e) / 2, node[i].l);
        init((s + e) / 2 + 1, e, node[i].r);
    }

    void init(int s, int e, int k, int src, int dst) {
        node[dst] = node[src];
        node[dst].d++;
        if (s == e)
            return;
        if (k > (s + e) / 2) {
            node[dst].r = newNode();
            init((s + e) / 2 + 1, e, k, node[src].r, node[dst].r);
        } else {
            node[dst].l = newNode();
            init(s, (s + e) / 2, k, node[src].l, node[dst].l);
        }
    }

    int sum(int s, int e, int k, int src, int dst) {
        if (e < k)
            return 0;
        if (k <= s)
            return node[dst].d - node[src].d;
        return sum(s, (s + e) / 2, k, node[src].l, node[dst].l) + sum((s + e) / 2 + 1, e, k, node[src].r, node[dst].r);
    }
} pst;

int n, q;

int query(int a, int b) {
    int ret = 0;
    int l = 1, r = b - a + 1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (pst.sum(1, 200000, m, a - 1, b) >= m) {
            ret = max(ret, m);
            l = m + 1;
        } else
            r = m - 1;
    }
    return ret;
}

void init() {
    int p;
    cin >> n >> q;
    pst.cur = n;
    pst.init(1, 200000, 0);

    for (int i = 0; i < n; i++) {
        cin >> p;
        pst.init(1, 200000, p, i, i + 1);
    }
}

void solve() {
    int l, r;
    while (q--) {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
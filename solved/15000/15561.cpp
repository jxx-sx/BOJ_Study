#include <algorithm>
#include <iostream>

#define NONE 1000000000

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Seg {
    int lmx, rmx, mx, sum;
    Seg(int x = 0) : lmx(x), rmx(x), mx(x), sum(x) {}
    Seg(int lmx, int rmx, int mx, int sum) : lmx(lmx), rmx(rmx), mx(mx), sum(sum) {}
    Seg operator+(const Seg &t) const { return Seg(max(lmx, sum + t.lmx), max(t.rmx, rmx + t.sum), max({mx, t.mx, rmx + t.lmx}), sum + t.sum); }
} tree[400000];

int n, q, u, v;

void init(int s, int e, int i = 1) {
    if (s == e) {
        cin >> tree[i].sum;
        tree[i].sum = tree[i].sum * u + v;
        tree[i].lmx = tree[i].rmx = tree[i].mx = tree[i].sum;
        return;
    }
    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void update(int k, int x, int s, int e, int i = 1) {
    if (s == e) {
        tree[i].lmx = tree[i].rmx = tree[i].mx = tree[i].sum = x;
        return;
    }
    if (k > (s + e) / 2)
        update(k, x, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, x, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

Seg get(int l, int r, int s, int e, int i = 1) {
    if (e < l or r < s)
        return Seg(NONE);
    if (l <= s and e <= r)
        return tree[i];
    Seg ll = get(l, r, s, (s + e) / 2, i << 1);
    Seg rr = get(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    if (ll.sum == NONE)
        return rr;
    if (rr.sum == NONE)
        return ll;
    return ll + rr;
}

void init() {
    cin >> n >> q >> u >> v;
    init(1, n);
}

void solve() {
    int c, a, b;
    while (q--) {
        cin >> c >> a >> b;
        if (c)
            update(a, u * b + v, 1, n);
        else
            cout << get(a, b, 1, n).mx - v << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <algorithm>
#include <iostream>

#define N 200000

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Seg {
    long long lmx, rmx, mx, sum;
    bool l, r;
    bool flip;
    Seg(bool x = 0) : lmx(1), rmx(1), mx(1), sum(1), l(x), r(x), flip(false) {}
    Seg(long long lmx, long long rmx, long long mx, long long sum, bool l, bool r) : lmx(lmx), rmx(rmx), mx(mx), sum(sum), l(l), r(r), flip(false) {}
    Seg operator+(const Seg &t) const {
        return Seg(lmx == sum and r ^ t.l ? sum + t.lmx : lmx, t.rmx == t.sum and r ^ t.l ? t.sum + rmx : t.rmx, mx + t.mx + (r ^ t.l ? rmx * t.lmx : 0),
                   sum + t.sum, l, t.r);
    }
} tree[N << 2];

int n, q;

void push(int i) {
    if (!tree[i].flip)
        return;
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a].l ^= 1;
        tree[a].r ^= 1;
        tree[a].flip ^= 1;
    }
    tree[i].flip = false;
}

void update(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].l ^= 1;
        tree[i].r ^= 1;
        tree[i].flip ^= 1;
        return;
    }
    push(i);
    update(l, r, s, (s + e) / 2, i << 1);
    update(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

Seg get(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return Seg(-1, -1, -1, -1, 0, 0);
    if (l <= s and e <= r)
        return tree[i];
    push(i);
    auto ll = get(l, r, s, (s + e) / 2, i << 1);
    auto rr = get(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    if (ll.lmx == -1)
        return rr;
    if (rr.lmx == -1)
        return ll;
    return ll + rr;
}

void init(int s, int e, int i = 1) {
    if (s == e) {
        int inp;
        cin >> inp;
        tree[i] = Seg(inp);
        return;
    }
    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void init() {
    cin >> n >> q;
    init(1, n);
}

void solve() {
    int op, l, r;
    while (q--) {
        cin >> op >> l >> r;
        if (op == 1)
            update(l, r);
        else
            cout << get(l, r).mx << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
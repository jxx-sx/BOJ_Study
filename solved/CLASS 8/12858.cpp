#include <iostream>
#include <numeric>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Seg {
    long long gcd, l, r, lz;
    Seg(long long gcd = 0, long long l = 0, long long r = 0, long long lz = 0) : gcd(gcd), l(l), r(r), lz(lz) {}
    Seg operator+(const Seg &t) const { return Seg(std::gcd(std::gcd(gcd, t.gcd), abs(r - t.l)), l, t.r); }
} tree[400000];

void push(int s, int e, int i) {
    if (!tree[i].lz)
        return;
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a].l += tree[i].lz;
        tree[a].r += tree[i].lz;
        tree[a].lz += tree[i].lz;
    }
    if (s == (s + e) / 2)
        tree[i << 1].gcd += tree[i].lz;
    if ((s + e) / 2 + 1 == e)
        tree[i << 1 | 1].gcd += tree[i].lz;
    tree[i].lz = 0;
}

void init(int s, int e, int i = 1) {
    if (s == e) {
        cin >> tree[i].gcd;
        tree[i].l = tree[i].r = tree[i].gcd;
        return;
    }
    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void update(int l, int r, int x, int s, int e, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (s == e)
            tree[i].gcd += x;
        tree[i].l += x;
        tree[i].r += x;
        tree[i].lz += x;
        return;
    }
    push(s, e, i);
    update(l, r, x, s, (s + e) / 2, i << 1);
    update(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

long long query(int l, int r, int s, int e, int i = 1) {
    if (e < l or r < s)
        return -1;
    if (l <= s and e <= r)
        return gcd(tree[i].gcd, tree[i].l);
    push(s, e, i);
    long long ll = query(l, r, s, (s + e) / 2, i << 1);
    long long rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    if (ll == -1)
        return rr;
    if (rr == -1)
        return ll;
    return gcd(ll, rr);
}

int n, q;

void init() {
    cin >> n;
    init(1, n);
    cin >> q;
}

void solve() {
    int t, a, b;
    while (q--) {
        cin >> t >> a >> b;
        if (t)
            update(a, b, t, 1, n);
        else
            cout << query(a, b, 1, n) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
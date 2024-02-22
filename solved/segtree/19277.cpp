#include <iostream>

#define N 200000

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

struct Seg {
    ll mx, mn;
    Seg(ll x = 0) : mx(x), mn(x) {}
    Seg(ll mx, ll mn) : mx(mx), mn(mn) {}
    Seg operator+(const Seg &t) const { return Seg(max(mx, t.mx), min(mn, t.mn)); }
} tree[N << 2];

struct Lazy {
    ll set, add;
    Lazy(ll x = -1) : set(x), add(0) {}
} lz[N << 2];

int n, q;

void push(int i) {
    for (auto a : {i << 1, i << 1 | 1}) {
        if (lz[i].set != -1) {
            tree[a].mx = tree[a].mn = lz[i].set;
            lz[a] = Lazy(lz[i].set);
        }
        tree[a].mx += lz[i].add;
        tree[a].mn += lz[i].add;
        lz[a].add += lz[i].add;
    }
    lz[i] = Lazy();
}

void add(int l, int r, int x, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].mx += x;
        tree[i].mn += x;
        lz[i].add += x;
        return;
    }
    push(i);
    add(l, r, x, s, (s + e) / 2, i << 1);
    add(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void div(int l, int r, int x, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (tree[i].mx / x == tree[i].mn / x) {
            tree[i].mx = tree[i].mn = tree[i].mx / x;
            lz[i] = Lazy(tree[i].mx);
            return;
        }
        if (tree[i].mx == tree[i].mn + 1) {
            ll diff = tree[i].mx / x - tree[i].mx;
            tree[i].mx += diff;
            tree[i].mn += diff;
            lz[i].add += diff;
            return;
        }
    }
    push(i);
    div(l, r, x, s, (s + e) / 2, i << 1);
    div(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

ll query(int l, int r, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].mx;
    push(i);
    return max(query(l, r, s, (s + e) / 2, i << 1), query(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

void init(int s, int e, int i = 1) {
    if (s == e) {
        cin >> tree[i].mx;
        tree[i].mn = tree[i].mx;
        return;
    }
    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void init() {
    cin >> n >> q;
    init(0, n - 1);
}

void solve() {
    int op, l, r, x;
    while (q--) {
        cin >> op >> l >> r >> x;
        if (op == 0)
            add(l, r, x);
        else if (op == 1)
            div(l, r, x);
        else
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
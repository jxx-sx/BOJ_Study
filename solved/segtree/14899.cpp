#include <iostream>

#define N 100000
#define INF 2020202020

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

struct Seg {
    ll mx, mn, sum;
    Seg(ll x = 0) : mx(x), mn(x), sum(x) {}
    Seg(ll mx, ll mn, ll sum) : mx(mx), mn(mn), sum(sum) {}
    Seg operator+(const Seg &t) const { return Seg(max(mx, t.mx), min(mn, t.mn), sum + t.sum); }
} tree[N << 2];

struct Lazy {
    ll set, add;
    Lazy(ll x = INF) : set(x), add(0) {}
    bool empty() { return set == INF and !add; }
} lz[N << 2];

int n, q;

ll div_fl(ll x, ll d) { return x >= 0 ? x / d : (x - d + 1) / d; }

void push(int s, int e, int i) {
    if (lz[i].empty())
        return;

    int m = (s + e) / 2;
    if (lz[i].set != INF) {
        tree[i << 1] = tree[i << 1 | 1] = Seg(lz[i].set);
        tree[i << 1].sum = lz[i].set * (m - s + 1);
        tree[i << 1 | 1].sum = lz[i].set * (e - m);
        lz[i << 1] = lz[i << 1 | 1] = Lazy(lz[i].set);
    }

    tree[i << 1].mx += lz[i].add;
    tree[i << 1].mn += lz[i].add;
    tree[i << 1].sum += lz[i].add * (m - s + 1);
    tree[i << 1 | 1].mx += lz[i].add;
    tree[i << 1 | 1].mn += lz[i].add;
    tree[i << 1 | 1].sum += lz[i].add * (e - m);
    lz[i << 1].add += lz[i].add;
    lz[i << 1 | 1].add += lz[i].add;

    lz[i] = Lazy();
}

void add(int l, int r, int c, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].mx += c;
        tree[i].mn += c;
        tree[i].sum += c * (e - s + 1);
        lz[i].add += c;
        return;
    }
    push(s, e, i);
    add(l, r, c, s, (s + e) / 2, i << 1);
    add(l, r, c, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void div(int l, int r, int d, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (div_fl(tree[i].mx, d) == div_fl(tree[i].mn, d)) {
            ll v = div_fl(tree[i].mx, d);
            tree[i] = Seg(v);
            tree[i].sum = v * (e - s + 1);
            lz[i] = Lazy(v);
            return;
        }
        if (tree[i].mx == tree[i].mn + 1) {
            ll diff = div_fl(tree[i].mx, d) - tree[i].mx;
            tree[i].mx += diff;
            tree[i].mn += diff;
            tree[i].sum += diff * (e - s + 1);
            lz[i].add += diff;
            return;
        }
    }
    push(s, e, i);
    div(l, r, d, s, (s + e) / 2, i << 1);
    div(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

ll mn(int l, int r, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return INF;
    if (l <= s and e <= r)
        return tree[i].mn;
    push(s, e, i);
    return min(mn(l, r, s, (s + e) / 2, i << 1), mn(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

ll sum(int l, int r, int s = 0, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].sum;
    push(s, e, i);
    return sum(l, r, s, (s + e) / 2, i << 1) + sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init(int s, int e, int i = 1) {
    if (s == e) {
        ll x;
        cin >> x;
        tree[i] = Seg(x);
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
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            add(l, r, x);
        }
        if (op == 2) {
            cin >> x;
            div(l, r, x);
        }
        if (op == 3)
            cout << mn(l, r) << '\n';
        if (op == 4)
            cout << sum(l, r) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
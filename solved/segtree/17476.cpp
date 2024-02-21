#include <cmath>
#include <iostream>

#define N 100000

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

int n, m;

struct Seg {
    ll mx, mn, sum, lz_set, lz_add;
    Seg(ll x = 0) : mx(x), mn(x), sum(x), lz_set(-1), lz_add(0) {}
    Seg(ll mx, ll mn, ll sum) : mx(mx), mn(mn), sum(sum), lz_set(-1), lz_add(0) {}
    Seg operator+(const Seg &t) const { return Seg(max(mx, t.mx), min(mn, t.mn), sum + t.sum); }
} tree[N << 2];

void push(int s, int e, int i) {
    for (auto a : {make_pair(i << 1, (s + e) / 2 - s + 1), make_pair(i << 1 | 1, e - (s + e) / 2)}) {
        if (tree[i].lz_set != -1) {
            tree[a.first].mx = tree[i].lz_set;
            tree[a.first].mn = tree[i].lz_set;
            tree[a.first].sum = tree[i].lz_set * a.second;
            tree[a.first].lz_set = tree[i].lz_set;
            tree[a.first].lz_add = 0;
        }
        tree[a.first].mx += tree[i].lz_add;
        tree[a.first].mn += tree[i].lz_add;
        tree[a.first].sum += tree[i].lz_add * a.second;
        tree[a.first].lz_add += tree[i].lz_add;
    }

    tree[i].lz_set = -1;
    tree[i].lz_add = 0;
}

void add(int l, int r, long long x, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].mx += x;
        tree[i].mn += x;
        tree[i].sum += x * (e - s + 1);
        tree[i].lz_add += x;
        return;
    }
    push(s, e, i);
    add(l, r, x, s, (s + e) / 2, i << 1);
    add(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void set(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (floor(sqrt(tree[i].mx)) == floor(sqrt(tree[i].mn))) {
            tree[i].mx = tree[i].mn = floor(sqrt(tree[i].mx));
            tree[i].sum = tree[i].mx * (e - s + 1);
            tree[i].lz_set = tree[i].mx;
            tree[i].lz_add = 0;
            return;
        }
        if (tree[i].mx == tree[i].mn + 1) {
            long long diff = floor(sqrt(tree[i].mx)) - tree[i].mx;
            tree[i].mx += diff;
            tree[i].mn += diff;
            tree[i].sum += diff * (e - s + 1);
            tree[i].lz_add += diff;
            return;
        }
    }
    push(s, e, i);
    set(l, r, s, (s + e) / 2, i << 1);
    set(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

long long sum(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].sum;
    push(s, e, i);
    return sum(l, r, s, (s + e) / 2, i << 1) + sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init(int s, int e, int i = 1) {
    if (s == e) {
        ll tmp;
        cin >> tmp;
        tree[i] = Seg(tmp);
        return;
    }

    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void init() {
    cin >> n;
    init(1, n);
    cin >> m;
}

void solve() {
    int op, l, r;
    long long x;
    while (m--) {
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            add(l, r, x);
        }
        if (op == 2)
            set(l, r);
        if (op == 3)
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
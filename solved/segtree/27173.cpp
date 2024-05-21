#include <cmath>
#include <iostream>
#include <vector>

#define N 100001
#define INF 2e18
#define pb push_back

using namespace std;

typedef long long ll;

int n, q;

struct Seg {
    ll mx, mn;
    Seg(ll mx = 0, ll mn = 0) : mx(mx), mn(mn) {}
    Seg operator+(const Seg &t) const { return Seg(max(mx, t.mx), min(mn, t.mn)); }
} tree[N << 2];

struct LZ {
    int op;
    ll t;
    LZ(int op = 0, ll t = 0) : op(op), t(t) {}
};
vector<LZ> lz[N << 2];

void push(ll s, ll e, int i) {
    ll m = (s + e) / 2;
    for (auto [op, t] : lz[i]) {
        if (op == 2) {
            tree[i << 1].mn += t;
            tree[i << 1].mx += t;
            tree[i << 1 | 1].mn += t;
            tree[i << 1 | 1].mx += t;

            lz[i << 1].pb(LZ(op, t));
            lz[i << 1 | 1].pb(LZ(op, t));
        }
        if (op == 3) {
            tree[i << 1].mn = t;
            tree[i << 1].mx = t + m - s;
            tree[i << 1 | 1].mn = t + m - s + 1;
            tree[i << 1 | 1].mx = t + e - s;

            lz[i << 1].clear();
            lz[i << 1 | 1].clear();
            lz[i << 1].pb(LZ(op, t));
            lz[i << 1 | 1].pb(LZ(op, t + m - s + 1));
        }
        if (op == 4) {
            tree[i << 1].mn = sqrt(tree[i << 1].mn);
            tree[i << 1].mx = sqrt(tree[i << 1].mx);
            tree[i << 1 | 1].mn = sqrt(tree[i << 1 | 1].mn);
            tree[i << 1 | 1].mx = sqrt(tree[i << 1 | 1].mx);

            lz[i << 1].pb(LZ(4, 0));
            lz[i << 1 | 1].pb(LZ(4, 0));
        }
    }
    lz[i].clear();
}

ll kth(int k, int s = 1, int e = n, int i = 1) {
    if (tree[i].mx == tree[i].mn || s == e)
        return tree[i].mx;
    push(s, e, i);
    if (k > (s + e) / 2)
        return kth(k, (s + e) / 2 + 1, e, i << 1 | 1);
    return kth(k, s, (s + e) / 2, i << 1);
}

ll mn(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return INF;
    if (l <= s and e <= r)
        return tree[i].mn;
    push(s, e, i);
    return min(mn(l, r, s, (s + e) / 2, i << 1), mn(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

void add(int l, int r, ll t, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].mx += t;
        tree[i].mn += t;
        if (!lz[i].empty() && lz[i].back().op == 2)
            lz[i].back().t += t;
        else
            lz[i].pb(LZ(2, t));
        return;
    }
    push(s, e, i);
    add(l, r, t, s, (s + e) / 2, i << 1);
    add(l, r, t, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void sub(int l, int r, ll t) {
    if (mn(l, r) < t)
        return;
    add(l, r, -t);
}

void set(int l, int r, ll t, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].mn = t + s - r;
        tree[i].mx = t + e - r;
        lz[i].clear();
        lz[i].pb(LZ(3, t + s - r));
        return;
    }
    push(s, e, i);
    set(l, r, t, s, (s + e) / 2, i << 1);
    set(l, r, t, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void sqrt_fl(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s or tree[i].mx <= 1)
        return;
    if (l <= s and e <= r) {
        tree[i].mx = sqrt(tree[i].mx);
        tree[i].mn = sqrt(tree[i].mn);
        lz[i].pb(LZ(4, 0));
        return;
    }
    push(s, e, i);
    sqrt_fl(l, r, s, (s + e) / 2, i << 1);
    sqrt_fl(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
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
    init(1, n);
}

void solve() {
    int op, x, y;
    ll t;
    while (q--) {
        cin >> op >> x;
        if (op == 1)
            cout << kth(x) << '\n';
        if (op == 2) {
            cin >> y >> t;
            sub(x, y, t);
        }
        if (op == 3) {
            cin >> y >> t;
            set(x, y, t);
        }
        if (op == 4) {
            cin >> y;
            sqrt_fl(x, y);
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
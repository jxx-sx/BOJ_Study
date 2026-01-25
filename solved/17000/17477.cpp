#include <iostream>

#define N 500000
#define INF 2020202020

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

struct Node {
    ll mx, smx, cmx, mn, smn, cmn, lz_mx, lz_cmx, lz_mn, lz_cmn, lz_d;
    ll b, lz_b;
    Node operator+(const Node &t) const {
        Node ret;

        if (mx > t.mx) {
            ret.mx = mx;
            ret.smx = max(smx, t.mx);
            ret.cmx = cmx;
        } else if (mx < t.mx) {
            ret.mx = t.mx;
            ret.smx = max(mx, t.smx);
            ret.cmx = t.cmx;
        } else {
            ret.mx = mx;
            ret.smx = max(smx, t.smx);
            ret.cmx = cmx + t.cmx;
        }

        if (mn < t.mn) {
            ret.mn = mn;
            ret.smn = min(smn, t.mn);
            ret.cmn = cmn;
        } else if (mn > t.mn) {
            ret.mn = t.mn;
            ret.smn = min(mn, t.smn);
            ret.cmn = t.cmn;
        } else {
            ret.mn = mn;
            ret.smn = min(smn, t.smn);
            ret.cmn = cmn + t.cmn;
        }

        ret.b = b + t.b;
        return ret;
    }

    Node(ll mx = 0, ll smx = -INF, ll cmx = 1, ll mn = 0, ll smn = INF, ll cmn = 1, ll lz_mx = -INF, ll lz_cmx = 0, ll lz_mn = INF, ll lz_cmn = 0, ll lz_d = 0,
         ll b = 0, ll lz_b = 0)
        : mx(mx), smx(smx), cmx(cmx), mn(mn), smn(smn), cmn(cmn), lz_mx(lz_mx), lz_cmx(lz_cmx), lz_mn(lz_mn), lz_cmn(lz_cmn), lz_d(lz_d), b(b), lz_b(lz_b) {}
} tree[N << 2];

ll n, m;

inline void push_a(ll i) {
    ll l = i << 1;
    ll r = l | 1;
    if (tree[i].lz_d) {
        for (auto a : {l, r}) {
            tree[a].mx += tree[i].lz_d;
            if (tree[a].smx != -INF)
                tree[a].smx += tree[i].lz_d;
            tree[a].mn += tree[i].lz_d;
            if (tree[a].smn != INF)
                tree[a].smn += tree[i].lz_d;
            tree[a].lz_d += tree[i].lz_d;
            if (tree[a].lz_cmx)
                tree[a].lz_mx += tree[i].lz_d;
            if (tree[a].lz_cmn)
                tree[a].lz_mn += tree[i].lz_d;
        }
        tree[i].lz_d = 0;
    }

    if (tree[i].lz_cmx) {
        if (tree[l].mn < tree[r].mn) {
            tree[l].lz_cmx += tree[i].lz_cmx;
            tree[l].b += (ll)tree[i].lz_cmx * tree[l].cmn;

            if (tree[l].mx == tree[l].mn)
                tree[l].mx = tree[i].lz_mx;
            else if (tree[l].smx == tree[l].mn)
                tree[l].smx = tree[i].lz_mx;
            tree[l].mn = tree[i].lz_mx;
            tree[l].lz_mx = tree[i].lz_mx;
            if (tree[l].lz_cmn)
                tree[l].lz_mn = max(tree[i].lz_mx, tree[l].lz_mn);
        } else if (tree[l].mn > tree[r].mn) {
            tree[r].lz_cmx += tree[i].lz_cmx;
            tree[r].b += (ll)tree[i].lz_cmx * tree[r].cmn;

            if (tree[r].mx == tree[r].mn)
                tree[r].mx = tree[i].lz_mx;
            else if (tree[r].smx == tree[r].mn)
                tree[r].smx = tree[i].lz_mx;
            tree[r].mn = tree[i].lz_mx;
            tree[r].lz_mx = tree[i].lz_mx;
            if (tree[r].lz_cmn)
                tree[r].lz_mn = max(tree[i].lz_mx, tree[r].lz_mn);
        } else {
            tree[l].lz_cmx += tree[i].lz_cmx;
            tree[r].lz_cmx += tree[i].lz_cmx;
            tree[l].b += (ll)tree[i].lz_cmx * tree[l].cmn;
            tree[r].b += (ll)tree[i].lz_cmx * tree[r].cmn;

            if (tree[l].mx == tree[l].mn)
                tree[l].mx = tree[i].lz_mx;
            else if (tree[l].smx == tree[l].mn)
                tree[l].smx = tree[i].lz_mx;
            tree[l].mn = tree[i].lz_mx;
            tree[l].lz_mx = tree[i].lz_mx;
            if (tree[l].lz_cmn)
                tree[l].lz_mn = max(tree[i].lz_mx, tree[l].lz_mn);

            if (tree[r].mx == tree[r].mn)
                tree[r].mx = tree[i].lz_mx;
            else if (tree[r].smx == tree[r].mn)
                tree[r].smx = tree[i].lz_mx;
            tree[r].mn = tree[i].lz_mx;
            tree[r].lz_mx = tree[i].lz_mx;
            if (tree[r].lz_cmn)
                tree[r].lz_mn = max(tree[i].lz_mx, tree[r].lz_mn);
        }
        tree[i].lz_cmx = 0;
        tree[i].lz_mx = -INF;
    }

    if (tree[i].lz_cmn) {
        if (tree[l].mx > tree[r].mx) {
            tree[l].lz_cmn += tree[i].lz_cmn;
            tree[l].b += (ll)tree[i].lz_cmn * tree[l].cmx;

            if (tree[l].mn == tree[l].mx)
                tree[l].mn = tree[i].lz_mn;
            else if (tree[l].smn == tree[l].mx)
                tree[l].smn = tree[i].lz_mn;
            tree[l].mx = tree[i].lz_mn;
            tree[l].lz_mn = tree[i].lz_mn;
        } else if (tree[l].mx < tree[r].mx) {
            tree[r].lz_cmn += tree[i].lz_cmn;
            tree[r].b += (ll)tree[i].lz_cmn * tree[r].cmx;

            if (tree[r].mn == tree[r].mx)
                tree[r].mn = tree[i].lz_mn;
            else if (tree[r].smn == tree[r].mx)
                tree[r].smn = tree[i].lz_mn;
            tree[r].mx = tree[i].lz_mn;
            tree[r].lz_mn = tree[i].lz_mn;
        } else {
            tree[l].lz_cmn += tree[i].lz_cmn;
            tree[r].lz_cmn += tree[i].lz_cmn;
            tree[l].b += (ll)tree[i].lz_cmn * tree[l].cmx;
            tree[r].b += (ll)tree[i].lz_cmn * tree[r].cmx;

            if (tree[l].mn == tree[l].mx)
                tree[l].mn = tree[i].lz_mn;
            else if (tree[l].smn == tree[l].mx)
                tree[l].smn = tree[i].lz_mn;
            tree[l].mx = tree[i].lz_mn;
            tree[l].lz_mn = tree[i].lz_mn;

            if (tree[r].mn == tree[r].mx)
                tree[r].mn = tree[i].lz_mn;
            else if (tree[r].smn == tree[r].mx)
                tree[r].smn = tree[i].lz_mn;
            tree[r].mx = tree[i].lz_mn;
            tree[r].lz_mn = tree[i].lz_mn;
        }
        tree[i].lz_cmn = 0;
        tree[i].lz_mn = INF;
    }
}

inline void push_b(ll s, ll e, ll i) {
    if (!tree[i].lz_b)
        return;
    ll m = (s + e) / 2;

    tree[i << 1].b += tree[i].lz_b * (m - s + 1);
    tree[i << 1 | 1].b += tree[i].lz_b * (e - m);

    tree[i << 1].lz_b += tree[i].lz_b;
    tree[i << 1 | 1].lz_b += tree[i].lz_b;

    tree[i].lz_b = 0;
}

inline void push(ll s, ll e, ll i) {
    push_a(i);
    push_b(s, e, i);
}

void add(ll l, ll r, ll x, ll s, ll e, ll i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].mx += x;
        if (tree[i].smx != -INF)
            tree[i].smx += x;
        tree[i].mn += x;
        if (tree[i].smn != INF)
            tree[i].smn += x;
        if (tree[i].lz_cmx)
            tree[i].lz_mx += x;
        if (tree[i].lz_cmn)
            tree[i].lz_mn += x;
        tree[i].lz_d += x;
        tree[i].b += e - s + 1;
        tree[i].lz_b++;
        return;
    }
    push(s, e, i);
    add(l, r, x, s, (s + e) / 2, i << 1);
    add(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void mx(ll l, ll r, ll x, ll s, ll e, ll i = 1) {
    if (e < l or r < s or tree[i].mn >= x)
        return;
    if (l <= s and e <= r and tree[i].smn > x) {
        if (tree[i].mx == tree[i].mn)
            tree[i].mx = x;
        else if (tree[i].smx == tree[i].mn)
            tree[i].smx = x;
        tree[i].mn = x;
        tree[i].lz_mx = x;
        tree[i].lz_mn = max(x, tree[i].lz_mn);
        tree[i].lz_cmx++;
        tree[i].b += tree[i].cmn;
        return;
    }
    push(s, e, i);
    mx(l, r, x, s, (s + e) / 2, i << 1);
    mx(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void mn(ll l, ll r, ll x, ll s, ll e, ll i = 1) {
    if (e < l or r < s or tree[i].mx <= x)
        return;
    if (l <= s and e <= r and tree[i].smx < x) {
        if (tree[i].mn == tree[i].mx)
            tree[i].mn = x;
        else if (tree[i].smn == tree[i].mx)
            tree[i].smn = x;
        tree[i].mx = x;
        tree[i].lz_mn = x;
        tree[i].lz_cmn++;
        tree[i].b += tree[i].cmx;
        return;
    }
    push(s, e, i);
    mn(l, r, x, s, (s + e) / 2, i << 1);
    mn(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

ll sum(ll l, ll r, ll s, ll e, ll i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].b;
    push(s, e, i);
    return sum(l, r, s, (s + e) / 2, i << 1) + sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void tree_init(ll s, ll e, ll i = 1) {
    if (s == e) {
        cin >> tree[i].mx;
        tree[i].mn = tree[i].mx;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void init() {
    cin >> n;
    tree_init(1, n);
    cin >> m;
}

void solve() {
    ll op, l, r, x;
    while (m--) {
        cin >> op >> l >> r;
        if (op == 4) {
            cout << sum(l, r, 1, n) << '\n';
            continue;
        }
        cin >> x;
        if (op == 1 and x)
            add(l, r, x, 1, n);
        if (op == 2)
            mx(l, r, x, 1, n);
        if (op == 3)
            mn(l, r, x, 1, n);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
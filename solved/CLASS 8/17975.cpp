#include <algorithm>
#include <iostream>
#include <memory.h>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

struct Seg {
    ll lmx, rmx, mx, sum;
    Seg(ll lmx = 0, ll rmx = 0, ll mx = 0, ll sum = 0) : lmx(max(lmx, 0ll)), rmx(max(rmx, 0ll)), mx(max(mx, 0ll)), sum(sum) {}
    Seg operator+(const Seg &t) const { return Seg(max(lmx, sum + t.lmx), max(t.rmx, t.sum + rmx), max({mx, t.mx, rmx + t.lmx}), sum + t.sum); }
} tree[10000];

struct Point {
    ll x, y, w;
    Point(int x = 0, int y = 0, int w = 0) : x(x), y(y), w(w) {}
    bool operator<(const Point &t) const { return x == t.x ? y < t.y : x < t.x; }
} p[2000];

void update(int k, ll w, int s, int e, int i = 1) {
    if (s == e) {
        tree[i].sum += w;
        tree[i].lmx = tree[i].rmx = tree[i].mx = max(tree[i].sum, 0ll);
        return;
    }
    if (k > (s + e) / 2)
        update(k, w, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, w, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

int n1, n2, n, c1, c2;
ll ans;
vector<Point> v[2000];
vector<int> x, y;

void init() {
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].w = 1;
        x.push_back(p[i].x);
        y.push_back(p[i].y);
    }
    cin >> n2;
    for (int i = n1; i < n1 + n2; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].w = -1;
        x.push_back(p[i].x);
        y.push_back(p[i].y);
    }
    cin >> c1 >> c2;
    n = n1 + n2;
    sort(p, p + n);
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    for (int i = 0; i < n; i++) {
        p[i].w = p[i].w > 0 ? c1 : -c2;
        p[i].y = lower_bound(y.begin(), y.end(), p[i].y) - y.begin();
        v[lower_bound(x.begin(), x.end(), p[i].x) - x.begin()].push_back(p[i]);
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        memset(tree, 0, sizeof(tree));
        for (int j = i; j < n; j++) {
            for (auto a : v[j])
                update(a.y, a.w, 0, 1999);
            ans = max(ans, tree[1].mx);
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
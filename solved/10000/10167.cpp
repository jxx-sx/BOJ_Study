#include <algorithm>
#include <iostream>
#include <memory.h>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Point {
    long long x, y, w;
    Point(long long x = 0, long long y = 0, long long w = 0) : x(x), y(y), w(w) {}
    bool operator<(const Point &t) const { return x == t.x ? y < t.y : x < t.x; }
};

struct Node {
    long long lmx, rmx, mx, sum;
    Node(long long lmx = 0, long long rmx = 0, long long mx = 0, long long sum = 0) : lmx(max(lmx, 0ll)), rmx(max(rmx, 0ll)), mx(max(mx, 0ll)), sum(sum) {}
    Node operator+(const Node &t) const { return Node(max(lmx, sum + t.lmx), max(rmx + t.sum, t.rmx), max({mx, t.mx, rmx + t.lmx}), sum + t.sum); }
} tree[12000];

void update(int k, long long x, int s, int e, int i = 1) {
    if (s == e) {
        tree[i].sum += x;
        tree[i].lmx = tree[i].rmx = tree[i].mx = max(tree[i].sum, 0ll);
        return;
    }
    if ((s + e) / 2 < k)
        update(k, x, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, x, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

vector<long long> x, y;
vector<Point> v;
vector<vector<Point>> sorted_v(3000);
int n;
long long ans;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v) {
        cin >> a.x >> a.y >> a.w;
        x.push_back(a.x);
        y.push_back(a.y);
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    sort(v.begin(), v.end());
    for (auto &a : v) {
        a.y = lower_bound(y.begin(), y.end(), a.y) - y.begin();
        sorted_v[lower_bound(x.begin(), x.end(), a.x) - x.begin()].push_back(a);
    }
}

void solve() {
    for (int i = 0; i < 3000; i++) {
        fill(tree, tree + 12000, Node());
        for (int j = i; j < 3000; j++) {
            for (auto a : sorted_v[j])
                update(a.y, a.w, 0, 2999);
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
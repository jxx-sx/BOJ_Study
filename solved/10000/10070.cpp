#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define INF 100000

using namespace std;

struct Query {
    int op, l, r, h;
};

int n, k;
vector<int> v;
vector<Query> q;
vector<int> ans;

struct Seg {
    int mx, mn, lz_mx, lz_mn;
    Seg(int mx = 0, int mn = 0) : mx(mx), mn(mn), lz_mx(0), lz_mn(INF) {}
    Seg operator+(const Seg &t) const { return Seg(max(mx, t.mx), min(mn, t.mn)); }
} tree[4004000];

void push(int i) {
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a].mx = min(tree[i].lz_mn, max(tree[i].lz_mx, tree[a].mx));
        tree[a].mn = min(tree[i].lz_mn, max(tree[i].lz_mx, tree[a].mn));
        tree[a].lz_mx = max(tree[i].lz_mx, tree[a].lz_mx);
        tree[a].lz_mn = min(tree[i].lz_mn, max(tree[i].lz_mx, tree[a].lz_mn));
    }
    tree[i].lz_mx = 0;
    tree[i].lz_mn = INF;
}

void mx_update(int l, int r, int x, int s, int e, int i = 1) {
    if (e < l or r < s or tree[i].mn >= x)
        return;
    if (l <= s and e <= r) {
        tree[i].mx = max(tree[i].mx, x);
        tree[i].mn = max(tree[i].mn, x);
        tree[i].lz_mx = max(tree[i].lz_mx, x);
        tree[i].lz_mn = max(tree[i].lz_mn, x);
        return;
    }
    push(i);
    mx_update(l, r, x, s, (s + e) / 2, i << 1);
    mx_update(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void mn_update(int l, int r, int x, int s, int e, int i = 1) {
    if (e < l or r < s or tree[i].mx <= x)
        return;
    if (l <= s and e <= r) {
        tree[i].mx = min(tree[i].mx, x);
        tree[i].mn = min(tree[i].mn, x);
        tree[i].lz_mn = min(tree[i].lz_mn, x);
        return;
    }
    push(i);
    mn_update(l, r, x, s, (s + e) / 2, i << 1);
    mn_update(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void print(int s, int e, int i = 1) {
    if (s == e) {
        ans.push_back(tree[i].mx);
        return;
    }
    push(i);
    print(s, (s + e) / 2, i << 1);
    print((s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n >> k;
    q.resize(k);
    for (auto &a : q) {
        cin >> a.op >> a.l >> a.r >> a.h;
        a.r++;
        v.push_back(a.l);
        v.push_back(a.r);
    }
    v.push_back(0);
    v.push_back(n);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

void solve() {
    for (auto a : q) {
        int l = lower_bound(v.begin(), v.end(), a.l) - v.begin();
        int r = lower_bound(v.begin(), v.end(), a.r) - v.begin() - 1;
        if (a.op == 1)
            mx_update(l, r, a.h, 0, v.size() - 1);
        else
            mn_update(l, r, a.h, 0, v.size() - 1);
    }
    print(0, v.size() - 1);
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = v[i]; j < v[i + 1]; j++)
            cout << ans[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
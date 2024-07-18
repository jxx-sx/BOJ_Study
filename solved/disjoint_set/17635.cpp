#include <algorithm>
#include <iostream>
#include <vector>

#define N 100001
#define B 1000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &t) const { return w > t.w; }
} e[N];

struct Query {
    int t, a, b, i, ans;
    bool operator<(const Query &t) const { return b > t.b; }
} qry[N];

int n, m, q;
int sz[N], p[N];
bool used[N];
vector<int> _used;
vector<Edge> _e;
vector<Query> _q;
vector<pair<int, int>> s;

int find_root(int x) {
    if (x == p[x])
        return x;
    return find_root(p[x]);
}

void union_root(int a, int b, int t = 0) {
    a = find_root(a);
    b = find_root(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    if (t)
        s.pb({a, b});
}

void split(int a, int b) {
    sz[a] -= sz[b];
    p[b] = b;
}

void clear() {
    _e.clear();
    _q.clear();
    _used.clear();
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i <= m; i++)
        used[i] = false;
}

void edge_init(int st, int ed) {
    for (int i = st; i < ed; i++) {
        if (qry[i].t == 1)
            used[qry[i].a] = true;
    }
    for (int i = 1; i <= m; i++)
        used[i] ? _used.pb(i) : _e.pb(e[i]);
    sort(_e.begin(), _e.end());
}

void query(int st, int ed) {
    int cur = 0;
    for (int i = st; i < ed; i++) {
        if (qry[i].t == 2)
            _q.pb(qry[i]);
    }
    sort(_q.begin(), _q.end());
    for (auto &[_, a, b, idx, ans] : _q) {
        for (; cur < _e.size(); cur++) {
            if (_e[cur].w < b)
                break;
            union_root(_e[cur].u, _e[cur].v);
        }
        for (int i = st; i < idx; i++) {
            if (qry[i].t == 1)
                swap(e[qry[i].a].w, qry[i].b);
        }
        for (auto i : _used) {
            if (b <= e[i].w)
                union_root(e[i].u, e[i].v, 1);
        }
        qry[idx].ans = sz[find_root(a)];
        while (s.size()) {
            split(s.back().first, s.back().second);
            s.pop_back();
        }
        for (int i = idx - 1; i >= st; i--) {
            if (qry[i].t == 1)
                swap(e[qry[i].a].w, qry[i].b);
        }
    }
    for (int i = st; i < ed; i++) {
        if (qry[i].t == 1)
            swap(e[qry[i].a].w, qry[i].b);
    }
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qry[i].t >> qry[i].a >> qry[i].b;
        qry[i].i = i;
    }
}

void solve() {
    for (int i = 0; i < q; i += B) {
        clear();
        edge_init(i, min(i + B, q));
        query(i, min(i + B, q));
    }
    for (int i = 0; i < q; i++) {
        if (qry[i].t == 2)
            cout << qry[i].ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
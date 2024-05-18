#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define N 100001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Qry {
    int s, e, ans, l, r, m;
} qry[N];

int n, k, q, dist[N], p[N];
vector<pair<int, int>> e[N];
vector<int> arr;
priority_queue<pair<int, int>> pq;

int find_root(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    p[a] = b;
}

void dijk() {
    while (arr.size() != n) {
        int x = pq.top().second;
        int _dist = pq.top().first;
        pq.pop();
        if (dist[x] != -1)
            continue;
        dist[x] = -_dist;
        arr.pb(x);
        for (auto [a, b] : e[x])
            if (dist[a] == -1)
                pq.push({_dist - b, a});
    }
}

void init() {
    int m, u, v, w;
    cin >> n >> m >> k >> q;
    memset(dist, -1, N << 2);
    for (int i = 1; i <= n; i++)
        p[i] = i;
    while (m--) {
        cin >> u >> v >> w;
        e[u].pb({v, w});
        e[v].pb({u, w});
    }
    while (k--) {
        cin >> u;
        arr.pb(u);
        dist[u] = 0;
        for (auto [a, b] : e[u])
            pq.push({-b, a});
    }
    dijk();
    for (int i = 0; i < q; i++) {
        cin >> qry[i].s >> qry[i].e;
        qry[i].r = n - 1;
    }
}

void solve() {
    vector<int> m[N];
    while (true) {
        bool flag = false;
        for (int i = 0; i <= n; i++) {
            m[i].clear();
            p[i] = i;
        }
        for (int i = 0; i < q; i++) {
            if (qry[i].l <= qry[i].r) {
                m[(qry[i].l + qry[i].r) >> 1].pb(i);
                flag = true;
            }
        }
        if (!flag)
            break;
        for (int i = n - 1; i >= 0; i--) {
            for (auto [a, _] : e[arr[i]])
                if (dist[a] >= dist[arr[i]])
                    union_root(a, arr[i]);
            for (auto a : m[i]) {
                if (find_root(qry[a].s) == find_root(qry[a].e)) {
                    qry[a].l = i + 1;
                    qry[a].ans = dist[arr[i]];
                } else
                    qry[a].r = i - 1;
            }
        }
    }
    for (int i = 0; i < q; i++)
        cout << qry[i].ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
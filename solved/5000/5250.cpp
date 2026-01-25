#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define N 2001
#define INF 2100000000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct Edge {
    int s, e, w;
    Edge(int s = 0, int e = 0) : s(s), e(e), w(0) {}
};

struct Node {
    int cur, lz;
    Node(int cur = INF) : cur(cur), lz(INF) {}
    // Node operator+(const Node &t) const { return Node(min(cur, t.cur)); }
} tree[N << 2];

int n, m, src, dst, k;
int dist[2][N], branch[2][N], lucky[N], ans[N];
vector<pair<int, int>> e[N];
vector<Edge> edges;

void push(int i) {
    if (tree[i].lz == INF)
        return;
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a].cur = min(tree[a].cur, tree[i].lz);
        tree[a].lz = min(tree[a].lz, tree[i].lz);
    }
    tree[i].lz = INF;
}

void update(int l, int r, int d, int s = 1, int e = k - 1, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].cur = min(tree[i].cur, d);
        tree[i].lz = min(tree[i].lz, d);
        return;
    }
    push(i);
    update(l, r, d, s, (s + e) / 2, i << 1);
    update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
}

void print(int s = 1, int e = k - 1, int i = 1) {
    if (s == e) {
        cout << (tree[i].cur == INF ? -1 : tree[i].cur) << '\n';
        return;
    }
    push(i);
    print(s, (s + e) / 2, i << 1);
    print((s + e) / 2 + 1, e, i << 1 | 1);
}

void dijk(int i, int st) {
    priority_queue<pair<int, pair<int, int>>> pq;
    for (auto [a, w] : e[st])
        pq.push({-w, {a, st}});
    dist[i][st] = 0;
    while (!pq.empty()) {
        int cur = pq.top().second.first;
        int from = pq.top().second.second;
        int cur_dist = pq.top().first;
        pq.pop();
        if (dist[i][cur] != -1)
            continue;
        dist[i][cur] = -cur_dist;
        branch[i][cur] = lucky[cur] ? cur : branch[i][from];
        for (auto [a, w] : e[cur]) {
            if (dist[i][a] == -1)
                pq.push({cur_dist - w, {a, cur}});
        }
    }
}

void init() {
    for (int i = 0; i < N; i++)
        dist[0][i] = dist[1][i] = -1;

    int v;
    cin >> n >> m >> src >> dst;
    edges.resize(m);
    for (auto &a : edges) {
        cin >> a.s >> a.e >> a.w;
        e[a.s].pb({a.e, a.w});
        e[a.e].pb({a.s, a.w});
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> v;
        lucky[v] = i;
    }
    dijk(0, src);
    dijk(1, dst);
}

void solve() {
    for (auto [s, e, w] : edges) {
        if (lucky[s] && lucky[e] && abs(lucky[s] - lucky[e]) == 1)
            continue;
        if (lucky[branch[0][s]] == lucky[branch[0][e]])
            continue;
        if (lucky[branch[0][s]] > lucky[branch[0][e]])
            swap(s, e);
        update(lucky[branch[0][s]], lucky[branch[0][e]] - 1, dist[0][s] + w + dist[1][e]);
    }
    print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
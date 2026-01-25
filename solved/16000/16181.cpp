#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define N 200001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, q, u, v, c, m, _in, sz[N], p[N], dep[N], top[N], in[N], cnt[N], road[N];
vector<int> e[N];
stack<pair<int, int>> st[N]; // Node, Color

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        e[a].erase(find(e[a].begin(), e[a].end(), x));
        p[a] = x;
        dep[a] = dep[x] + 1;
        dfs(a);
    }
}

void dfs1(int x = 1) {
    for (auto &a : e[x]) {
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[e[x][0]])
            swap(e[x][0], a);
    }
}

void dfs2(int x = 1) {
    in[x] = _in++;
    for (auto a : e[x]) {
        top[a] = a == e[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void update(int _c, int _cnt) {
    road[cnt[_c]]--;
    cnt[_c] += _cnt;
    road[cnt[_c]]++;
}

void query(int _u, int _c) {
    while (top[_u]) {
        int cur = p[top[_u]];
        while (!st[top[_u]].empty()) {
            if (dep[st[top[_u]].top().first] > dep[_u])
                break;
            update(st[top[_u]].top().second, dep[cur] - dep[st[top[_u]].top().first]);
            cur = st[top[_u]].top().first;
            st[top[_u]].pop();
        }
        if (!st[top[_u]].empty())
            update(st[top[_u]].top().second, dep[cur] - dep[_u]);
        update(_c, dep[_u] - dep[p[top[_u]]]);
        st[top[_u]].push({_u, _c});
        _u = p[top[_u]];
    }
    int cur = 1;
    while (!st[0].empty()) {
        if (dep[st[0].top().first] > dep[_u])
            break;
        update(st[0].top().second, dep[cur] - dep[st[0].top().first]);
        cur = st[0].top().first;
        st[0].pop();
    }
    if (!st[top[_u]].empty())
        update(st[top[_u]].top().second, dep[cur] - dep[_u]);
    update(_c, dep[_u]);
    st[0].push({_u, _c});
}

void init() {
    cin >> n >> road[0] >> q;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs();
    dfs1();
    dfs2();
}

void solve() {
    while (q--) {
        cin >> u >> c >> m;
        query(u, c);
        cout << road[m] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
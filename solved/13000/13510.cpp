#include <iostream>
#include <vector>

using namespace std;
int tree[404040];
int sz[101010];
int dep[101010];
int in[101010];
int node[101010];
int edge[101010];
int w[101010];
int p[101010];
int top[101010];
vector<pair<int, int>> edges[101010];
vector<int> c[101010];
int ord;
int n, m;

int tree_query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return max(tree_query(l, r, s, (s + e) / 2, i << 1), tree_query(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

void update(int k, int c, int s, int e, int i) {
    if (s == k and k == e) {
        tree[i] = c;
        return;
    }
    if (k > ((s + e) / 2))
        update(k, c, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, c, s, (s + e) / 2, i << 1);
    tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
}

int query(int s, int e) {
    int rtn = 0;
    while (top[s] != top[e]) {
        if (dep[top[s]] < dep[top[e]])
            swap(s, e);
        int st = top[s];
        rtn = max(rtn, tree_query(in[st], in[s], 1, n, 1));
        s = p[st];
    }
    if (dep[s] > dep[e])
        swap(s, e);
    rtn = max(rtn, tree_query(in[s] + 1, in[e], 1, n, 1));
    return rtn;
}

void dfs(int x) {
    sz[x] = -1;
    for (auto a : edges[x])
        if (sz[a.first] == 0) {
            c[x].push_back(a.first);
            node[a.second] = a.first;
            edge[a.first] = a.second;
            dfs(a.first);
        }
}

void dfs1(int x) {
    sz[x] = 1;
    for (auto &a : c[x]) {
        dep[a] = dep[x] + 1;
        p[a] = x;
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] < sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x) {
    ord++;
    in[x] = ord;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void init() {
    int s, e, k;
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        cin >> s >> e >> w[i];
        edges[s].push_back({e, i});
        edges[e].push_back({s, i});
    }
    cin >> m;
    dfs(1);
    dfs1(1);
    dfs2(1);
    for (int i = 1; i <= n - 1; i++)
        update(in[node[i]], w[i], 1, n, 1);
}

void solve() {
    int q, a, b;
    while (m--) {
        cin >> q >> a >> b;
        if (q == 1)
            update(in[node[a]], b, 1, n, 1);
        else
            cout << query(a, b) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
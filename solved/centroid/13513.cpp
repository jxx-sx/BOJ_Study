#include <iostream>
#include <map>
#include <set>
#include <vector>

#define N 100001
#define INF 1000100000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<pair<int, int>> e[N];

namespace HLD {
vector<pair<int, int>> c[N];
int ord;
int p[N], top[N], dep[N], in[N], sz[N], arr[N];

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto [a, w] : e[x]) {
        if (sz[a])
            continue;
        p[a] = x;
        dep[a] = dep[x] + 1;
        c[x].pb({a, w});
        dfs(a);
    }
}

void dfs1(int x = 1) {
    for (auto &a : c[x]) {
        dfs1(a.first);
        sz[x] += sz[a.first];
        if (sz[a.first] > sz[c[x][0].first])
            swap(a, c[x][0]);
    }
}

void dfs2(int x = 1) {
    in[x] = ++ord;
    for (auto [a, w] : c[x]) {
        top[a] = a == c[x][0].first ? top[x] : a;
        dfs2(a);
        arr[in[a]] = w;
    }
}

void init() {
    dfs();
    dfs1();
    dfs2();
    for (int i = 1; i < N; i++)
        arr[i] += arr[i - 1];
}

int dist(int u, int v) {
    int ret = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret += arr[in[u]] - arr[in[top[u]] - 1];
        u = p[top[u]];
    }
    if (u == v)
        return ret;
    if (dep[u] < dep[v])
        swap(u, v);
    ret += arr[in[u]] - arr[in[v]];
    return ret;
}
}; // namespace HLD

int n, m, cnt;
int p[N], sz[N];
bool visited[N], white[N];
multiset<int> dist[N], ans;
map<int, multiset<int>> sub_dist[N];

int get_sz(int x, int b = -1) {
    sz[x] = 1;
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == b)
            continue;
        sz[x] += get_sz(a, x);
    }
    return sz[x];
}

int get_centroid(int x, int b, int size) {
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == b or (sz[a] << 1) <= size)
            continue;
        return get_centroid(a, x, size);
    }
    return x;
}

int tree_init(int x = 1) {
    x = get_centroid(x, -1, get_sz(x));
    visited[x] = true;
    for (auto [a, _] : e[x]) {
        if (visited[a])
            continue;
        int tmp = tree_init(a);
        p[tmp] = x;
    }
    return x;
}

inline int mx(int x) { return *dist[x].rbegin() + *next(dist[x].rbegin()); }

void update(int x) {
    white[x] ^= 1;
    if (white[x]) {
        cnt++;
        if (dist[x].size() > 1)
            ans.erase(ans.find(*dist[x].rbegin() + *next(dist[x].rbegin())));
        dist[x].insert(0);
        if (dist[x].size() > 1)
            ans.insert(*dist[x].rbegin() + *next(dist[x].rbegin()));
    } else {
        cnt--;
        if (dist[x].size() > 1)
            ans.erase(ans.find(*dist[x].rbegin() + *next(dist[x].rbegin())));
        dist[x].erase(dist[x].find(0));
        if (dist[x].size() > 1)
            ans.insert(*dist[x].rbegin() + *next(dist[x].rbegin()));
    }
    int cur = p[x];
    int b = x;
    while (cur) {
        int d = HLD::dist(cur, x);
        if (white[x]) {
            if (sub_dist[cur][b].empty()) {
                if (dist[cur].size() > 1)
                    ans.erase(ans.find(mx(cur)));
                dist[cur].insert(d);
                if (dist[cur].size() > 1)
                    ans.insert(mx(cur));
            } else if (*sub_dist[cur][b].rbegin() < d) {
                if (dist[cur].size() > 1)
                    ans.erase(ans.find(mx(cur)));
                dist[cur].erase(dist[cur].find(*sub_dist[cur][b].rbegin()));
                dist[cur].insert(d);
                if (dist[cur].size() > 1)
                    ans.insert(mx(cur));
            }
            sub_dist[cur][b].insert(d);
        } else {
            sub_dist[cur][b].erase(sub_dist[cur][b].find(d));
            if (sub_dist[cur][b].empty()) {
                if (dist[cur].size() > 1)
                    ans.erase(ans.find(mx(cur)));
                dist[cur].erase(dist[cur].find(d));
                if (dist[cur].size() > 1)
                    ans.insert(mx(cur));
            } else if (*sub_dist[cur][b].rbegin() < d) {
                if (dist[cur].size() > 1)
                    ans.erase(ans.find(mx(cur)));
                dist[cur].erase(dist[cur].find(d));
                dist[cur].insert(*sub_dist[cur][b].rbegin());
                if (dist[cur].size() > 1)
                    ans.insert(mx(cur));
            }
        }
        b = cur;
        cur = p[cur];
    }
}

void init() {
    int a, b, w;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> a >> b >> w;
        e[a].pb({b, w});
        e[b].pb({a, w});
    }
    cin >> m;
    tree_init();
    HLD::init();
    for (int i = 1; i <= n; i++)
        update(i);
}

void solve() {
    int op, i;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> i;
            update(i);
        } else
            cout << (cnt ? ans.empty() ? 0 : max(*ans.rbegin(), 0) : -1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}

/*
10
1 2 1
1 3 1
2 4 1
2 5 1
3 6 1
3 7 1
4 8 1
4 9 1
5 10 1
0
*/
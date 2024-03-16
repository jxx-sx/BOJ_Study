#include <iostream>
#include <vector>

#define N 200001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<pair<int, int>> e[N], dfs_ret;
vector<int> modified;
bool visited[N];
int n, k, ans = N;
int sz[N];
int dist_cnt[1000001];

inline void reset() {
    for (auto a : modified)
        dist_cnt[a] = N;
    modified.clear();
}

int get_sz(int x, int p = -1) {
    sz[x] = 1;
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == p)
            continue;
        sz[x] += get_sz(a, x);
    }
    return sz[x];
}

int get_cent(int x, int p, int size) {
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == p or (sz[a] << 1) <= size)
            continue;
        return get_cent(a, x, size);
    }
    return x;
}

void dfs(int x, int p, int cnt, int dist) {
    if (dist > k)
        return;
    dfs_ret.pb({cnt, dist});
    ans = min(dist_cnt[k - dist] + cnt, ans);
    for (auto [a, w] : e[x]) {
        if (visited[a] or a == p)
            continue;
        dfs(a, x, cnt + 1, dist + w);
    }
}

void query(int x = 1, int p = -1) {
    x = get_cent(x, -1, get_sz(x));
    visited[x] = true;
    for (auto [a, w] : e[x]) {
        if (visited[a] or a == p)
            continue;
        dfs(a, x, 1, w);
        for (auto [cnt, dist] : dfs_ret) {
            dist_cnt[dist] = min(dist_cnt[dist], cnt);
            modified.push_back(dist);
        }
        dfs_ret.clear();
    }
    ans = min(ans, dist_cnt[k]);
    reset();
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == p)
            continue;
        query(a, x);
    }
}

void init() {
    cin >> n >> k;
    int a, b, c;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;
        e[a].pb({b, c});
        e[b].pb({a, c});
    }
    for (int i = 0; i < 1000001; i++)
        dist_cnt[i] = N;
}

void solve() {
    query();
    cout << (ans == N ? -1 : ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
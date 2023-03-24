#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> edges[100001];
int dp[100001][17];
long long dist[100001][17];
int depth[100001];
bool is_visit[100001];
int n;

void dfs(int x, int d) {
    is_visit[x] = true;
    depth[x] = d;
    for (auto a : edges[x])
        if (!is_visit[a.first]) {
            dp[a.first][0] = x;
            dist[a.first][0] = a.second;
            dfs(a.first, d + 1);
        }
}

void lca_init() {
    for (int i = 1; i < 17; i++)
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
            dist[j][i] = dist[j][i - 1] + dist[dp[j][i - 1]][i - 1];
        }
}

int get_lca(int a, int b) {
    if (depth[a] > depth[b])
        swap(a, b);
    int diff = depth[b] - depth[a];
    int i = 0;

    while (diff) {
        if (diff & 1) {
            b = dp[b][i];
        }
        diff >>= 1;
        i++;
    }

    for (i = 16; i >= 0; i--)
        if (dp[a][i] != dp[b][i]) {
            a = dp[a][i];
            b = dp[b][i];
        }

    while (a != b) {
        a = dp[a][0];
        b = dp[b][0];
    }

    return a;
}

long long query_1(int a, int b) {
    long long rtn = 0;

    if (depth[a] > depth[b])
        swap(a, b);
    int diff = depth[b] - depth[a];
    int i = 0;

    while (diff) {
        if (diff & 1) {
            rtn += dist[b][i];
            b = dp[b][i];
        }
        diff >>= 1;
        i++;
    }

    if (a == b)
        return rtn;

    for (i = 16; i >= 0; i--)
        if (dp[a][i] != dp[b][i]) {
            rtn += dist[a][i];
            a = dp[a][i];
            rtn += dist[b][i];
            b = dp[b][i];
        }

    while (a != b) {
        rtn += dist[a][0];
        a = dp[a][0];
        rtn += dist[b][0];
        b = dp[b][0];
    }
    return rtn;
}

int query_2(int s, int e, int k) {
    k -= 1;
    int lca = get_lca(s, e);
    int diff;
    if (depth[s] - depth[lca] >= k) {
        diff = k;
        int i = 0;
        while (diff) {
            if (diff & 1) {
                s = dp[s][i];
            }
            diff >>= 1;
            i++;
        }
        return s;
    } else {
        diff = depth[e] + depth[s] - (depth[lca] << 1) - k;
        int i = 0;
        while (diff) {
            if (diff & 1) {
                e = dp[e][i];
            }
            diff >>= 1;
            i++;
        }
        return e;
    }
}

void init() {
    int s, e, w;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> s >> e >> w;
        edges[s].push_back({e, w});
        edges[e].push_back({s, w});
    }

    dfs(1, 0);
    lca_init();
    return;
}

void solve() {
    int q, u, v, k, m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q >> u >> v;
        if (q == 1)
            cout << query_1(u, v) << '\n';
        else {
            cin >> k;
            cout << query_2(u, v, k) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> edges[40001];
int dp[40001][17];
int dist[40001][17];
int h[40001];
bool is_visit[40001];
int n;

void dfs(int x, int d) {
    is_visit[x] = true;
    h[x] = d;
    for (auto a : edges[x]) {
        if (!is_visit[a.first]) {
            dp[a.first][0] = x;
            dist[a.first][0] = a.second;
            dfs(a.first, d + 1);
        }
    }
}

void lca_init() {
    for (int i = 1; i < 17; i++)
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
            dist[j][i] = dist[j][i - 1] + dist[dp[j][i - 1]][i - 1];
        }
}

int lca(int a, int b) {
    int ret = 0;
    if (h[a] > h[b]) // b가 더 아래여야함
        swap(a, b);
    int diff = h[b] - h[a];
    int i = 0;
    while (diff) {
        if (diff & 1) {
            ret += dist[b][i];
            b = dp[b][i];
        }
        diff >>= 1;
        i++;
    }

    if (a == b)
        return ret;

    for (i = 16; i >= 0; i--) {
        if (dp[a][i] != dp[b][i]) {
            ret += dist[a][i];
            a = dp[a][i];
            ret += dist[b][i];
            b = dp[b][i];
        }
    }

    while (a != b) {
        ret += dist[a][0];
        a = dp[a][0];
        ret += dist[b][0];
        b = dp[b][0];
    }
    return ret;
}

void init() {
    int s, e, t;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e >> t;
        edges[s].push_back({e, t});
        edges[e].push_back({s, t});
    }

    dfs(1, 0);
    lca_init();

    return;
}

void solve() {
    int m, a, b;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}
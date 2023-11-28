#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define N 501
#define pb push_back

using namespace std;

int S, T;
int n, m;
int c[N][N], f[N][N];
int work[N], level[N];
vector<int> e[N];
queue<int> q;

bool bfs() {
    memset(level, -1, N << 2);
    level[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto next : e[cur]) {
            if (level[next] == -1 and c[cur][next] - f[cur][next] > 0) {
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
    }

    return level[T] != -1;
}

int dfs(int x, int flow) {
    if (x == T)
        return flow;
    for (int &i = work[x]; i < e[x].size(); i++) {
        int next = e[x][i];
        if (level[next] == level[x] + 1 and c[x][next] - f[x][next] > 0) {
            int ret = dfs(next, min(flow, c[x][next] - f[x][next]));

            if (ret > 0) {
                f[x][next] += ret;
                f[next][x] -= ret;
                return ret;
            }
        }
    }

    return 0;
}

void init() {
    int a, b, d;
    int cnt, work;
    cin >> n >> m;

    while (m--) {
        cin >> a >> b >> d;
        c[a][b] = d;
        c[b][a] = d;
        e[a].pb(b);
        e[b].pb(a);
    }

    cin >> S >> T;
}

void solve() {
    int ans = 0;
    int flow;
    while (bfs()) {
        memset(work, 0, N << 2);
        while ((flow = dfs(S, 1000)))
            ans += flow;
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
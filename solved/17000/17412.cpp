#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define S 1
#define T 2
#define N 401
#define pb push_back

using namespace std;

int n, p;
int c[N][N], f[N][N];
int level[N], work[N];
vector<int> e[N];
queue<int> q;

bool bfs() {
    memset(level, -1, N << 2);
    level[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto a : e[cur]) {
            if (level[a] == -1 and c[cur][a] - f[cur][a] > 0) {
                q.push(a);
                level[a] = level[cur] + 1;
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
    int a, b;
    cin >> n >> p;
    while (p--) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
        c[a][b] = 1;
    }
}

void solve() {
    int flow, ans = 0;
    while (bfs()) {
        memset(work, 0, N << 2);
        while ((flow = dfs(S, 1)) > 0)
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
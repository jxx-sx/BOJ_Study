#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define S 2001
#define M 2002
#define T 2003
#define N 2004
#define INF 1000
#define pb push_back

using namespace std;

int n, m, k;
int c[N][N];
int f[N][N];
int work[N];
int level[N];
vector<int> e[N];
queue<int> q;

bool bfs() {
    memset(level, -1, sizeof(level));
    level[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto next : e[cur])
            if (level[next] == -1 and c[cur][next] - f[cur][next] > 0) {
                level[next] = level[cur] + 1;
                q.push(next);
            }
    }

    return level[T] != -1;
}

int dfs(int x, int flow) {
    if (x == T)
        return flow;
    for (int &i = work[x]; i < e[x].size(); i++) {
        int next = e[x][i];
        if (level[next] == level[x] + 1 && c[x][next] - f[x][next] > 0) {
            int ret = dfs(next, min(c[x][next] - f[x][next], flow));

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
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        c[S][i] = 1;
        c[M][i] = 1;
        e[S].pb(i);
        e[M].pb(i);
        e[i].pb(S);
        e[i].pb(M);
    }

    for (int i = 1; i <= m; i++) {
        c[i + 1000][T] = 1;
        e[i + 1000].pb(T);
        e[T].pb(i + 1000);
    }
    c[S][M] = k;
    e[S].pb(M);
    e[M].pb(S);
    for (int i = 1; i <= n; i++) {
        int cnt, w;
        cin >> cnt;
        while (cnt--) {
            cin >> w;
            c[i][w + 1000] = 1;
            e[i].pb(w + 1000);
            e[w + 1000].pb(i);
        }
    }
}

void solve() {
    int ans = 0;

    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (true) {
            int flow = dfs(S, INF);
            if (!flow)
                break;
            ans += flow;
        }
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
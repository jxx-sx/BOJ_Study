#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define S 201
#define T 202
#define N 203
#define pb push_back

using namespace std;

int n, m, ans;
int c[N][N], f[N][N];
int level[N], work[N];
vector<int> e[N];
queue<int> q;

bool bfs() {
    memset(level, -1, N << 2);
    level[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto a : e[x]) {
            if (level[a] == -1 and c[x][a] - f[x][a] > 0) {
                level[a] = level[x] + 1;
                q.push(a);
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
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c[S][i];
        e[S].pb(i);
        e[i].pb(S);
    }
    for (int i = 101; i <= m + 100; i++) {
        cin >> c[i][T];
        e[i].pb(T);
        e[T].pb(i);
    }
    for (int j = 101; j <= m + 100; j++)
        for (int i = 1; i <= n; i++) {
            cin >> c[i][j];
            e[i].pb(j);
            e[j].pb(i);
        }
}

void solve() {
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
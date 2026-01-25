#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define pb push_back
#define INF 100000000

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int S, T;
int c[440][440], f[440][440];
int work[440], level[440];
bool visited[440];
int n, m;
vector<int> e[440];

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(S);
    level[S] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto a : e[cur]) {
            if (level[a] == -1 and c[cur][a] - f[cur][a] > 0) {
                level[a] = level[cur] + 1;
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
        if (level[next] == level[x] + 1 and c[x][next] - f[x][next]) {
            int ret = dfs(next, min(flow, c[x][next] - f[x][next]));
            if (ret) {
                f[x][next] += ret;
                f[next][x] -= ret;
                return ret;
            }
        }
    }
    return 0;
}

void bfs1() {
    queue<int> q;
    q.push(S);
    visited[S] = true;
    while (!q.empty()) {
        for (auto a : e[q.front()]) {
            if (!visited[a] and c[q.front()][a] - f[q.front()][a] > 0) {
                visited[a] = true;
                q.push(a);
            }
        }
        q.pop();
    }
}

void init() {
    cin >> n >> m >> S >> T;
    S <<= 1;
    T = T << 1 | 1;
    for (int i = 1; i <= n; i++) {
        cin >> c[i << 1][i << 1 | 1];
        e[i << 1].pb(i << 1 | 1);
        e[i << 1 | 1].pb(i << 1);
    }
    int a, b;
    while (m--) {
        cin >> a >> b;
        e[a << 1 | 1].pb(b << 1);
        e[b << 1].pb(a << 1 | 1);
        c[a << 1 | 1][b << 1] = INF;

        e[b << 1 | 1].pb(a << 1);
        e[a << 1].pb(b << 1 | 1);
        c[b << 1 | 1][a << 1] = INF;
    }
}

void solve() {
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (dfs(S, INF))
            ;
    }
    bfs1();
    for (int i = 1; i <= n; i++) {
        if (visited[i << 1] ^ visited[i << 1 | 1])
            cout << i << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
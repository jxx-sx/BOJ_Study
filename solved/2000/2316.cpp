#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define S 2
#define T 5
#define N 1000
#define pb push_back

using namespace std;

int n, p;
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
    cin >> n >> p;
    c[2][3] = 1000;
    e[2].pb(3);
    e[3].pb(2);
    c[4][5] = 1000;
    e[4].pb(5);
    e[5].pb(4);
    for (int i = 3; i <= n; i++) {
        c[i << 1][i << 1 | 1] = 1;
        e[i << 1].pb(i << 1 | 1);
        e[i << 1 | 1].pb(i << 1);
    }

    int a, b;
    for (int i = 0; i < p; i++) {
        cin >> a >> b;
        c[a << 1 | 1][b << 1] = 1;
        e[a << 1 | 1].pb(b << 1);
        e[b << 1].pb(a << 1 | 1);
        c[b << 1 | 1][a << 1] = 1;
        e[a << 1].pb(b << 1 | 1);
        e[b << 1 | 1].pb(a << 1);
    }
}

void solve() {
    int ans = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (true) {
            int flow = dfs(S, 1000);
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
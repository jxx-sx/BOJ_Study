#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define S 0
#define T 25
#define N 52
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
    char a, b;
    int k;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> k;
        a -= a >= 'a' ? 'a' - 26 : 'A';
        b -= b >= 'a' ? 'a' - 26 : 'A';
        if (!c[a][b])
            e[a].pb(b);
        c[a][b] += k;
        if (!c[b][a])
            e[b].pb(a);
        c[b][a] += k;
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
#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define pb push_back
#define S 0
#define T 2001

using namespace std;

int n, m;
int c[2002][2002], f[2002][2002];
int level[2002], work[2002];
vector<int> e[2002];

bool bfs() {
    memset(level, -1, sizeof(level));
    level[S] = 0;
    queue<int> q;
    q.push(S);

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
        if (level[e[x][i]] == level[x] + 1 and c[x][e[x][i]] - f[x][e[x][i]] > 0) {
            int ret = dfs(e[x][i], min(flow, c[x][e[x][i]] - f[x][e[x][i]]));

            if (ret > 0) {
                f[x][e[x][i]] += ret;
                f[e[x][i]][x] -= ret;
                return ret;
            }
        }
    }
    return 0;
}

void init() {
    int cnt, w;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        e[S].pb(i);
        e[i].pb(S);
        c[S][i] = 2;

        cin >> cnt;
        while (cnt--) {
            cin >> w;
            e[i].pb(w + 1000);
            e[w + 1000].pb(i);
            c[i][w + 1000] = 1;
        }
    }
    for (int i = 1; i <= m; i++) {
        e[i + 1000].pb(T);
        e[T].pb(i + 1000);
        c[i + 1000][T] = 1;
    }
}

void solve() {
    int tmp;
    int ans = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while ((tmp = dfs(S, 1000)))
            ans += tmp;
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
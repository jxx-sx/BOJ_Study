#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

#define S 301
#define T 302
#define pb push_back
#define N 303

using namespace std;

int n, k, d;
int c[N][N];
int f[N][N];
int level[N];
int work[N];
vector<int> e[N];
queue<int> q;

bool bfs() {
    memset(level, -1, sizeof(level));
    level[S] = 0;
    q.push(S);
    while (!q.empty()) {
        for (auto a : e[q.front()]) {
            if (level[a] == -1 and c[q.front()][a] - f[q.front()][a] > 0) {
                level[a] = level[q.front()] + 1;
                q.push(a);
            }
        }
        q.pop();
    }
    return level[T] != -1;
}

int dfs(int x, int flow) {
    if (x == T)
        return flow;
    for (int &i = work[x]; i < e[x].size(); i++) {
        int next = e[x][i];
        if (level[next] == level[x] + 1 and c[x][next] - f[x][next] > 0) {
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
    cin >> n >> k >> d;
    for (int i = 1; i <= n; i++) {
        c[S][i] = k;
        e[S].pb(i);
        e[i].pb(S);
    }

    for (int i = 1; i <= d; i++) {
        cin >> c[i + 200][T];
        e[i + 200].pb(T);
        e[T].pb(i + 200);
    }

    int z, food;
    for (int i = 1; i <= n; i++) {
        cin >> z;
        while (z--) {
            cin >> food;
            c[i][food + 200] = 1;
            e[i].pb(food + 200);
            e[food + 200].pb(i);
        }
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
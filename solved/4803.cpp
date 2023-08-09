#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[505];
int p[505], visited[505];
int n, m;
int a, b;
int ans, tc;

bool dfs(int x) {
    visited[x] = 1;
    for (auto a : edges[x]) {
        if (visited[a] and p[x] == a)
            continue;
        if (visited[a])
            return false;
        p[a] = x;
        if (!dfs(a))
            return false;
    }
    return true;
}
bool init() {
    cin >> n >> m;

    if (n or m) {
        for (int i = 1; i <= n; i++) {
            edges[i].clear();
            p[i] = visited[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        ans = 0;
        return true;
    }
    return false;
}

void solve() {
    tc++;
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            if (dfs(i))
                ans++;
    cout << "Case " << tc << ": ";
    if (ans == 0)
        cout << "No trees.\n";
    else if (ans == 1)
        cout << "There is one tree.\n";
    else
        cout << "A forest of " << ans << " trees.\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}
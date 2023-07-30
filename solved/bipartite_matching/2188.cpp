#include <iostream>
#include <vector>
#define pb push_back

using namespace std;

int n, m, ord, ans;
int a[201], b[201], cur[201], visited[201];
vector<int> e[201];

bool dfs(int x) {
    if (visited[x] == ord)
        return false;
    visited[x] = ord;
    for (int i = cur[x]; i < e[x].size(); i++) {
        if (b[e[x][i]] == 0 or dfs(b[e[x][i]])) {
            a[x] = e[x][i];
            b[e[x][i]] = x;
            return true;
        }
    }
    return false;
}

void init() {
    int c, s;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c;
        while (c--) {
            cin >> s;
            e[i].pb(s);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        ord++;
        if (dfs(i))
            ans++;
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
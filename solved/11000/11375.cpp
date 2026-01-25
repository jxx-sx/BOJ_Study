#include <iostream>
#include <vector>
#define pb push_back

using namespace std;

int n, m, ord, ans;
int a[1001], b[1001], cnt[1001], visited[1001];
vector<int> e[1001];

bool dfs(int x) {
    if (visited[x] == ord)
        return false;
    visited[x] = ord;
    for (int i = cnt[x]; i < e[x].size(); i++) {
        if (b[e[x][i]] == 0 or dfs(b[e[x][i]])) {
            a[x] = e[x][i];
            b[e[x][i]] = x;
            return true;
        }
    }
    return false;
}

void init() {
    int c, w;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c;
        while (c--) {
            cin >> w;
            e[i].pb(w);
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
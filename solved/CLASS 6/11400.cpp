#include <algorithm>
#include <iostream>
#include <vector>

#define N 100001
#define pb push_back

using namespace std;

int v, e, ord, visited[N], l[N];
vector<int> edges[N];
vector<pair<int, int>> ans;

int dfs(int x, int p = 0) {
    visited[x] = l[x] = ++ord;
    for (auto a : edges[x]) {
        if (a == p)
            continue;
        if (!visited[a])
            l[x] = min(l[x], dfs(a, x));
        else
            l[x] = min(l[x], l[a]);
    }

    if (l[x] == visited[x] and p) {
        ans.pb(min(make_pair(x, p), make_pair(p, x)));
    }

    return l[x];
}

void init() {
    int a, b;
    cin >> v >> e;
    while (e--) {
        cin >> a >> b;
        edges[a].pb(b);
        edges[b].pb(a);
    }
}

void solve() {
    dfs(1);
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto a : ans) {
        cout << a.first << ' ' << a.second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
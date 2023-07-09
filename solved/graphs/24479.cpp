#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, r;
vector<int> edges[100001];
int cnt = 0;
int ans[100001];

void dfs(int x) {
    if (ans[x])
        return;
    cnt++;
    ans[x] = cnt;
    for (auto a : edges[x])
        dfs(a);
}

void init() {
    int s, e;
    cin >> n >> m >> r;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        edges[e].push_back(s);
    }
    for (int i = 1; i <= n; i++)
        sort(edges[i].begin(), edges[i].end());
}

void solve() {
    dfs(r);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

int n, r, q;
vector<int> edges[100001];
bool visited[100001];
int child[100001];

int dfs(int x) {
    visited[x] = true;

    for (auto a : edges[x])
        if (!visited[a])
            child[x] += dfs(a);

    return child[x] + 1;
}

void init() {
    int s, e;
    cin >> n >> r >> q;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        edges[e].push_back(s);
    }

    dfs(r);

    return;
}

void solve() {
    int v;
    for (int i = 0; i < q; i++) {
        cin >> v;
        cout << child[v] + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;
vector<int> edges[500001];
bool visited[500001];
int n;
int cnt;

void dfs(int x, int d) {
    bool leaf = true;
    visited[x] = true;
    for (auto a : edges[x])
        if (!visited[a]) {
            dfs(a, d + 1);
            leaf = false;
        }
    if (leaf)
        cnt += d;
}

void init() {
    int s, e;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        edges[e].push_back(s);
    }
}

void solve() {
    dfs(1, 0);
    if (cnt % 2)
        cout << "Yes";
    else
        cout << "No";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
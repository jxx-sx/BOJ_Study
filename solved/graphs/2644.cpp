#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[101];
int n, m;
int a, b;
int arr[101];

void dfs(int x, int d) {
    arr[x] = d;
    for (auto a : edges[x])
        if (arr[a] == -1)
            dfs(a, d + 1);
}

void init() {
    int p, c;
    cin >> n >> a >> b >> m;
    for (int i = 0; i < m; i++) {
        cin >> p >> c;
        edges[p].push_back(c);
        edges[c].push_back(p);
    }
    for (int i = 1; i <= n; i++)
        arr[i] = -1;
}

void solve() {
    dfs(a, 0);
    cout << arr[b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
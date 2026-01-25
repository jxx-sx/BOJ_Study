#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int arr[100001];
int ans[100001];
int n, m;
vector<int> e[100001];

void dfs(int x, int d = 0) {
    d += arr[x];
    ans[x] = d;
    for (auto a : e[x])
        dfs(a, d);
}

void init() {
    cin >> n >> m;
    int p;
    cin >> p;
    for (int i = 2; i <= n; i++) {
        cin >> p;
        e[p].push_back(i);
    }
}

void solve() {
    int x, w;
    while (m--) {
        cin >> x >> w;
        arr[x] += w;
    }

    dfs(1);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
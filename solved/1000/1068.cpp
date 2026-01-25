#include <iostream>
#include <vector>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<int> v[50];
int n, m, r, ans, arr[50];

void dfs(int x = r) {
    if (v[x].empty())
        ans++;
    for (auto a : v[x])
        dfs(a);
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> m;
    for (int i = 0; i < n; i++) {
        if (arr[i] == -1) {
            r = i;
            continue;
        }
        if (i == m)
            continue;
        v[arr[i]].pb(i);
    }
}

void solve() {
    dfs();
    cout << (m == r ? 0 : ans);
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}
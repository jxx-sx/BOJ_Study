#include <algorithm>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct E {
    int u, v, w;
    bool operator<(const E &t) const { return w < t.w; }
} e[100000];

int n, m, ans = 1001;
int arr[10001];
int p[10001];

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

bool union_root(int a, int b) {
    a = find_root(a);
    p[a] = find_root(b);
    return a != p[a];
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i], ans = min(arr[i], ans), p[i] = i;
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].w = (e[i].w << 1) + arr[e[i].u] + arr[e[i].v];
    }
    sort(e, e + m);
}

void solve() {
    for (int i = 0; i < m && n > 1; i++) {
        if (union_root(e[i].u, e[i].v)) {
            ans += e[i].w;
            n--;
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}
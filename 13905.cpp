#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m, s, e;
vector<pair<int, pair<int, int>>> edges;
int p[100001];
int r[100001];

int find_root(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (r[a] > r[b]) {
        r[a]++;
        p[b] = a;
    } else {
        r[b]++;
        p[a] = b;
    }
}

void solve() {
    int h1, h2, k;
    int ans = 1000000;
    while (find_root(s) != find_root(e)) {
        h1 = edges.back().second.first;
        h2 = edges.back().second.second;
        k = edges.back().first;
        edges.pop_back();
        
        if (find_root(h1) != find_root(h2)) {
            union_root(h1, h2);
            ans = min(ans, k);
        }
    }
    cout << ans;
}

void init() {
    cin >> n >> m >> s >> e;
    int a, b, c;
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        r[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges.push_back({a, {b, c}});
    }

    sort(edges.begin(), edges.end());

    solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    return 0;
}
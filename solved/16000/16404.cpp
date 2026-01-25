#include <iostream>
#include <vector>

using namespace std;
vector<int> edges[100001];
pair<int, int> interval[100001];
int tree[400000];
int cur, n, m;

void push_down(int i) {
    if (tree[i]) {
        tree[i << 1] += tree[i];
        tree[i << 1 | 1] += tree[i];
        tree[i] = 0;
    }
}

void dfs(int x) {
    cur++;
    interval[x].first = cur;
    for (auto a : edges[x])
        dfs(a);
    interval[x].second = cur;
}

void update(int l, int r, int d, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] += d;
        return;
    }
    update(l, r, d, s, (s + e) / 2, i << 1);
    update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
}

int query(int k, int s, int e, int i) {
    if (s == e)
        return tree[i];
    push_down(i);
    if ((s + e) / 2 < k)
        return query(k, (s + e) / 2 + 1, e, i << 1 | 1);
    return query(k, s, (s + e) / 2, i << 1);
}

void init() {
    int p;
    cin >> n >> m >> p;
    for (int i = 2; i <= n; i++) {
        cin >> p;
        edges[p].push_back(i);
    }
    dfs(1);
}

void solve() {
    int q, a, b;
    for (int i = 0; i < m; i++) {
        cin >> q >> a;
        if (q == 1) {
            cin >> b;
            update(interval[a].first, interval[a].second, b, 1, n, 1);
        } else
            cout << query(interval[a].first, 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
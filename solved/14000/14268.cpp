#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[100001];
pair<int, int> itv[100001];
int tree[400000];
int reord[100001];
int cur;
int n, m;

void push_down(int i) {
    if (tree[i]) {
        tree[i << 1] += tree[i];
        tree[i << 1 | 1] += tree[i];
        tree[i] = 0;
    }
}

void dfs(int x) {
    cur++;
    reord[x] = cur;
    itv[x].first = cur;
    for (auto a : edges[x])
        dfs(a);
    itv[x].second = cur;
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
        edges[p].emplace_back(i);
    }
    dfs(1);
    return;
}

void solve() {
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (a == 1) {
            cin >> c;
            update(itv[b].first, itv[b].second, c, 1, n, 1);
        } else
            cout << query(reord[b], 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
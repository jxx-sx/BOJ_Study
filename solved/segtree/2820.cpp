#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[500001];
int tree[2000000];
pair<int, int> interval[500001];
int reorder[500001];
int reorder2[500001];
int salary[500001];
int cur = 1;
int n, m;

void push_down(int x) {
    if (tree[x]) {
        tree[x << 1] += tree[x];
        tree[x << 1 | 1] += tree[x];
        tree[x] = 0;
    }
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

int query(int x, int s, int e, int i) {
    if (s == e)
        return tree[i];
    push_down(i);
    if ((s + e) / 2 < x)
        return query(x, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        return query(x, s, (s + e) / 2, i << 1);
}

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i] = salary[reorder[s]];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void dfs(int x) {
    reorder[cur] = x;
    reorder2[x] = cur;

    cur++;
    interval[x].first = cur;
    for (auto a : edges[x])
        dfs(a);
    interval[x].second = cur - 1;
}

void init() {
    cin >> n >> m >> salary[1];
    int p;
    for (int i = 2; i <= n; i++) {
        cin >> salary[i] >> p;
        edges[p].push_back(i);
    }
    dfs(1);
    tree_init(1, n, 1);

    return;
}

void solve() {
    char ch;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> ch >> a;
        if (ch == 'p') {
            cin >> b;
            update(interval[a].first, interval[a].second, b, 1, n, 1);
        } else {
            cout << query(reorder2[a], 1, n, 1) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
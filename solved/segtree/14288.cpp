#include <iostream>
#include <vector>

using namespace std;

vector<int> childs[100001];
int p[100001];
int tree[400000];
int n, m;
pair<int, int> interval[100000];
int cur;
bool is_range = true;

void dfs(int x) {
    cur++;
    interval[x].first = cur;
    for (auto a : childs[x])
        dfs(a);
    interval[x].second = cur;
}

void push_down(int i) {
    if (tree[i]) {
        tree[i << 1] += tree[i];
        tree[i << 1 | 1] += tree[i];
        tree[i] = 0;
    }
}

void point_update(int x, int k, int s, int e, int i) {
    if (s == e) {
        tree[i] += k;
        return;
    }
    if ((s + e) / 2 < x)
        point_update(x, k, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        point_update(x, k, s, (s + e) / 2, i << 1);
}

void range_update(int l, int r, int k, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] += k;
        return;
    }
    range_update(l, r, k, s, (s + e) / 2, i << 1);
    range_update(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
}

int query(int x, int s, int e, int i) {
    if (s == e)
        return tree[i];
    push_down(i);
    if ((s + e) / 2 < x)
        return query(x, (s + e) / 2 + 1, e, i << 1 | 1);
    return query(x, s, (s + e) / 2, i << 1);
}

void init() {
    int inp;
    cin >> n >> m >> inp;
    for (int i = 2; i <= n; i++) {
        cin >> inp;
        childs[inp].push_back(i);
        p[i] = inp;
    }
    dfs(1);
}

void solve() {
    int q, w, i;
    while (m--) {
        cin >> q;
        if (q == 1) {
            cin >> i >> w;
            if (is_range)
                range_update(interval[i].first, interval[i].second, w, 1, n, 1);
            else {
                while (i != 0) {
                    point_update(interval[i].first, w, 1, n, 1);
                    i = p[i];
                }
            }
        } else if (q == 2) {
            cin >> i;
            cout << query(interval[i].first, 1, n, 1) << '\n';
        } else
            is_range = !is_range;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
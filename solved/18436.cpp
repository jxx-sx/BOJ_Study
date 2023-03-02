#include <iostream>

using namespace std;

int n;
pair<int, int> tree[400000];
int tree_data[100000];
int tree_index[100000];

pair<int, int> tree_init(int s, int e, int i) {
    if (s == e) {
        tree_index[s] = i;
        if (tree_data[s] & 1)
            tree[i] = {1, 0};
        else
            tree[i] = {0, 1};
        return tree[i];
    }
    pair<int, int> l = tree_init(s, (s + e) / 2, i << 1);
    pair<int, int> r = tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
    return tree[i] = {l.first + r.first, l.second + r.second};
}

void tree_update(int i, int x) {
    int cur = tree_index[i];
    if (x & 1)
        tree[cur] = {1, 0};
    else
        tree[cur] = {0, 1};

    while ((cur >>= 1) > 0) {
        tree[cur] = {tree[cur << 1].first + tree[(cur << 1) | 1].first, tree[cur << 1].second + tree[(cur << 1) | 1].second};
    }
}

pair<int, int> tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return {0, 0};
    if (l <= s and e <= r)
        return tree[i];
    pair<int, int> l_c = tree_find(l, r, s, (s + e) / 2, i << 1);
    pair<int, int> r_c = tree_find(l, r, (s + e) / 2 + 1, e, (i << 1) | 1);
    return {l_c.first + r_c.first, l_c.second + r_c.second};
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];
    tree_init(0, n - 1, 1);
    return;
}

void solve() {
    int m;
    cin >> m;
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a == 1)
            tree_update(b - 1, c);
        else {
            pair<int, int> ans = tree_find(b - 1, c - 1, 0, n - 1, 1);
            if (a & 1)
                cout << ans.first << '\n';
            else
                cout << ans.second << '\n';
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
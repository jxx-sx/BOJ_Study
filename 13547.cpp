#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> tree[400000];
vector<int> query_v;
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        int inp;
        cin >> inp;
        tree[i].emplace_back(inp);
        return;
    }

    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);

    int l = 0, r = 0;

    while (l != tree[i << 1].size() and r != tree[i << 1 | 1].size()) {
        tree[i].emplace_back(min(tree[i << 1][l], tree[i << 1 | 1][r]));
        tree[i << 1][l] < tree[i << 1 | 1][r] ? l++ : r++;
    }
    while (l != tree[i << 1].size()) {
        tree[i].emplace_back(tree[i << 1][l]);
        l++;
    }
    while (r != tree[i << 1 | 1].size()) {
        tree[i].emplace_back(tree[i << 1 | 1][r]);
        r++;
    }
}

void query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        for (auto a : tree[i])
            query_v.emplace_back(a);
        return;
    }
    query(l, r, s, (s + e) / 2, i << 1);
    query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n;
    tree_init(1, n, 1);
    return;
}

void solve() {
    int l, r;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        query_v.clear();
        cin >> l >> r;
        query(l, r, 1, n, 1);
        sort(query_v.begin(), query_v.end());
        cout << unique(query_v.begin(), query_v.end()) - query_v.begin() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
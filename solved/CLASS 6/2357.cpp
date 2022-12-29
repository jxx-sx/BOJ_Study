#include <iostream>
#include <vector>
#define MAX_INT 1000000001

using namespace std;
vector<pair<int, int>> tree;
vector<int> tree_data;
int n, m;

pair<int, int> find_min_max(int index, int s, int e, int l, int r) {
    if (e < l or r < s)
        return make_pair(MAX_INT, -1);
    if (l <= s and e <= r)
        return tree[index];
    pair<int, int> l_c = find_min_max(index * 2, s, (s + e) / 2, l, r);
    pair<int, int> r_c = find_min_max(index * 2 + 1, (s + e) / 2 + 1, e, l, r);
    return {min(l_c.first, r_c.first), max(l_c.second, r_c.second)};
}

pair<int, int> tree_init(int index, int s, int e) {
    if (s == e)
        return tree[index] = {tree_data[s], tree_data[s]}; //{min, max}

    pair<int, int> l_c = tree_init(index * 2, s, (s + e) / 2);
    pair<int, int> r_c = tree_init(index * 2 + 1, (s + e) / 2 + 1, e);
    return tree[index] = {min(l_c.first, r_c.first), max(l_c.second, r_c.second)};
}

void init() {
    cin >> n >> m;
    tree = vector<pair<int, int>>(n * 4, {0, 0});
    tree_data = vector<int>(n, 0);
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];
    tree_init(1, 0, n - 1);

    return;
}

void solve() {
    int a, b;
    pair<int, int> ans;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        ans = find_min_max(1, 0, n - 1, a - 1, b - 1);
        cout << ans.first << ' ' << ans.second << '\n';
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
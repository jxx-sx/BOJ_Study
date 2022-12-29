#include <iostream>
#include <vector>

using namespace std;
vector<pair<int, int>> tree;
vector<int> tree_data, data_index;
int n, m;

pair<int, int> find_min_max(int index, int s, int e, int l, int r) {
    if (e < l or r < s)
        return {-1, -1};
    if (l <= s and e <= r)
        return tree[index];
    pair<int, int> l_c = find_min_max(index * 2, s, (s + e) / 2, l, r);
    pair<int, int> r_c = find_min_max(index * 2 + 1, (s + e) / 2 + 1, e, l, r);
    if (l_c.first != -1 and r_c.first != -1) {
        int l_data = tree_data[l_c.first] <= tree_data[r_c.first] ? l_c.first : r_c.first;
        int r_data = tree_data[l_c.second] >= tree_data[r_c.second] ? l_c.second : r_c.second;
        return tree[index] = {l_data, r_data};
    } else {
        if (l_c.first == -1)
            return r_c;
        else
            return l_c;
    }
}

pair<int, int> tree_init(int index, int s, int e) {
    if (s == e) {
        data_index[s] = index;
        return tree[index] = {s, s};
    }

    pair<int, int> l_c = tree_init(index * 2, s, (s + e) / 2);
    pair<int, int> r_c = tree_init(index * 2 + 1, (s + e) / 2 + 1, e);
    int l = tree_data[l_c.first] <= tree_data[r_c.first] ? l_c.first : r_c.first;
    int r = tree_data[l_c.second] >= tree_data[r_c.second] ? l_c.second : r_c.second;
    return tree[index] = {l, r};
}

void init() {
    cin >> n >> m;
    tree = vector<pair<int, int>>(n * 4, {0, 0});
    tree_data = vector<int>(n, 0);
    data_index = vector<int>(n, 0);
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
        cout << tree_data[ans.first] << ' ' << tree_data[ans.second] << '\n';
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
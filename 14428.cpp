#include <iostream>
#include <vector>

using namespace std;
vector<int> tree_data, tree, data_index;
int n, m;

int query(int index, int s, int e, int l, int r) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[index];
    int left_query = query(index * 2, s, (s + e) / 2, l, r);
    int right_query = query(index * 2 + 1, (s + e) / 2 + 1, e, l, r);

    if (!left_query)
        return right_query;
    else if (!right_query)
        return left_query;
    else {
        int l_data = tree_data[left_query];
        int r_data = tree_data[right_query];
        return l_data <= r_data ? left_query : right_query;
    }
}

void change_data(int index, int num) {
    int cur_index = data_index[index] / 2;
    tree_data[index] = num;
    int l_child, r_child;
    while (cur_index) {
        l_child = tree[cur_index * 2];
        r_child = tree[cur_index * 2 + 1];
        int l_data = tree_data[l_child];
        int r_data = tree_data[r_child];
        tree[cur_index] = l_data <= r_data ? l_child : r_child;
        cur_index /= 2;
    }
}

int tree_init(int index, int s, int e) {
    if (s == e) {
        data_index[s] = index;
        return tree[index] = s;
    }
    int l_child = tree_init(index * 2, s, (s + e) / 2);
    int r_child = tree_init(index * 2 + 1, (s + e) / 2 + 1, e);
    int l_data = tree_data[l_child];
    int r_data = tree_data[r_child];
    return tree[index] = l_data <= r_data ? l_child : r_child;
}

void init() {
    cin >> n;
    tree = vector<int>(n * 4, 0);
    tree_data = vector<int>(n, 0);
    data_index = vector<int>(n, 0);
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];
    tree_init(1, 0, n - 1);
    cin >> m;
}

void solve() {
    int s, e, t;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> t;
        if (s == 1)
            change_data(e - 1, t);
        else
            cout << query(1, 0, n - 1, e - 1, t - 1) + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}
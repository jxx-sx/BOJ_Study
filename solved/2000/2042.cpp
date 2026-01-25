#include <iostream>
#include <vector>

using namespace std;
vector<long long> data_set, segment_tree;
vector<int> index_v;
int n, m, k;

long long sum(int index, int s, int e, int l, int r) {
    if (s > r or e < l)
        return 0;
    if (l <= s and e <= r)
        return segment_tree[index];
    return sum(index * 2, s, (s + e) / 2, l, r) + sum(index * 2 + 1, (s + e) / 2 + 1, e, l, r);
}

void update(int data_index, long long change_data) {
    int tree_index = index_v[data_index];
    long long diff = change_data - data_set[data_index];
    data_set[data_index] = change_data;
    while (tree_index) {
        segment_tree[tree_index] += diff;
        tree_index /= 2;
    }
}

long long init_tree(int index, int s, int e) {
    if (s == e) {
        index_v[s] = index;
        return segment_tree[index] = data_set[s];
    }
    return segment_tree[index] = init_tree(index * 2, s, (s + e) / 2) + init_tree(index * 2 + 1, (s + e) / 2 + 1, e);
}

void init() {
    cin >> n >> m >> k;
    data_set = vector<long long>(n, 0);
    index_v = vector<int>(n, 0);
    segment_tree = vector<long long>(4 * n, 0);
    for (int i = 0; i < n; i++)
        cin >> data_set[i];
    init_tree(1, 0, n - 1);
}

void solve() {
    long long a, b, c;
    for (int i = 0; i < m + k; i++) {
        cin >> a >> b >> c;
        if (a == 1)
            update(b - 1, c);
        else
            cout << sum(1, 0, n - 1, b - 1, c - 1) << '\n';
    }
}

int main() {
    init();
    solve();
}
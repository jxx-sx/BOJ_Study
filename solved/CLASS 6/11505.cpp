#include <iostream>
#include <vector>

using namespace std;
vector<int> tree, tree_data, data_index;
int n, m, k;

long long mul(int index, int s, int e, int l, int r) {
    if (e < l or r < s)
        return -1;
    if (l <= s and e <= r)
        return tree[index];
    long long l_child = mul(index * 2, s, (s + e) / 2, l, r);
    long long r_child = mul(index * 2 + 1, (s + e) / 2 + 1, e, l, r);
    if (l_child == -1)
        return r_child;
    if (r_child == -1)
        return l_child;
    return l_child * r_child % 1000000007;
}

void change_data(int index, int new_data) {
    tree[data_index[index]] = new_data;
    int cur_index = data_index[index] / 2;
    while (cur_index) {
        tree[cur_index] = (long long)tree[cur_index * 2] * (long long)tree[cur_index * 2 + 1] % 1000000007;
        cur_index /= 2;
    }

    return;
}

long long tree_init(int index, int s, int e) {
    if (s == e) {
        data_index[s] = index;
        return tree[index] = tree_data[s];
    }
    long long l = tree_init(index * 2, s, (s + e) / 2);
    long long r = tree_init(index * 2 + 1, (s + e) / 2 + 1, e);
    return tree[index] = l * r % 1000000007;
}

void init() {
    cin >> n >> m >> k;
    tree = vector<int>(4 * n, 0);
    tree_data = vector<int>(n, 0);
    data_index = vector<int>(n, 0);
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];
    tree_init(1, 0, n - 1);

    return;
}

void solve() {
    int a, b, c;
    for (int i = 0; i < m + k; i++) {
        cin >> a >> b >> c;
        if (a == 1) {
            change_data(b - 1, c);
        } else {
            cout << mul(1, 0, n - 1, b - 1, c - 1) << '\n';
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
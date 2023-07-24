#include <iostream>

using namespace std;

int tree[400000];
int arr[100000];
int ans[100000];
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i] = 1;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = e - s + 1;
}

int query(int d, int s, int e, int i) {
    if (s == e)
        return s;
    if (tree[i << 1] < d)
        return query(d - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
    return query(d, s, (s + e) / 2, i << 1);
}

void update(int k, int s, int e, int i) {
    tree[i]--;
    if (s == e)
        return;
    if (k > (s + e) / 2)
        update(k, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, s, (s + e) / 2, i << 1);
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    tree_init(1, n, 1);
}

void solve() {
    for (int i = n - 1; i >= 0; i--) {
        int q = query(i + 1 - arr[i], 1, n, 1);
        ans[q - 1] = i + 1;
        update(q, 1, n, 1);
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
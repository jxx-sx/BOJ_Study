#include <iostream>

using namespace std;
struct seg {
    int tree[65537 << 2];

    void update(int k, int d, int s = 0, int e = 65536, int i = 1) {
        tree[i] += d;
        if (s == e)
            return;
        if ((s + e) / 2 < k)
            update(k, d, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, d, s, (s + e) / 2, i << 1);
    }

    int get(int k, int s = 0, int e = 65536, int i = 1) {
        if (s == e)
            return s;
        if (k > tree[i << 1])
            return get(k - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
        else
            return get(k, s, (s + e) / 2, i << 1);
    }
} tree;

int arr[250000], k, n;

void init() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void solve() {
    for (int i = 0; i < k; i++)
        tree.update(arr[i], 1);
    long long ans = tree.get((k + 1) / 2);

    for (int i = k; i < n; i++) {
        tree.update(arr[i], 1);
        tree.update(arr[i - k], -1);
        ans += tree.get((k + 1) / 2);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
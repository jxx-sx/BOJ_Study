#include <iostream>

using namespace std;

int ans[100001];
int n;

struct seg {
    int tree[400000];

    int get(int k, int s, int e, int i) {
        tree[i]--;
        if (s == e)
            return s;
        if (tree[i << 1] < k)
            return get(k - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
        else
            return get(k, s, (s + e) / 2, i << 1);
    }

    void init(int s, int e, int i) {
        tree[i] = e - s + 1;
        if (s == e)
            return;

        init(s, (s + e) / 2, i << 1);
        init((s + e) / 2 + 1, e, i << 1 | 1);
    }

} tree;

void init() {
    cin >> n;
    tree.init(1, n, 1);
}

void solve() {
    int k;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        ans[tree.get(k + 1, 1, n, 1)] = i;
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
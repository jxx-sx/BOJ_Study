#include <iostream>

using namespace std;

int tree[800000];
int ind[200001];
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        ind[s] = i;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
    return;
}

int query(int k, int s, int e, int i) {
    if (s == e)
        return s;
    if (k > tree[i << 1])
        return query(k - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
    else
        return query(k, s, (s + e) / 2, i << 1);
}

void update(int k) {
    int diff = tree[ind[k]];
    int cur = ind[k];
    while (cur) {
        tree[cur] -= diff;
        cur >>= 1;
    }
}

void init() {
    cin >> n;
    tree_init(1, n, 1);
    return;
}

void solve() {
    int p;
    for (int i = 0; i < n; i++) {
        cin >> p;
        int q = query(p, 1, n, 1);
        update(q);
        cout << q << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
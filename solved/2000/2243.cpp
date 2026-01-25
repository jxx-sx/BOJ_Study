#include <iostream>
#define MAX_SIZE 1000000

using namespace std;

int tree[MAX_SIZE * 4];
int tree_index[MAX_SIZE + 1];
int n;

void tree_init(int s, int e, int i) {
    if (s == e)
        tree_index[s] = i;
    else {
        tree_init(s, (s + e) / 2, i << 1);
        tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
    }
}

void tree_update(int i, int diff) {
    tree[tree_index[i]] += diff;
    int cur = tree_index[i];
    while (cur >>= 1 > 0)
        tree[cur] = tree[cur << 1] + tree[(cur << 1) | 1];
}

int tree_find(int s, int e, int i, int c) {
    if (s == e)
        return s;
    if (tree[i << 1] < c)
        return tree_find((s + e) / 2 + 1, e, (i << 1) | 1, c - tree[i << 1]);
    return tree_find(s, (s + e) / 2, i << 1, c);
}

void init() {
    cin >> n;
    tree_init(1, MAX_SIZE, 1);
}

void solve() {
    int a, b, c;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (a == 1) {
            cin >> b;
            int ans = tree_find(1, MAX_SIZE, 1, b);
            cout << ans << '\n';
            tree_update(ans, -1);
        } else {
            cin >> b >> c;
            tree_update(b, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}
#include <iostream>
#define MAX 199999
#define MOD 1000000007
using namespace std;
typedef pair<long long, long long> Node;
Node tree[800000]; // sum of distance from 0,cnt
int tree_index[200000];
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree_index[s] = i;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void new_tree(int i) {
    int cur = tree_index[i];
    while (cur > 0) {
        tree[cur].second++;
        tree[cur].first += i;
        cur >>= 1;
    }
}

Node tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return {0, 0};
    if (l <= s and e <= r)
        return tree[i];
    Node l_c = tree_find(l, r, s, (s + e) / 2, i << 1);
    Node r_c = tree_find(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    return {l_c.first + r_c.first, l_c.second + r_c.second};
}

void init() {
    tree_init(0, MAX, 1);
    return;
}

void solve() {
    int inp;
    unsigned long long ans = 1;
    cin >> n;
    cin >> inp;
    new_tree(inp);
    for (int i = 1; i < n; i++) {
        cin >> inp;
        new_tree(inp);
        Node l = tree_find(0, inp, 0, MAX, 1);
        Node r = tree_find(inp, MAX, 0, MAX, 1);
        ans *= ((l.second * inp - l.first) + (r.first - r.second * inp)) % MOD;
        ans %= MOD;
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
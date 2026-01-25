#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define N 1000000

using namespace std;

struct Node {
    int mx, smx, cnt;
    long long sum;

    Node operator+(const Node &t) const {
        if (mx == t.mx)
            return Node(mx, max(smx, t.smx), cnt + t.cnt, sum + t.sum);
        if (mx > t.mx)
            return Node(mx, max(smx, t.mx), cnt, sum + t.sum);
        return Node(t.mx, max(mx, t.smx), t.cnt, sum + t.sum);
    }

    Node(int mx = 0, int smx = -1, int cnt = 1, long long sum = 0) : mx(mx), smx(smx), cnt(cnt), sum(sum) {}
} node[N << 2];

void push(int i) {
    for (auto a : {i << 1, i << 1 | 1}) {
        if (node[i].mx >= node[a].mx)
            continue;
        node[a].sum -= (long long)(node[a].mx - node[i].mx) * node[a].cnt;
        node[a].mx = node[i].mx;
    }
}

void tree_init(int s, int e, int i = 1) {
    if (s == e) {
        cin >> node[i].mx;
        node[i].sum = node[i].mx;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    node[i] = node[i << 1] + node[i << 1 | 1];
}

void update(int l, int r, int x, int s, int e, int i = 1) {
    if (e < l or r < s or x >= node[i].mx)
        return;
    if (l <= s and e <= r and x > node[i].smx) {
        node[i].sum -= (long long)(node[i].mx - x) * node[i].cnt;
        node[i].mx = x;
        return;
    }
    push(i);
    update(l, r, x, s, (s + e) / 2, i << 1);
    update(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    node[i] = node[i << 1] + node[i << 1 | 1];
}

int mx(int l, int r, int s, int e, int i = 1) {
    if (e < l or r < s)
        return -1;
    if (l <= s and e <= r)
        return node[i].mx;
    push(i);
    return max(mx(l, r, s, (s + e) / 2, i << 1), mx(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

long long sum(int l, int r, int s, int e, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return node[i].sum;
    push(i);
    return sum(l, r, s, (s + e) / 2, i << 1) + sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

int n, m;

void init() {
    cin >> n;
    tree_init(1, n);
    cin >> m;
}

void solve() {
    int op, l, r, x;
    while (m--) {
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            update(l, r, x, 1, n);
        }
        if (op == 2)
            cout << mx(l, r, 1, n) << '\n';
        if (op == 3)
            cout << sum(l, r, 1, n) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
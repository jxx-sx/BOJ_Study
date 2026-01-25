#include <iostream>
#define MOD 1000000007

using namespace std;
struct Lazy {
    long long m;
    long long a;
    long long c;
    bool check;

    Lazy() {
        m = 1;
        a = c = 0;
        check = false;
    }

    Lazy(int v) {
        m = 1;
        a = 0;
        c = v;
        check = true;
    }
} lazy[400000];
long long tree[400000];
int n;

void update(int s, int e, int x) {
    if (lazy[x].check) {
        tree[x << 1 | 1] = tree[x << 1] = (lazy[x].c * lazy[x].m + lazy[x].a) % MOD;
        tree[x << 1] = tree[x << 1] * ((s + e) / 2 - s + 1) % MOD;
        tree[x << 1 | 1] = tree[x << 1 | 1] * (e - (s + e) / 2) % MOD;
    } else if (lazy[x].m != 1 or lazy[x].a != 0) {
        tree[x << 1] = tree[x << 1] * lazy[x].m % MOD;
        tree[x << 1] = (tree[x << 1] + lazy[x].a * ((s + e) / 2 - s + 1)) % MOD;
        tree[x << 1 | 1] = tree[x << 1 | 1] * lazy[x].m % MOD;
        tree[x << 1 | 1] = (tree[x << 1 | 1] + lazy[x].a * (e - (s + e) / 2)) % MOD;
    }
}

void push_down(int s, int e, int x) {
    if (lazy[x].check) {
        lazy[x << 1] = lazy[x << 1 | 1] = lazy[x];
    } else {
        lazy[x << 1].m = lazy[x << 1].m * lazy[x].m % MOD;
        lazy[x << 1].a = (lazy[x].m * lazy[x << 1].a + lazy[x].a) % MOD;
        lazy[x << 1 | 1].m = lazy[x << 1 | 1].m * lazy[x].m % MOD;
        lazy[x << 1 | 1].a = (lazy[x].m * lazy[x << 1 | 1].a + lazy[x].a) % MOD;
    }
    update(s, e, x);
    lazy[x] = Lazy();
}

void add(int l, int r, long long k, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] = (tree[i] + k * (e - s + 1)) % MOD;
        lazy[i].a = (lazy[i].a + k) % MOD;
        return;
    }
    push_down(s, e, i);

    add(l, r, k, s, (s + e) / 2, i << 1);
    add(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % MOD;
}

void multiple(int l, int r, long long k, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] = tree[i] * k % MOD;
        lazy[i].m = lazy[i].m * k % MOD;
        lazy[i].a = lazy[i].a * k % MOD;
        return;
    }
    push_down(s, e, i);

    multiple(l, r, k, s, (s + e) / 2, i << 1);
    multiple(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % MOD;
}

void change(int l, int r, long long k, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] = k * (e - s + 1) % MOD;
        lazy[i] = Lazy(k);
        return;
    }
    push_down(s, e, i);

    change(l, r, k, s, (s + e) / 2, i << 1);
    change(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % MOD;
}

long long query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    push_down(s, e, i);

    return (query(l, r, s, (s + e) / 2, i << 1) + query(l, r, (s + e) / 2 + 1, e, i << 1 | 1)) % MOD;
}

void tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % MOD;
    return;
}

void init() {
    cin >> n;
    tree_init(1, n, 1);
}

void solve() {
    int m, q, x, y, v;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q;
        if (q == 1) {
            cin >> x >> y >> v;
            add(x, y, v, 1, n, 1);
        }
        if (q == 2) {
            cin >> x >> y >> v;
            multiple(x, y, v, 1, n, 1);
        }
        if (q == 3) {
            cin >> x >> y >> v;
            change(x, y, v, 1, n, 1);
        }
        if (q == 4) {
            cin >> x >> y;
            cout << query(x, y, 1, n, 1) << '\n';
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
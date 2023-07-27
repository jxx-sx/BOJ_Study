#include <iostream>
#include <vector>
#define pb push_back
#define N 500001
#define Mod 4294967296

using namespace std;

vector<int> e[N], c[N];
bool chk[N];
int sz[N], in[N], out[N], p[N], top[N], dep[N];
int n, q, ord;
unsigned long long tree[N << 2];
struct Lazy {
    unsigned long long d;
    unsigned long long m;
    Lazy() : d(0), m(1) {}
    void mod() {
        d = d % Mod;
        m = m % Mod;
    }
} lazy[N << 2];

void push_down(int i) {
    lazy[i << 1].m *= lazy[i].m;
    lazy[i << 1].d *= lazy[i].m;
    lazy[i << 1].d += lazy[i].d;
    lazy[i << 1].mod();

    lazy[i << 1 | 1].m *= lazy[i].m;
    lazy[i << 1 | 1].d *= lazy[i].m;
    lazy[i << 1 | 1].d += lazy[i].d;
    lazy[i << 1 | 1].mod();
}

void propagate(int s, int e, int i) {
    if (lazy[i].d == 0 and lazy[i].m == 1)
        return;
    tree[i] = tree[i] * lazy[i].m % Mod;
    tree[i] += lazy[i].d * (e - s + 1);
    tree[i] %= Mod;
    if (s != e) {
        push_down(i);
    }
    lazy[i].d = 0;
    lazy[i].m = 1;
}

void update_sum(unsigned long long d, int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] += d * (e - s + 1);
        tree[i] %= Mod;
        if (s != e) {
            lazy[i << 1].d += d;
            lazy[i << 1].d %= Mod;
            lazy[i << 1 | 1].d += d;
            lazy[i << 1 | 1].d %= Mod;
        }
        return;
    }
    update_sum(d, l, r, s, (s + e) / 2, i << 1);
    update_sum(d, l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
    tree[i] %= Mod;
}

void update_mul(unsigned long long d, int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] *= d;
        tree[i] %= Mod;
        if (s != e) {
            lazy[i << 1].m *= d;
            lazy[i << 1].d *= d;
            lazy[i << 1].mod();
            lazy[i << 1 | 1].m *= d;
            lazy[i << 1 | 1].d *= d;
            lazy[i << 1 | 1].mod();
        }
        return;
    }
    update_mul(d, l, r, s, (s + e) / 2, i << 1);
    update_mul(d, l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
    tree[i] %= Mod;
}

unsigned long long sum(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return (sum(l, r, s, (s + e) / 2, i << 1) + sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1)) % Mod;
}

void update_sum_query(int a, int b, unsigned long long d) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        update_sum(d, in[st], in[a], 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    update_sum(d, in[a], in[b], 1, n, 1);
}

void update_mul_query(int a, int b, unsigned long long d) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        update_mul(d, in[st], in[a], 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    update_mul(d, in[a], in[b], 1, n, 1);
}

unsigned long long sum_query(int a, int b) {
    unsigned long long ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret += sum(in[st], in[a], 1, n, 1);
        ret %= Mod;
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret += sum(in[a], in[b], 1, n, 1);
    ret %= Mod;
    return ret;
}

void dfs(int x) {
    chk[x] = true;
    for (auto a : e[x]) {
        if (chk[a])
            continue;
        c[x].pb(a);
        dfs(a);
    }
}

void dfs1(int x) {
    sz[x] = 1;
    for (auto &a : c[x]) {
        dep[a] = dep[x] + 1;
        p[a] = x;
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x) {
    ord++;
    in[x] = ord;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
    out[x] = ord;
}

void init() {
    int a, b;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    int op, x, y, v;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> x >> v;
            update_sum(v, in[x], out[x], 1, n, 1);
        }
        if (op == 2) {
            cin >> x >> y >> v;
            update_sum_query(x, y, v);
        }
        if (op == 3) {
            cin >> x >> v;
            update_mul(v, in[x], out[x], 1, n, 1);
        }
        if (op == 4) {
            cin >> x >> y >> v;
            update_mul_query(x, y, v);
        }
        if (op == 5) {
            cin >> x;
            cout << sum(in[x], out[x], 1, n, 1) << '\n';
        }
        if (op == 6) {
            cin >> x >> y;
            cout << sum_query(x, y) << '\n';
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
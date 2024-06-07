#include <iostream>
#include <string>
#include <vector>

#define N 100001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int tree[N << 2], lz[N << 2];
int n, q, _in, p[N], top[N], sz[N], in[N], out[N];
vector<int> c[N];

void push(int s, int e, int i) {
    if (!lz[i])
        return;
    if (lz[i] == 1) {
        tree[i << 1] = tree[i << 1 | 1] = 0;
        lz[i << 1] = lz[i << 1 | 1] = 1;
    } else {
        int m = (s + e) / 2;
        tree[i << 1] = m - s + 1;
        tree[i << 1 | 1] = e - m;
        lz[i << 1] = lz[i << 1 | 1] = 2;
    }
    lz[i] = 0;
}

// update and get
int uag(int l, int r, int d, int s = 1, int e = n, int i = 1) {
    if (e < l || r < s)
        return 0;
    if (l <= s && e <= r) {
        int ret = tree[i];
        tree[i] = d ? e - s + 1 : 0;
        lz[i] = d + 1;
        return ret;
    }
    push(s, e, i);
    int ret = uag(l, r, d, s, (s + e) / 2, i << 1) + uag(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
    return ret;
}

int install(int x) {
    int ret = 0;
    while (top[x]) {
        int a = uag(in[top[x]], in[x], 1);
        ret += in[x] - in[top[x]] + 1 - a;
        x = p[top[x]];
    }
    ret += in[x] - uag(1, in[x], 1);

    return ret;
}

int uninstall(int x) { return uag(in[x], out[x], 0); }

void dfs(int x = 0) {
    sz[x] = 1;
    for (auto &a : c[x]) {
        dfs(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs1(int x = 0) {
    in[x] = ++_in;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs1(a);
    }
    out[x] = _in;
}

void init() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        c[p[i]].pb(i);
    }
    dfs();
    dfs1();
    cin >> q;
}

void solve() {
    string op;
    int x;
    while (q--) {
        cin >> op >> x;
        cout << (op[0] == 'i' ? install(x) : uninstall(x)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
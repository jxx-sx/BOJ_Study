#include <iostream>
#include <vector>

#define N 500001
#define pb push_back
#define m ((s + e) >> 1)

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

int n, q, _in;
int arr[N], sz[N], dep[N], p[N], top[N], in[N];
ll tree[N << 2], lz[N << 2];
ll ans;
vector<int> c[N];

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto &a : c[x]) {
        dep[a] = dep[x] + 1;
        dfs(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs1(int x = 1) {
    in[x] = ++_in;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs1(a);
    }
}

inline void push(int s, int e, int i) {
    if (!lz[i])
        return;
    tree[i << 1] += (ll)(m - s + 1) * lz[i];
    tree[i << 1 | 1] += (ll)(e - m) * lz[i];
    lz[i << 1] += lz[i];
    lz[i << 1 | 1] += lz[i];
    lz[i] = 0;
}

// get and update
ll gau(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l || r < s)
        return 0;
    if (l <= s && e <= r) {
        ll ret = tree[i];
        tree[i] += e - s + 1;
        lz[i]++;
        return ret;
    }
    push(s, e, i);
    ll ret = gau(l, r, s, m, i << 1) + gau(l, r, m + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
    return ret;
}

// update and get
ll uag(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l || r < s)
        return 0;
    if (l <= s && e <= r) {
        tree[i] -= e - s + 1;
        lz[i]--;
        return tree[i];
    }
    push(s, e, i);
    ll ret = uag(l, r, s, m, i << 1) + uag(l, r, m + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
    return ret;
}

void update(int x) {
    int v = x;
    while (top[v]) {
        if (arr[x])
            ans += gau(in[top[v]], in[v]);
        else
            ans -= uag(in[top[v]], in[v]);
        v = p[top[v]];
    }
    if (arr[x])
        ans += gau(2, in[v]);
    else
        ans -= uag(2, in[v]);
}

inline void query(int x) {
    arr[x] ^= 1;
    update(x);
}

void init() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        c[p[i]].pb(i);
    }
}

void solve() {
    int x;
    dfs();
    dfs1();
    for (int i = 1; i <= n; i++) {
        if (!arr[i])
            continue;
        update(i);
    }
    cout << ans << '\n';
    while (q--) {
        cin >> x;
        query(x);
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
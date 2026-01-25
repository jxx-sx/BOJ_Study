#include <cassert>
#include <iostream>
#include <set>
#include <vector>

#define N 100001
#define pb push_back
#define BLACK 0
#define WHITE 1

using namespace std;

int dp[2][N], n, m, _in, top[N], sz[N], in[N], p[N], arr[N], rev[N];
set<int> s[2][N];
vector<int> e[N], c[N];

void dp_p_update(int color, int x, int d) {
    while (x <= n) {
        dp[color][x] += d;
        x += (x & -x);
    }
}

void dp_update(int color, int l, int r, int d) {
    dp_p_update(color, l, d);
    dp_p_update(color, r + 1, -d);
}

int dp_get(int color, int x) {
    int ret = 0;
    while (x) {
        ret += dp[color][x];
        x -= (x & -x);
    }
    return ret;
}

int g(int color, int x) {
    while (top[x]) {
        auto lb = s[1 - color][top[x]].lower_bound(-in[x]);
        if (lb != s[1 - color][top[x]].end())
            return -(*lb) + 1;
        if (arr[p[top[x]]] != color)
            return in[top[x]];
        x = p[top[x]];
    }
    auto lb = s[1 - color][0].lower_bound(-in[x]);
    if (lb != s[1 - color][0].end())
        return -(*lb) + 1;
    return 1;
}

void range_update(int color, int x, int d) {
    int tp = max(p[rev[g(color, x)]], 1);
    while (top[tp] != top[x]) {
        dp_update(color, in[top[x]], in[x], d);
        x = p[top[x]];
    }
    dp_update(color, in[tp], in[x], d);
}

void update(int x) {
    arr[x] = 1 - arr[x];
    if (arr[x] == BLACK) { // W->B
        s[WHITE][top[x]].erase(-in[x]);
        s[BLACK][top[x]].insert(-in[x]);
    } else { // B->W
        s[BLACK][top[x]].erase(-in[x]);
        s[WHITE][top[x]].insert(-in[x]);
    }
    if (x == 1)
        return;
    if (arr[x] == BLACK) { // W->B
        if (arr[p[x]] == BLACK) {
            range_update(BLACK, p[x], dp_get(BLACK, in[x]));
            dp_update(WHITE, in[p[x]], in[p[x]], -dp_get(WHITE, in[x]));
        } else {
            range_update(WHITE, p[x], -dp_get(WHITE, in[x]));
            dp_update(BLACK, in[p[x]], in[p[x]], dp_get(BLACK, in[x]));
        }
    } else { // B->W
        if (arr[p[x]] == BLACK) {
            range_update(BLACK, p[x], -dp_get(BLACK, in[x]));
            dp_update(WHITE, in[p[x]], in[p[x]], dp_get(WHITE, in[x]));
        } else {
            range_update(WHITE, p[x], dp_get(WHITE, in[x]));
            dp_update(BLACK, in[p[x]], in[p[x]], -dp_get(BLACK, in[x]));
        }
    }
}

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        c[x].pb(a);
        p[a] = x;
        dfs(a);
    }
}

void dfs1(int x = 1) {
    for (auto &a : c[x]) {
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x = 1) {
    in[x] = ++_in;
    rev[in[x]] = x;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void init() {
    int u, v;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs();
    dfs1();
    dfs2();
    cin >> m;
    for (int i = 1; i <= n; i++) {
        dp_update(BLACK, in[i], in[i], sz[i]);
        s[BLACK][top[i]].insert(-in[i]);
    }
    dp_update(WHITE, 1, n, 1);
}

void solve() {
    int op, x;
    while (m--) {
        cin >> op >> x;
        if (op == 1)
            update(x);
        else
            cout << dp_get(arr[x], g(arr[x], x)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
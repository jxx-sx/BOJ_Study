#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#define N 100001
#define pb push_back

using namespace std;

struct Node {
    long long d, a, b;
    Node() : d(0), a(0), b(0) {}
} tree[N << 2];
int n, q, ord, sz[N], top[N], p[N], dep[N], in[N];
vector<int> c[N], e[N];
stack<pair<int, int>> s;

void dfs(int x) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        c[x].pb(a);
        dfs(a);
    }
}

void dfs1(int x) {
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
    in[x] = ++ord;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void push(int s, int e, int i) {
    if (tree[i].a or tree[i].b) {
        int m = (s + e) >> 1;
        tree[i << 1].d += tree[i].a;
        tree[i << 1 | 1].d += tree[i].a + tree[i].b * (m - s + 1);
        tree[i << 1].a += tree[i].a;
        tree[i << 1].b += tree[i].b;
        tree[i << 1 | 1].a += tree[i].a + tree[i].b * (m - s + 1);
        tree[i << 1 | 1].b += tree[i].b;
        tree[i].a = tree[i].b = 0;
    }
}

int update(int l, int r, int a, int b, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r) {
        tree[i].d += a;
        tree[i].a += a;
        tree[i].b += b;
        return e - s + 1;
    }
    push(s, e, i);
    int ret = 0;
    int m = (s + e) / 2;
    ret = update(l, r, a, b, s, m, i << 1);
    ret += update(l, r, a + ret * b, b, m + 1, e, i << 1 | 1);
    return ret;
}

long long get(int k, int s, int e, int i) {
    if (s == e)
        return tree[i].d;
    push(s, e, i);
    if (k > (s + e) / 2)
        return get(k, (s + e) / 2 + 1, e, i << 1 | 1);
    return get(k, s, (s + e) / 2, i << 1);
}

void query(int a, int b) {
    int cur_a = 0;
    bool immediate = true;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) {
            swap(a, b);
            immediate = !immediate;
        }
        int st = top[a];
        if (immediate) {
            cur_a += in[a] - in[st];
            update(in[st], in[a], cur_a, -1, 1, n, 1);
            cur_a++;
        } else
            s.push({in[st], in[a]});
        a = p[st];
    }

    if (dep[a] > dep[b]) {
        swap(a, b);
        immediate = !immediate;
    }
    if (!immediate) {
        cur_a += in[b] - in[a];
        update(in[a], in[b], cur_a, -1, 1, n, 1);
        cur_a++;
    } else
        s.push({in[a], in[b]});

    while (s.size()) {
        update(s.top().first, s.top().second, cur_a, 1, 1, n, 1);
        cur_a += s.top().second - s.top().first + 1;
        s.pop();
    }
}

ifstream f("hld_tle.in");
void init() {

    int a, b;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    cin >> q;

    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    int op, a, b;
    while (q--) {
        cin >> op >> a;
        if (op == 1) {
            cin >> b;
            query(a, b);
        } else
            cout << get(in[a], 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
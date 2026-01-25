#include <iostream>
#include <string>
#include <vector>
#define pb push_back
#define N 30001
#define M 300000

using namespace std;

struct Query {
    string s;
    int a, b;
    bool ans;
} q[M];

int w[N], sz[N], top[N], dep[N], p[N], in[N], r[N], tree[N];
int n, m, ord;
vector<int> e[N], c[N];

void update(int i, int d) {
    while (i <= n) {
        tree[i] += d;
        i += i & -i;
    }
}

int sum(int i) {
    int ret = 0;
    while (i) {
        ret += tree[i];
        i -= i & -i;
    }
    return ret;
}

int query(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret += sum(in[a]) - sum(in[st] - 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret += sum(in[b]) - sum(in[a] - 1);
    return ret;
}

int find_root(int x) {
    if (x == r[x])
        return x;
    return r[x] = find_root(r[x]);
}

bool union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a != b) {
        r[a] = b;
        return true;
    }
    return false;
}

void dfs(int x) {
    sz[x] = -1;
    for (auto a : e[x]) {
        if (sz[a] != 0)
            continue;
        c[x].push_back(a);
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
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        r[i] = i;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].a >> q[i].b;
        if (q[i].s[0] == 'b') {
            q[i].ans = union_root(q[i].a, q[i].b);
            if (q[i].ans) {
                e[q[i].a].pb(q[i].b);
                e[q[i].b].pb(q[i].a);
            }
        }
        if (q[i].s[0] == 'e') {
            q[i].ans = find_root(q[i].a) == find_root(q[i].b);
        }
    }
    dfs(1);
    for (int i = 2; i <= n; i++) {
        if (sz[i] != 0)
            continue;
        int a = find_root(i);
        int b = find_root(1);
        if (a == b)
            continue;
        r[a] = b;
        c[b].pb(a);
        dfs(a);
    }
    dfs1(1);
    dfs2(1);

    for (int i = 1; i <= n; i++)
        update(in[i], w[i]);
}

void solve() {
    for (int i = 0; i < m; i++) {
        if (q[i].s[0] == 'b')
            cout << (q[i].ans ? "yes\n" : "no\n");
        if (q[i].s[0] == 'p') {
            update(in[q[i].a], q[i].b - w[q[i].a]);
            w[q[i].a] = q[i].b;
        }
        if (q[i].s[0] == 'e') {
            if (q[i].ans)
                cout << query(q[i].a, q[i].b) << '\n';
            else
                cout << "impossible\n";
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
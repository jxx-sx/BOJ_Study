#include <iostream>
#include <vector>

#define N 200001
#define pb push_back

using namespace std;

int in[N], dep[N], out[N];
int ord;
int n, c, q;
vector<int> e[N];
struct Fenwick {
    int tree[N];
    void update(int x) {
        while (x <= n) {
            tree[x]++;
            x += x & -x;
        }
    }

    int sum(int x) {
        int ret = 0;
        while (x) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }

    int get(int x) { return sum(out[x]) - sum(in[x] - 1); }
} tree;

void dfs(int x) {
    in[x] = ++ord;
    for (auto a : e[x]) {
        if (in[a])
            continue;
        dep[a] = dep[x] + 1;
        dfs(a);
    }
    out[x] = ord;
}

void init() {
    int a, b;
    cin >> n >> c;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    cin >> q;
}

void solve() {
    dep[c] = 1;
    dfs(c);
    int op, a;
    while (q--) {
        cin >> op >> a;
        if (op == 1)
            tree.update(in[a]);
        else
            cout << (long long)dep[a] * tree.get(a) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
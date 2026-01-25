#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define N 100001
#define pb push_back

#define LEFT -1
#define NONE 0
#define RIGHT 1
#define FIND 2

using namespace std;

struct Node {
    int l, r, flag;

    Node() : l(0), r(0), flag(NONE) {}
    Node(int l, int r, int flag) : l(l), r(r), flag(flag) {}

    bool operator<(const Node &t) const {
        if (l == t.l)
            return r < t.r;
        return l < t.l;
    }
};

int n, q, ord;
int p[N], in[N], out[N];
vector<int> e[N];
vector<Node> nodes;

struct Seg {
    int tree[N << 2];
    int cnt[N << 2];

    void update(int l, int r, int s, int e, int i, int d) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r)
            tree[i] += d;
        else {
            update(l, r, s, (s + e) / 2, i << 1, d);
            update(l, r, (s + e) / 2 + 1, e, i << 1 | 1, d);
        }

        if (tree[i] > 0)
            cnt[i] = e - s + 1;
        else if (e - s)
            cnt[i] = cnt[i << 1] + cnt[i << 1 | 1];
        else
            cnt[i] = 0;
    }

    int get() { return n - cnt[1]; }
} tree;

bool check(Node x) { return x.flag == LEFT ? p[x.l] == x.r : p[x.r] == x.l; }

void dfs(int x = 1) {
    in[x] = ++ord;
    for (auto a : e[x]) {
        if (in[a])
            continue;
        p[a] = x;
        dfs(a);
    }
    out[x] = ord;
}

void init() {
    string st;
    cin >> n;
    nodes.resize(n - 1);
    for (auto &a : nodes) {
        cin >> a.l >> st >> a.r;
        e[a.l].pb(a.r);
        e[a.r].pb(a.l);
        a.flag = st != "->" ? st == "<-" ? LEFT : NONE : RIGHT;
        if (a.l > a.r) {
            swap(a.l, a.r);
            a.flag *= -1;
        }
    }
    cin >> q;
}

void update(Node a, int d) {
    if (a.flag == NONE)
        return;
    int x = p[a.l] == a.r ? a.l : a.r;
    if (check(a))
        tree.update(in[x], out[x], 1, n, 1, d);
    else {
        tree.update(1, in[x] - 1, 1, n, 1, d);
        tree.update(out[x] + 1, n, 1, n, 1, d);
    }
}

void tree_init() {
    for (auto a : nodes) {
        update(a, 1);
    }
}

void solve() {
    dfs();
    tree_init();
    sort(nodes.begin(), nodes.end());
    int a, b;
    string st;
    while (q--) {
        cin >> a >> st >> b;
        int flag = st != "->" ? st == "<-" ? LEFT : NONE : RIGHT;
        if (a > b) {
            swap(a, b);
            flag *= -1;
        }
        auto node = lower_bound(nodes.begin(), nodes.end(), Node(a, b, FIND));
        if (flag != node->flag) {
            update(*node, -1);
            node->flag = flag;
            update(*node, 1);
        }

        cout << tree.get() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
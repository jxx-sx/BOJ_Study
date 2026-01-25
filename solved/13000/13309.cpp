#include <iostream>
#include <vector>

using namespace std;

int sz[200001];
int dep[200001];
int p[200001];
int top[200001];
int in[200001];
int tree[200001];
int arr[200001];
int n, m;
int ord;
vector<int> edges[200001];

void update(int x) {
    if (arr[x]) {
        arr[x] = 0;
        while (x <= n) {
            tree[x]--;
            x += x & -x;
        }
    }
}

int sum(int x) {
    int rtn = 0;
    while (x) {
        rtn += tree[x];
        x -= x & -x;
    }
    return rtn;
}

void dfs1(int x) {
    sz[x] = 1;
    for (auto &a : edges[x]) {
        dep[a] = dep[x] + 1;
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[edges[x][0]])
            swap(a, edges[x][0]);
    }
}

void dfs2(int x) {
    ord++;
    in[x] = ord;
    for (auto a : edges[x]) {
        top[a] = a == edges[x][0] ? top[x] : a;
        dfs2(a);
    }
}

bool query(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        if ((sum(in[a]) - sum(in[st] - 1)) != (in[a] - in[st] + 1))
            return false;
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    if (sum(in[a]) - sum(in[b]) != in[a] - in[b])
        return false;
    return true;
}

void init() {
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        edges[p[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        tree[i] = i & -i;
        arr[i] = 1;
    }
    dfs1(1);
    dfs2(1);
}

void solve() {
    int b, c, d;
    bool cur;
    while (m--) {
        cin >> b >> c >> d;
        cur = query(b, c);
        cout << (cur ? "YES\n" : "NO\n");
        if (d)
            update(cur ? in[b] : in[c]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
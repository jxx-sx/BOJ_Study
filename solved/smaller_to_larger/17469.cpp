#include <iostream>
#include <set>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Query {
    int x, a, ans;
} query[1100001];

struct UnionFind {
    int p[100001];
    set<int> s[100001];

    int find_root(int x) {
        if (p[x] == x)
            return x;
        return p[x] = find_root(p[x]);
    }

    void union_root(int a, int b) {
        a = find_root(a);
        b = find_root(b);

        if (s[a].size() < s[b].size()) {
            p[a] = b;
            s[b].merge(s[a]);
        } else {
            p[b] = a;
            s[a].merge(s[b]);
        }
    }

    void init() {
        for (int i = 1; i < 100001; i++)
            p[i] = i;
    }

} uf;

int n, q;
int p[100001];

void init() {
    cin >> n >> q;
    for (int i = 2; i <= n; i++)
        cin >> p[i];
    int tmp;
    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        uf.s[i].insert(tmp);
    }
    for (int i = 0; i < n + q - 1; i++)
        cin >> query[i].x >> query[i].a;
    uf.init();
}

void solve() {
    for (int i = n + q - 2; i >= 0; i--) {
        if (query[i].x == 1)
            uf.union_root(query[i].a, p[query[i].a]);
        else
            query[i].ans = uf.s[uf.find_root(query[i].a)].size();
    }
    for (int i = 0; i < n + q - 1; i++)
        if (query[i].x == 2)
            cout << query[i].ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
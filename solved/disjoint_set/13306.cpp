#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Query {
    int x, a, b;
    bool ans;
} query[400001];

int arr[200001];
int p[200001];
int query_p[200001];
int n, q;
int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);

    p[a] = b;
}

void init() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 2; i <= n; i++)
        cin >> query_p[i];
    for (int i = 0; i < n + q - 1; i++) {
        cin >> query[i].x >> query[i].a;
        if (query[i].x)
            cin >> query[i].b;
    }
}

void solve() {
    for (int i = n + q - 1; i >= 0; i--) {
        if (query[i].x)
            query[i].ans = find_root(query[i].a) == find_root(query[i].b);
        else
            union_root(query[i].a, query_p[query[i].a]);
    }
    for (int i = 0; i < n + q - 1; i++)
        cout << (query[i].x ? query[i].ans ? "YES\n" : "NO\n" : "");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
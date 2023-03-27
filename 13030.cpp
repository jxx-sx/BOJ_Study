#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;

int n, q;
int p[300001];
vector<int> child[300001];
pair<int, int> lazy[300001]; // x, k
int tree[300001];

void propagate(int x) {
    tree[x] += lazy[x].first;
    tree[x] %= MOD;
    for (auto a : child[x]) {
        lazy[a].first += lazy[x].first;
        lazy[a].first -= lazy[x].second;
        lazy[a].first %= MOD;
        lazy[a].second += lazy[x].second;
        lazy[a].second %= MOD;
    }
    lazy[x] = {0, 0};
}

void update(int x) {
    if (p[x])
        update(p[x]);
    propagate(x);
}

void query(int v, int x, int k) {
    lazy[v].first += x;
    lazy[v].first %= MOD;
    lazy[v].second += k;
    lazy[v].second %= MOD;
}

void init() {
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        child[p[i]].push_back(i);
        lazy[p[i]] = {0, 0};
    }

    return;
}

void solve() {
    int m, v, x, k;
    for (int i = 0; i < q; i++) {
        cin >> m >> v;
        if (m == 1) {
            cin >> x >> k;
            query(v, x, k);
        } else {
            update(v);
            cout << tree[v] << '\n';
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
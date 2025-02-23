#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

#define N 300'001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct PQ {
    ll x;
    int a, b;
    bool operator<(const PQ &t) const { return x > t.x; }
};

ll w[N], s[N];
int n, m, p[N];
bool finished[N];
priority_queue<PQ> ans_buff;
priority_queue<PQ> g[N];
vector<int> ans;

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (g[a].size() < g[b].size())
        swap(a, b);
    p[b] = a;
    w[a] += w[b];
    while (!g[b].empty()) {
        PQ cur = g[b].top();
        g[b].pop();
        if (find_root(cur.a) != a)
            g[a].push(cur);
    }
    while (!g[a].empty()) {
        ll _x = g[a].top().x;
        int _a = find_root(g[a].top().a);
        int _b = g[a].top().b;
        if (w[a] < _x)
            break;
        g[a].pop();
        if (a == _a || finished[_b])
            continue;
        if (w[a] + w[_a] >= s[_b]) {
            ans_buff.push({_b, a, _a});
            finished[_b] = true;
        } else {
            ll diff = max((s[_b] - w[a] - w[_a]) >> 1, 1ll);
            g[a].push({w[a] + diff, _a, _b});
            g[_a].push({w[_a] + diff, a, _b});
        }
    }
}

inline bool comp_root(int a, int b) { return find_root(a) == find_root(b); }

void init() {
    int a, b;
    iota(p, p + N, 0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> s[i];
        if (w[a] + w[b] >= s[i]) {
            ans_buff.push({i, a, b});
            continue;
        }
        ll diff = max((s[i] - w[a] - w[b]) >> 1, 1ll);
        g[a].push({w[a] + diff, b, i});
        g[b].push({w[b] + diff, a, i});
    }
}

void solve() {
    while (!ans_buff.empty()) {
        int x = ans_buff.top().x;
        int a = ans_buff.top().a;
        int b = ans_buff.top().b;
        ans_buff.pop();

        if (comp_root(a, b))
            continue;
        union_root(a, b);
        ans.pb(x);
    }
    cout << ans.size() << '\n';
    for (auto a : ans)
        cout << a << ' ';
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

#define N 250000
#define pb emplace_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

int n, m, k;
ll dist[N * 5];
vector<pair<int, int>> v[N * 5];

inline void g(int &x, int d) { x = x + n - d; }

void dijk() {
    priority_queue<pair<ll, int>> pq;
    pq.emplace(-1, k + n - 1);
    while (!pq.empty()) {
        ll cur_dist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        if (dist[cur])
            continue;
        dist[cur] = -cur_dist;
        for (auto [a, w] : v[cur]) {
            if (!dist[a])
                pq.emplace(cur_dist - w, a);
        }
        if (cur < n) {
            for (auto a : {cur << 1, cur << 1 | 1}) {
                if (!dist[a])
                    pq.emplace(cur_dist, a);
            }
        } else if (cur < (n << 1)) {
            if (!dist[cur + (n << 1)])
                pq.emplace(cur_dist, cur + (n << 1));
        } else if (cur < (n << 2)) {
            cur -= (n << 1);
            if (!dist[(cur >> 1) + (n << 1)])
                pq.emplace(cur_dist, (cur >> 1) + (n << 1));
        }
    }
}

void init() {
    cin >> n >> m >> k;
    int a, b, c, d, e;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d >> e;
        for (g(b, 1), g(c, 0); b < c; b >>= 1, c >>= 1) {
            if (b & 1) {
                v[b + (n << 1)].pb(i + (N << 2), a);
                b++;
            }
            if (c & 1) {
                c--;
                v[c + (n << 1)].pb(i + (N << 2), a);
            }
        }

        for (g(d, 1), g(e, 0); d < e; d >>= 1, e >>= 1) {
            if (d & 1)
                v[i + (N << 2)].pb(d++, 0);
            if (e & 1)
                v[i + (N << 2)].pb(--e, 0);
        }
    }
}

void solve() {
    dijk();
    for (int i = 0; i < n; i++)
        cout << dist[i + n] - 1 << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
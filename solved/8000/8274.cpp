#include <iostream>
#include <queue>
#include <vector>

#define N 500000
#define pb push_back

using namespace std;

int n, m, k;
vector<int> dist((N << 2) + 200000, N);
vector<int> v[(N << 2) + 200000];

inline void g(int &x, int d) { x = x + n - d; }

void dijk() {
    priority_queue<pair<int, int>> pq;
    pq.push({0, k + n - 1});
    dist[k + n - 1] = 0;
    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        if (dist[cur] < cur_dist)
            continue;
        int w = cur >= (N << 2) ? 1 : 0;
        for (auto a : v[cur]) {
            if (dist[a] > -cur_dist + w) {
                pq.push({cur_dist - w, a});
                dist[a] = -cur_dist + w;
            }
        }
        if (cur < n) {
            for (auto a : {cur << 1, cur << 1 | 1}) {
                if (dist[a] > -cur_dist) {
                    pq.push({cur_dist, a});
                    dist[a] = -cur_dist;
                }
            }
        } else if (cur < (n << 1)) {
            if (dist[cur + (n << 1)] > -cur_dist) {
                pq.push({cur_dist, cur + (n << 1)});
                dist[cur + (n << 1)] = -cur_dist;
            }
        } else if (cur < (n << 2)) {
            cur -= (n << 1);
            if (dist[(cur >> 1) + (n << 1)] > -cur_dist) {
                pq.push({cur_dist, (cur >> 1) + (n << 1)});
                dist[(cur >> 1) + (n << 1)] = -cur_dist;
            }
        }
    }
}

void add_edge(int b, int c, int d, int e, int i) {
    for (; b < c; b >>= 1, c >>= 1) {
        if (b & 1) {
            v[b + (n << 1)].pb(i + (N << 2));
            b++;
        }
        if (c & 1) {
            c--;
            v[c + (n << 1)].pb(i + (N << 2));
        }
    }

    for (; d < e; d >>= 1, e >>= 1) {
        if (d & 1)
            v[i + (N << 2)].pb(d++);
        if (e & 1)
            v[i + (N << 2)].pb(--e);
    }
}

void init() {
    cin >> n >> m >> k;
    int b, c, d, e;
    for (int i = 0; i < m; i++) {
        cin >> b >> c >> d >> e;
        g(b, 1), g(c, 0), g(d, 1), g(e, 0);
        add_edge(b, c, d, e, i << 1);
        add_edge(d, e, b, c, i << 1 | 1);
    }
}

void solve() {
    dijk();
    for (int i = 0; i < n; i++)
        cout << dist[i + n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
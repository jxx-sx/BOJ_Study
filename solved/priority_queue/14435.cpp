#include <iostream>
#include <queue>

#define N 200'001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Query {
    int i, j, k;
} qry[N];

struct P {
    int a, b, i;
    bool operator<(const P &t) const { return b > t.b; }
};
priority_queue<P> pq[N];

int n, m, k, q;
int h_limit[N];
int h[N];
int child[N];
int cur, prv;
bool done[N];

void init() {
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= m; i++)
        cin >> h_limit[i];
    for (int i = 1; i <= k; i++)
        cin >> child[i];
    for (int i = 0; i < q; i++) {
        cin >> qry[i].i >> qry[i].j >> qry[i].k;
        pq[qry[i].i].push({qry[i].j, max(h_limit[qry[i].k] >> 1, 1), i});
        pq[qry[i].j].push({qry[i].i, max(h_limit[qry[i].k] >> 1, 1), i});
    }
}

void solve() {
    for (int i = 1; i <= k; i++) {
        int x = child[i];
        h[x]++;
        if (i > 2 && cur > prv)
            h[x]++;
        prv = cur;
        while (!pq[x].empty()) {
            if (pq[x].top().b > h[x])
                break;
            int a = pq[x].top().a;
            int j = pq[x].top().i;
            pq[x].pop();
            if (h[x] + h[a] >= h_limit[qry[j].k]) {
                if (!done[j]) {
                    cur++;
                    done[j] = true;
                }
            } else {
                int tmp = max((h_limit[qry[j].k] - h[x] - h[a]) >> 1, 1);
                pq[a].push({x, tmp + h[a], j});
                pq[x].push({a, tmp + h[x], j});
            }
        }
        cout << cur << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}
#include <iostream>
#include <queue>
#include <vector>
#define pb push_back

using namespace std;

int n, m, k, s, d, tax;
long long dist[1001];
vector<pair<int, int>> v[1001];
priority_queue<pair<long long, int>> pq;

long long dijk() {
    // init
    for (int i = 1; i <= n; i++)
        dist[i] = 0;
    while (pq.size())
        pq.pop();

    for (auto a : v[s])
        pq.push({-(dist[s] + tax + a.second), a.first});
    while (pq.size()) {
        auto cur = pq.top();
        pq.pop();
        if (dist[cur.second])
            continue;
        dist[cur.second] = -cur.first;
        if (cur.second == d)
            break;
        for (auto a : v[cur.second])
            if (!dist[a.first] and a.first != s)
                pq.push({-(-cur.first + tax + a.second), a.first});
    }

    return dist[d];
}

void init() {
    int a, b, w;
    cin >> n >> m >> k >> s >> d;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        v[a].pb({b, w});
        v[b].pb({a, w});
    }
}

void solve() {
    int tmp;
    cout << dijk() << '\n';
    while (k--) {
        cin >> tmp;
        tax += tmp;
        cout << dijk() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
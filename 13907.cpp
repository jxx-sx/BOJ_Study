#include <iostream>
#include <queue>
#include <vector>
#define pb push_back

using namespace std;

struct Node {
    long long dist;
    int dst, cnt;

    bool operator<(const Node &t) const { return dist == t.dist ? cnt < t.cnt : dist > t.dist; }

    Node(long long dist, int dst, int cnt) : dist(dist), dst(dst), cnt(cnt) {}
};

int n, m, k, s, d, tax;
long long dist[1001];
bool visited[1001];
vector<pair<int, int>> v[1001];
priority_queue<Node> pq;

void dijk() {
    for (auto a : v[s])
        pq.push(Node(a.second, a.first, 1));
    while (pq.size()) {
        auto cur = pq.top();
        pq.pop();
        if (visited[cur.dst])
            continue;
        if (cur.dst == d) {
            dist[cur.cnt] = dist[cur.cnt] == 0 ? cur.dist : min(dist[cur.cnt], cur.dist);
            continue;
        }
        visited[cur.dst] = true;
        for (auto a : v[cur.dst])
            if (!visited[a.first])
                pq.push(Node(cur.dist + a.second, a.first, cur.cnt + 1));
    }
}

long long find() {
    long long ret = 300000000000000;
    for (int i = 1; i <= n; i++)
        if (dist[i])
            ret = min(ret, dist[i] + tax * i);
    return ret;
}

void init() {
    int a, b, w;
    cin >> n >> m >> k >> s >> d;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        v[a].pb({b, w});
        v[b].pb({a, w});
    }

    visited[s] = true;

    dijk();
}

void solve() {
    int tmp;
    cout << find() << '\n';
    while (k--) {
        cin >> tmp;
        tax += tmp;
        cout << find() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
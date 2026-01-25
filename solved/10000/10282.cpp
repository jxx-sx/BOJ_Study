#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int dst, s;
    Node(int dst, int s) : dst(dst), s(s) {}

    bool operator<(const Node &t) const { return s > t.s; }
};

int n, d, c;
vector<int> mn;
vector<pair<int, int>> e[10001];
priority_queue<Node> pq;

void init() {
    int a, b, s;
    cin >> n >> d >> c;
    mn = vector<int>(n + 1, 0);
    for (int i = 1; i <= 10000; i++)
        e[i].clear();
    while (d--) {
        cin >> a >> b >> s;
        e[b].push_back({a, s});
    }
}

void solve() {
    int mx_time = 0;
    int cnt = 0;
    pq.push(Node(c, 1));
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if (mn[cur.dst])
            continue;
        mx_time = mn[cur.dst] = cur.s;
        cnt++;
        for (auto a : e[cur.dst]) {
            if (mn[a.first])
                continue;
            pq.push(Node(a.first, cur.s + a.second));
        }
    }

    cout << cnt << ' ' << mx_time - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> edges[1001];
int in_degree[1001];
int ans[1001];
int n, m;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void init() {
    int a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        edges[a].push_back(b);
        in_degree[b]++;
    }

    for (int i = 1; i <= n; i++)
        if (in_degree[i] == 0)
            pq.push({1, i});
    return;
}

void solve() {
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        ans[cur.second] = cur.first;
        for (auto a : edges[cur.second]) {
            in_degree[a]--;
            if (in_degree[a] == 0)
                pq.push({cur.first + 1, a});
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
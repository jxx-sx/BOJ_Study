#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges[n + 1];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    bool check[n + 1];
    for (int i = 0; i < n + 1; i++) {
        check[i] = false;
    }
    int s, e, t;
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> t;
        edges[s].push_back({t, e});
        edges[e].push_back({t, s});
        sum += t;
    }
    int count = 0;
    for (int i = 0; i < edges[1].size(); i++) {
        pq.push(edges[1][i]);
    }
    check[1] = true;
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();

        if (!check[cur.second]) {
            check[cur.second] = true;
            count += 1;
            sum -= cur.first;
            for (int i = 0; i < edges[cur.second].size(); i++) {
                if (!check[edges[cur.second][i].second])
                    pq.push(edges[cur.second][i]);
            }
        }
        if (count == n - 1)
            break;
    }
    cout << (count == n - 1 ? sum : -1);
}
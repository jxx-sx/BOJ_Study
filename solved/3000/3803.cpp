#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, e, t;
    cin >> n;
    while (n != 0) {
        cin >> m;
        bool check[n + 1];
        vector<pair<int, int>> edges[n + 1];
        int edges_count = 0, ans = 0;
        for (int i = 0; i < n + 1; i++) {
            check[i] = false;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 0; i < m; i++) {
            cin >> s >> e >> t;
            edges[s].push_back({t, e});
            edges[e].push_back({t, s});
        }

        for (int i = 0; i < edges[1].size(); i++) {
            pq.push(edges[1][i]);
        }
        check[1] = true;

        while (!pq.empty()) {
            pair<int, int> cur = pq.top();
            pq.pop();

            if (!check[cur.second]) {
                check[cur.second] = true;
                for (int i = 0; i < edges[cur.second].size(); i++) {
                    if (!check[edges[cur.second][i].second]) {
                        pq.push(edges[cur.second][i]);
                    }
                }
                ans += cur.first;
                edges_count += 1;
            }
            if (edges_count == n - 1)
                break;
        }
        cout << ans << '\n';
        cin >> n;
    }
}
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, e, h1, h2, k;
    int ans = 100000000;
    cin >> n >> m >> s >> e;
    vector<pair<int, int>> edges[n + 1];
    priority_queue<pair<int, int>> pq;
    bool check[n + 1];

    for (int i = 0; i < n + 1; i++) {
        check[i] = false;
    }

    for (int i = 0; i < m; i++) {
        cin >> h1 >> h2 >> k;
        edges[h1].push_back({k, h2});
        edges[h2].push_back({k, h1});
    }

    for (int i = 0; i < edges[h2].size(); i++) {
        pq.push(edges[h2][i]);
    }

    check[h1] = true;

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();

        if (cur.second == h1) {
            ans = (ans < cur.first ? ans : cur.first);
            cout << ans;
            break;
        }

        if (!check[cur.second]) {
            check[cur.second] = true;
            ans = (ans < cur.first ? ans : cur.first);
            for (int i = 0; i < edges[cur.second].size(); i++) {
                if (!check[edges[cur.second][i].second]) {
                    pq.push(edges[cur.second][i]);
                }
            }
        }
    }

    return 0;
}
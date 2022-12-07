#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    int s, e, t;

    cin >> n >> m;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<pair<int, int>> edges[n + 1];
    bool mark[n + 1];

    for (int i = 0; i < m; i++) {
        cin >> s >> e >> t;
        edges[s].push_back({t, e});
    }
    cin >> s >> e;
    for (int i = 0; i < n + 1; i++) {
        mark[i] = false;
    }

    for (int i = 0; i < edges[s].size(); i++) {
        pq.push(edges[s][i]);
        mark[s] = true;
    }

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        if (cur.second == e) {
            cout << cur.first;
            break;
        }

        if (!mark[cur.second]) {
            for (int i = 0; i < edges[cur.second].size(); i++) {
                pair<int, int> tmp = edges[cur.second][i];
                if (!mark[tmp.second]) {
                    pq.push({tmp.first + cur.first, tmp.second});
                }
            }
        }
        mark[cur.second] = true;
    }
}
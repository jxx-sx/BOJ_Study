#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define MAX 2000001;

using namespace std;
struct cmp {
    bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) { return a.first < b.first; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E, K;
    cin >> V >> E;
    bool is_red[V + 1];
    int distance[V + 1];
    for (int i = 0; i < V + 1; i++) {
        distance[i] = MAX;
        is_red[i] = false;
    }
    cin >> K;
    distance[K] = 0;
    is_red[K] = true;
    vector<pair<int, int>> edges[V + 1];
    int a, b, c;
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> c;
        edges[a].push_back({c, b});
    }
    int v = 1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < edges[K].size(); i++) {
        pq.push(edges[K][i]);
    }

    while (!pq.empty() && v != V) {
        int cur_node = pq.top().second;
        if (!is_red[cur_node]) {
            distance[cur_node] = pq.top().first;
            for (int i = 0; i < edges[cur_node].size(); i++) {
                pq.push({distance[cur_node] + edges[cur_node][i].first, edges[cur_node][i].second});
            }
            is_red[cur_node] = true;
            v++;
        }
        pq.pop();
    }

    for (int i = 1; i < V + 1; i++) {
        if (distance[i] == 2000001) {
            cout << "INF\n";
        } else {
            cout << distance[i] << '\n';
        }
    }
}
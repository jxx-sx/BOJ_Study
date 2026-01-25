#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct compare {
    bool operator()(pair<int, vector<int>> a, pair<int, vector<int>> b) { return a.first > b.first; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    int s, e, t;

    cin >> n >> m;

    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, compare> pq;
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
        vector<int> tmp;
        tmp.push_back(s);
        tmp.push_back(edges[s][i].second);
        pq.push({edges[s][i].first, tmp});
        mark[s] = true;
    }

    while (!pq.empty()) {
        pair<int, vector<int>> cur = pq.top();
        pq.pop();
        if (cur.second.back() == e) {
            cout << cur.first << '\n';
            cout << cur.second.size() << '\n';
            for (int i = 0; i < cur.second.size(); i++) {
                cout << cur.second[i] << ' ';
            }
            cout << '\n';
            break;
        }

        if (!mark[cur.second.back()]) {
            for (int i = 0; i < edges[cur.second.back()].size(); i++) {
                pair<int, int> tmp = edges[cur.second.back()][i];
                if (!mark[tmp.second]) {
                    vector<int> tmpV = cur.second;
                    tmpV.push_back(tmp.second);
                    pq.push({tmp.first + cur.first, tmpV});
                }
            }
        }
        mark[cur.second.back()] = true;
    }
}
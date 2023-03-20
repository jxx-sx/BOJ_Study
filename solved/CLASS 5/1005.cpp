#include <iostream>
#include <queue>
#include <vector>

using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // end_time, struct_num
int T[1001];
int D[1001];
bool is_visit[1001];
int n, k, w;
vector<int> edges[1001];

void init() {
    cin >> n >> k;
    pq = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>();
    for (int i = 1; i <= n; i++) {
        edges[i].clear();
        cin >> D[i];
        is_visit[i] = false;
        T[i] = 0;
    }

    int s, e;
    for (int i = 0; i < k; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        T[e]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!T[i]) {
            pq.push({D[i], i});
            is_visit[i] = true;
        }
    }
    cin >> w;

    return;
}

void solve() {
    int cur_time, cur;
    while (!pq.empty()) {
        cur_time = pq.top().first;
        cur = pq.top().second;
        pq.pop();

        if (cur == w) {
            cout << cur_time << '\n';
            break;
        }

        for (auto a : edges[cur]) {
            if (!is_visit[a]) {
                T[a]--;
                if (!T[a]) {
                    pq.push({cur_time + D[a], a});
                    is_visit[a] = true;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        init();
        solve();
    }

    return 0;
}
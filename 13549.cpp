#include <iostream>
#include <queue>

using namespace std;

bool is_visit[100001];
int n, k;
priority_queue<pair<int, int>> pq; // -cnt, cur

void solve() {
    while (!pq.empty()) {
        if (pq.top().second == k) {
            cout << -pq.top().first;
            break;
        }
        if ((pq.top().second << 1) < 100001)
            if (!is_visit[pq.top().second << 1]) {
                is_visit[pq.top().second << 1] = true;
                pq.push({pq.top().first, pq.top().second << 1});
            }

        if (pq.top().second - 1 >= 0)
            if (!is_visit[pq.top().second - 1]) {
                is_visit[pq.top().second - 1] = true;
                pq.push({pq.top().first - 1, pq.top().second - 1});
            }
        if (pq.top().second + 1 < 100001)
            if (!is_visit[pq.top().second + 1]) {
                is_visit[pq.top().second + 1] = true;
                pq.push({pq.top().first - 1, pq.top().second + 1});
            }
        pq.pop();
    }
}

void init() {
    cin >> n >> k;
    is_visit[n] = true;
    pq.push({0, n});
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}
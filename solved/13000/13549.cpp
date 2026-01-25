#include <iostream>
#include <queue>

using namespace std;

bool is_visit[100001];
int n, k;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // cnt, cur

void solve() {
    int cnt, cur, tmp;
    while (!pq.empty()) {
        cnt = pq.top().first;
        cur = pq.top().second;
        pq.pop();

        if (cur == k) {
            cout << cnt;
            break;
        }

        tmp = cur;
        while ((tmp <<= 1) < 100001) {
            if (!is_visit[tmp]) {
                is_visit[tmp] = true;
                pq.push({cnt, tmp});
            } else
                break;
        }

        if (cur - 1 >= 0)
            if (!is_visit[cur - 1]) {
                is_visit[cur - 1] = true;
                pq.push({cnt + 1, cur - 1});
            }

        if (cur + 1 < 100001)
            if (!is_visit[cur + 1]) {
                is_visit[cur + 1] = true;
                pq.push({cnt + 1, cur + 1});
            }
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
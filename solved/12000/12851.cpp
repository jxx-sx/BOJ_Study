#include <iostream>
#include <queue>

using namespace std;

int n, k;
pair<int, int> arr[100001]; // time, cnt
bool is_visit[100001];
queue<pair<int, int>> q; // cur, time

void solve() {
    int cur;
    while (!q.empty()) {
        cur = q.front().first;
        arr[cur].first = q.front().second + 1;
        if ((cur & 1) == 0)
            if (arr[cur >> 1].first == q.front().second)
                arr[cur].second += arr[cur >> 1].second;
        if (cur - 1 >= 0)
            if (arr[cur - 1].first == q.front().second)
                arr[cur].second += arr[cur - 1].second;
        if (cur + 1 < 100001)
            if (arr[cur + 1].first == q.front().second)
                arr[cur].second += arr[cur + 1].second;

        if ((cur << 1) < 100001)
            if (!is_visit[cur << 1]) {
                q.push({cur << 1, arr[cur].first});
                is_visit[cur << 1] = true;
            }
        if (cur - 1 >= 0)
            if (!is_visit[cur - 1]) {
                q.push({cur - 1, arr[cur].first});
                is_visit[cur - 1] = true;
            }
        if (cur + 1 < 100001)
            if (!is_visit[cur + 1]) {
                q.push({cur + 1, arr[cur].first});
                is_visit[cur + 1] = true;
            }
        q.pop();
    }

    cout << arr[k].first - 1 << '\n' << arr[k].second;
}

void init() {
    cin >> n >> k;
    arr[n].second = 1;
    is_visit[n] = true;
    q.push({n, 0});
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
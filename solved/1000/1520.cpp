#include <iostream>
#include <queue>

using namespace std;
typedef pair<int, pair<int, int>> pp;
int n, m;
int h[500][500], cnt[500][500];
bool visited[500][500];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    if (x < 0 or n <= x)
        return false;
    if (y < 0 or m <= y)
        return false;
    return true;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];
}

void solve() {
    priority_queue<pp> pq;
    pq.push({h[0][0], {0, 0}});
    visited[0][0] = true;
    cnt[0][0] = 1;
    while (!pq.empty()) {
        int cur_x = pq.top().second.first;
        int cur_y = pq.top().second.second;
        int cur_h = pq.top().first;
        pq.pop();
        for (int i = 0; i < 4; i++)
            if (valid(cur_x + dx[i], cur_y + dy[i])) {
                if (!visited[cur_x + dx[i]][cur_y + dy[i]]) {
                    pq.push({h[cur_x + dx[i]][cur_y + dy[i]], {cur_x + dx[i], cur_y + dy[i]}});
                    visited[cur_x + dx[i]][cur_y + dy[i]] = true;
                }
                if (h[cur_x + dx[i]][cur_y + dy[i]] < h[cur_x][cur_y])
                    cnt[cur_x + dx[i]][cur_y + dy[i]] += cnt[cur_x][cur_y];
            }
    }
    cout << cnt[n - 1][m - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
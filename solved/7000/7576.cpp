#include <iostream>
#include <queue>

using namespace std;
int n, m;
int arr[1000][1000];
int ans = 0;
queue<pair<int, int>> q;

void bfs() {
    int x, y;
    queue<pair<int, int>> next_q;
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        if (x > 0)
            if (arr[x - 1][y] == 0) {
                next_q.push({x - 1, y});
                arr[x - 1][y] = 1;
            }
        if (x < m - 1)
            if (arr[x + 1][y] == 0) {
                next_q.push({x + 1, y});
                arr[x + 1][y] = 1;
            }
        if (y > 0)
            if (arr[x][y - 1] == 0) {
                next_q.push({x, y - 1});
                arr[x][y - 1] = 1;
            }
        if (y < n - 1)
            if (arr[x][y + 1] == 0) {
                next_q.push({x, y + 1});
                arr[x][y + 1] = 1;
            }
    }
    q = next_q;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1)
                q.push({i, j});
        }
}

void solve() {
    while (!q.empty()) {
        ans += 1;
        bfs();
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 0) {
                cout << -1;
                return;
            }
        }
    cout << ans - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
}